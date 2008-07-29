/* $Id$
 *
 * Created by sccomer on Mar 29, 2007.
 *
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 */

package etch.bindings.java.support;

import etch.bindings.java.msg.Message;
import etch.bindings.java.msg.Type;
import etch.bindings.java.support.Pool.PoolRunnable;
import etch.bindings.java.transport.SessionMessage;
import etch.util.core.Who;

/**
 * Base class of stub implementations.
 * @param <T> The type of object used to implement stub.
 */
public class StubBase<T> implements SessionMessage
{
	/**
	 * Constructs the StubBase.
	 * @param svc the message source.
	 * @param obj the target of decoded messages.
	 * @param queued thread pool used to run AsyncMode.QUEUED methods.
	 * @param free thread pool used to run AsyncMode.FREE methods.
	 */
	public StubBase( DeliveryService svc, T obj, Pool queued, Pool free )
	{
		if (svc == null)
			throw new NullPointerException( "svc == null" );
		
		if (obj == null)
			throw new NullPointerException( "obj == null" );
		
		this._svc = svc;
		this._obj = obj;
		this._queued = queued;
		this._free = free;
		
		svc.setSession( this );
	}
	
	/**
	 * The message source.
	 */
	protected final DeliveryService _svc;
	
	/**
	 * The object used to implement stub.
	 */
	protected final T _obj;
	
	/**
	 * The thread pool used to run AsyncMode.QUEUED methods.
	 */
	protected final Pool _queued;
	
	/**
	 * The thread pool used to run AsyncMode.FREE methods.
	 */
	protected final Pool _free;

	@SuppressWarnings("unchecked")
	public final boolean sessionMessage( Who sender, Message msg ) throws Exception
	{
		Type type = msg.type();
		StubHelper<T> helper = (StubHelper<T>) type.getStubHelper();
		if (helper == null)
			return false;
		if (type.getAsyncMode() == AsyncMode.QUEUED)
		{
			_queued.run( new StubPoolRunnable( sender, msg, helper ) );
		}
		else if (type.getAsyncMode() == AsyncMode.FREE)
		{
			_free.run( new StubPoolRunnable( sender, msg, helper ) );
		}
		else
		{
			try
			{
				helper.run( _svc, _obj, sender, msg );
			}
			catch ( Exception e )
			{
				sessionNotify( _obj, e );
			}
		}
		return true;
	}

	public Object sessionQuery( Object query ) throws Exception
	{
		if (_obj instanceof ObjSession)
			return ((ObjSession) _obj)._sessionQuery( query );
		throw new UnsupportedOperationException( "unknown query "+query );
	}

	public void sessionControl( Object control, Object value ) throws Exception
	{
		if (_obj instanceof ObjSession)
			((ObjSession) _obj)._sessionControl( control, value );
		else
			throw new UnsupportedOperationException( "unknown control "+control );
	}

	public void sessionNotify( Object event ) throws Exception
	{
		sessionNotify( _obj, event );
	}
	
	/**
	 * Notifies the session of events going on "below the hood". Among
	 * other things, used to report exceptions from the transport stack,
	 * including exceptions caught by the stub which were thrown by obj.
	 * @param obj the service implementation, client or server.
	 * @param event an event which might or might not be an exception.
	 * @throws Exception
	 */
	public static void sessionNotify( Object obj, Object event ) throws Exception
	{
		if (obj instanceof ObjSession)
			((ObjSession) obj)._sessionNotify( event );
		else if (event instanceof Throwable)
			((Throwable) event).printStackTrace();
	}
	
	/**
	 * A PoolRunnable used by the stub to dispatch asynchronous
	 * receiver methods from messages.
	 */
	private final class StubPoolRunnable implements PoolRunnable
	{
		/**
		 * Constructs the StubPoolRunnable.
		 * @param sender the sender of the message.
		 * @param msg the message.
		 * @param helper the StubHelper which will dispatch the message.
		 */
		public StubPoolRunnable( Who sender, Message msg, StubHelper<T> helper )
		{
			this.sender = sender;
			this.msg = msg;
			this.helper = helper;
		}
		
		private final Who sender;
		
		private final Message msg;
		
		private final StubHelper<T> helper;

		public void exception( Exception e )
		{
			try
			{
				sessionNotify( e );
			}
			catch ( Exception e1 )
			{
				e1.printStackTrace();
			}
		}

		@SuppressWarnings("unchecked")
		public void run() throws Exception
		{
			helper.run( _svc, _obj, sender, msg );
		}
	}
}

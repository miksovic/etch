// This file automatically generated by:
//   Apache Etch 1.1.0-incubating (LOCAL-0) / java 1.1.0-incubating (LOCAL-0)
//   Thu Feb 19 12:21:33 CST 2009
// This file is automatically created for your convenience and will not be
// overwritten once it exists! Please edit this file as necessary to implement
// your service logic.

package org.apache.etch.examples.example;

import org.apache.etch.bindings.java.msg.Message;
import org.apache.etch.bindings.java.msg.Type;
import org.apache.etch.bindings.java.support.RetryMessageException;
import org.apache.etch.bindings.java.transport.UnwantedMessage;

/**
 * Your custom implementation of BaseFooServer. Add methods here to provide
 * implementations of messages from the client.
 */
public class ImplFooServer extends BaseFooServer
{
	/**
	 * Constructs the ImplFooServer.
	 *
	 * @param client a connection to the client session. Use this to send a
	 * message to the client.
	 */
	public ImplFooServer( RemoteFooClient client )
	{
		this.client = client;
	}
	
	/**
	 * A connection to the client session. Use this to send a
	 * message to the client.
	 */
	private final RemoteFooClient client;
	
	@Override
	public Integer foo( String msg )
	{
		return msg.hashCode();
	}
	
	@Override
	public void _sessionNotify( Object event ) throws Exception
	{
		if (event instanceof UnwantedMessage)
		{
			Message msg = ((UnwantedMessage) event).msg;
			Type type = msg.type();
			System.out.println( "unknown msg type "+type );
			
			String uri = (String) client._transportQuery( "uri" );
			
			// try to load ValueFactoryExample

			ValueFactoryExample nvf = new ValueFactoryExample( uri );
			if (nvf.getType( type.getId() ) != null)
			{
				System.out.println( "loading "+ValueFactoryExample.class.getName() );
				ExampleHelper.addServer( nvf, client );
				throw new RetryMessageException();
			}
			
			// no other service to try, fall through...
		}
	}
}
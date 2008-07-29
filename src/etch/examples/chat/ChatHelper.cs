// This file automatically generated by:
//   @EtchVersion@ (@EtchBuildTag@) / csharp @EtchVersion@ (@EtchBuildTag@)
//   Thu Jan 10 03:23:29 GMT-06:00 2008

using System;
using System.Collections.Generic;
using System.Text;

using Etch.Msg;
using Etch.Support;
using Etch.Transport;
using System.Collections;
using Etch.Util;

/// <summary>
/// Transport helper for Chat.
/// </summary>
namespace etch.examples.chat
{
    public class ChatHelper : TransportHelper
    {

        private ChatHelper()
        {
            // nothing
        }

		///
		/// <summary>Constructs a new server session listener per specifications
		/// in uri and resources.</summary>
		///
		/// <param name="uri"> contains specifications for the server session
		/// listener and for the server session transport stack.</param>
		///
		/// <param name="resources"> additional resources to aid in constructing
		/// new server sessions.</param>
		///
		/// <param name="implFactory"> called upon accepting a new server session to
		/// construct a new server implementation to handle messages
		/// from the client during the session.</param>
		///
		/// <returns> an out-of-band source that may be used to control
		/// the listener.</returns>
		///

		public static Transport NewChatListener( URL uri,		
			Resources resources, ChatServerFactory implFactory )
		{
			Resources res = InitResources( resources );

			TransportFactory factory = TransportFactory.Get( uri.Scheme );
			
			return factory.NewListener( uri, res, new MyServerFactory( uri, res, implFactory ) );
		}
		
		///
		/// <summary>Constructs a new client session per specifications in uri
		/// and resources.</summary>
		///
		/// <param name="uri"> contains specifications for the client session
		/// transport stack.</param>
		///
		/// <param name="resources"> additional resources to aid in constructing
		/// new sessions.</param>
		///
		/// <param name="client"> an client implementation to handle any
		/// messages from the server during the session.</param>
		///
		/// <returns> new remote server instance initialized by uri
		/// and resources which may be used to send messages to the
		/// server session.</returns>
		///
		
		public static RemoteChatServer NewChatServer( URL uri,
			Resources resources, ChatClient client )
		{
			resources = InitResources( resources );
			resources = new Resources( resources );
			resources.Add( Messagizer.VALUE_FACTORY, new ValueFactoryChat() );
	
			TransportFactory factory = TransportFactory.Get( uri.Scheme );
	
			DeliveryService d = factory.NewTransport( uri, resources );
	
			if (client != null)
				d.AddStub( new StubChatClient( d.GetSource(),
					client,
					(Pool) resources[ QUEUED_POOL ],
					(Pool) resources[ FREE_POOL ] ) );
	
			return new RemoteChatServer( d );
		}
		
		/// <summary>
		/// Factory for a Listener to use to create new instances of ChatServer.
		/// </summary>
		///
		public interface ChatServerFactory
		{
			///
			/// <param name="client"> an ChatClient instance for server implementation
			/// to use to call back to the client.</param>
			/// <returns> an instance of ChatServer (e.g., ImplChatServer) to
			/// handle messages which arrive from the client.</returns>
			///
			ChatServer NewChatServer( ChatClient client );
		}
		
		public class MyServerFactory : ServerFactory
		{
		
			private URL _uri;
			private Resources _resources;
			private ChatServerFactory _implFactory;
			
			public MyServerFactory( URL uri, Resources resources, ChatServerFactory implFactory ) 
			{
				_uri = uri;
				_resources = resources;
				_implFactory = implFactory;
			}
		
			public void NewServer( DeliveryService d )
			{
				ChatClient client = new RemoteChatClient( d );
				ChatServer server = _implFactory.NewChatServer( client );
				Pool qp = (Pool) _resources[ QUEUED_POOL ];
				Pool fp = (Pool) _resources[ FREE_POOL ];
				d.AddStub( new StubChatServer( d.GetSource(), server, qp, fp ) );
			}
			
			public ValueFactory NewValueFactory()
			{
				return new ValueFactoryChat();
			}
		}

	}
}
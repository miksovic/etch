// This file automatically generated by:
//   Apache Etch 1.1.0-incubating (LOCAL-0) / csharp 1.1.0-incubating (LOCAL-0)
//   Mon Feb 16 11:13:50 CST 2009
// This file is automatically created for your convenience and will not be
// overwritten once it exists! Please edit this file as necessary to implement
// your service logic.

using System;



using org.apache.etch.interoptester.example.iot.types.IOT;

///<summary>Your custom implementation of BaseIOTServer. Add methods here to provide
///implementation of messages from the client. </summary>
namespace org.apache.etch.interoptester.example.iot
{
	///<summary>Implementation for ImplIOTServer</summary>
	public class ImplIOTServer : BaseIOTServer
	{
		/// <summary>Constructs the ImplIOTServer.</summary>
 		/// <param name="client">a connection to the client session. Use this to
 		/// send a message to the client.</param>
		public ImplIOTServer(RemoteIOTClient client)
		{
			this.client = client;
		}
		
		/// <summary>A connection to the client session. Use this to
 		/// send a message to the client.</summary>
		private readonly RemoteIOTClient client;

        public override int? add(int? x, int? y)
        {
            if (x == null)
                throw new ArgumentNullException("x");
            if (y == null)
                throw new ArgumentNullException("y");
            return x + y;
        }
	}
}
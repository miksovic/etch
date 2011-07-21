// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership. The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
// 
//   http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the License for the
// specific language governing permissions and limitations
// under the License.
// 

using System;

using org.apache.etch.examples.signals.types.Signals;

namespace org.apache.etch.examples.signals
{
	///<summary>Main implementation for SignalsClient.</summary>
	public class MainSignalsClient : SignalsHelper.SignalsClientFactory
	{
		public static string ClientName { get; private set; }

		///<summary>Main for SignalsClient</summary>
		///<param name="args">Command Line Arguments</param>
		public static void Main(String[] args)
		{
			// TODO: Change to correct URI
			string uri = "udp://127.0.0.1:4001";
			
			RemoteSignalsServer server = SignalsHelper.NewServer( uri, null, new MainSignalsClient());

			// Connect to the service
			Console.WriteLine( "Connecting to server: " + uri );
			server._StartAndWaitUp( 4000 );

			try {
				ClientName = server.get_free_client_name();
				Console.WriteLine("Got client name: " + ClientName);

				Console.WriteLine(ClientName + ": Subscribing to example signal ...");
				server._SubscribeExampleSignal();

				Console.WriteLine(ClientName + ": Press enter to unsubscribe");
				Console.ReadLine();
				server._UnsubscribeExampleSignal();

				// Disconnect from the service
				Console.WriteLine(ClientName + ": Press enter to disconnect");
				Console.ReadLine();
				server._StopAndWaitDown(4000);
			} catch (Exception ex) {
				Console.WriteLine("Error: " + ex.Message);
			}
		}

		///<summary>Return a new instance of SignalsClient.</summary>
		///<param name="server">Reference to remote service</param>
		///<returns>Client Implementation</returns>
		public SignalsClient NewSignalsClient( RemoteSignalsServer server )
		{
			return new ImplSignalsClient( server );
		}
	}
}
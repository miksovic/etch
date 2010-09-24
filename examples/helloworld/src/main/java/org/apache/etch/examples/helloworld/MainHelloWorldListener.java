// This file automatically generated by:
//   Apache Etch 1.1.0-incubating (LOCAL-0) / java 1.1.0-incubating (LOCAL-0)
//   Wed Sep 15 17:22:46 CEST 2010
// This file is automatically created for your convenience and will not be
// overwritten once it exists! Please edit this file as necessary to implement
// your service logic.

package org.apache.etch.examples.helloworld;
/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */


import org.apache.etch.bindings.java.support.ServerFactory;
import org.apache.etch.util.core.io.Transport;

/**
 * Main program for HelloWorldServer. This program makes a listener to accept
 * connections from MainHelloWorldClient.
 */
public class MainHelloWorldListener implements HelloWorldHelper.HelloWorldServerFactory
{
	/**
	 * Main program for HelloWorldServer.
	 * 
	 * @param args command line arguments.
	 * @throws Exception
	 */
	public static void main( String[] args ) throws Exception
	{
		// TODO Change to correct URI
		String uri = "tcp://127.0.0.1:4001";
		
		ServerFactory listener = HelloWorldHelper.newListener( uri, null,
			new MainHelloWorldListener() );

		// Start the Listener
		listener.transportControl( Transport.START_AND_WAIT_UP, 4000 );
	}

	public HelloWorldServer newHelloWorldServer( RemoteHelloWorldClient client )
	{
		return new ImplHelloWorldServer( client );
	}
}

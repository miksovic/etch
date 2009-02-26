/* $Id$
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

package org.apache.etch.services.config;

import org.apache.etch.util.URL;

/**
 * Main program for ConfigurationClient. This program makes a connection to the
 * listener created by MainConfigurationListener.
 */
public class MainConfigurationClient implements
	ConfigurationHelper.ConfigurationClientFactory
{
	/**
	 * Main program for ConfigurationClient.
	 * 
	 * @param args command line arguments.
	 * @throws Exception
	 */
	public static void main( String[] args ) throws Exception
	{
		// get our configUri from a local config file.
		ConfigurationServer local = new YamlConfig( null, "services/config/local" );
		String configUri = local.getStringPath( null, "configUri" );
		System.out.println( "configUri = "+configUri );
		local.unloadConfig();
		local = null;		
		
		RemoteConfigurationServer server = ConfigurationHelper.newServer(
			configUri, null, new MainConfigurationClient() );

		// Connect to the service.
		server._startAndWaitUp( 4000 );
		System.out.println( "connected to config service" );
		
		String name = new URL( configUri ).getUri();
		server.loadConfig( name );
		System.out.println( "loaded configuration named '"+name+"'" );
		
		// Load a config and play with it.
		System.out.println( "bool = "+server.getBooleanPath( null, "bool" ) );
		System.out.println( "int = "+server.getIntegerPath( null, "int" ) );
		System.out.println( "dbl = "+server.getDoublePath( null, "dbl" ) );
		System.out.println( "str = "+server.getStringPath( null, "str" ) );
		System.out.println( "date = "+server.getDatePath( null, "date" ) );
		
		System.out.println( "users/mary = "+server.getStringPath( null, "users/mary" ) );
		
		Object users = server.getConfigPath( null, "users" );
		System.out.println( "users/mary = "+server.getStringPath( users, "mary" ) );
		System.out.println( "users/alice = "+server.getStringPath( users, "alice" ) );

		// Disconnect from the service.
		server._stopAndWaitDown( 4000 );
	}

	public ConfigurationClient newConfigurationClient(
		RemoteConfigurationServer server ) throws Exception
	{
		return new ImplConfigurationClient( server );
	}
}

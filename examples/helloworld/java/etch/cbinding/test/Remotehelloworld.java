// This file automatically generated by:
//   Apache Etch 1.1.0-incubating (LOCAL-0) / java 1.1.0-incubating (LOCAL-0)
//   Fri Jul 16 12:01:27 CEST 2010
// This file is automatically created and should not be edited!

package etch.cbinding.test;
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



/**
 * Call to message translator for helloworld.
 */
@SuppressWarnings("unused")
public class Remotehelloworld extends org.apache.etch.bindings.java.support.RemoteBase implements helloworld
{
	/**
	 * Constructs the Remotehelloworld.
	 *
	 * @param svc
	 * @param vf
	 */
	public Remotehelloworld( org.apache.etch.bindings.java.support.DeliveryService svc, org.apache.etch.bindings.java.msg.ValueFactory vf )
	{
		super( svc, vf );
	}

	/**
	 * {@link _Async} class instance used to hide asynchronous message
	 * implementation. Use this to invoke the asynchronous message
	 * implementations.
	 */
	public final _Async _async = new _Async();

	/**
	 * {@link _Async} class instance used to hide asynchronous message
	 * implementation. This is here for backwards compatibility only, use
	 * {@link #_async} instead.
	 * @deprecated
	 */
	@Deprecated
	public final _Async _inner = _async;

	/**
	 * Asynchronous implementation of service methods.
	 */
	public class _Async
	{

		// Mixin Methods
	}
}

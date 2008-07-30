/* $Id$
 *
 * Copyright 2007-2008 Cisco Systems Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

package etch.bindings.java.support;

/**
 * Exception thrown when messages marked with @Authorize fail.
 */
public class _Etch_AuthException extends _Etch_RuntimeException
{
	private static final long serialVersionUID = -5541931265968145750L;

	/**
	 * Constructs the _Etch_AuthException.
	 */
	public _Etch_AuthException()
	{
		// don't init anything.
	}

	/**
	 * Constructs the _Etch_AuthException.
	 * 
	 * @param msg a message describing the failure.
	 */
	public _Etch_AuthException( String msg )
	{
		super( msg );
	}
}
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
 * Interface to a queued or free thread pool.
 */
public interface Pool
{
	/**
	 * @param runnable the thing to run.
	 * @throws Exception if there is a problem scheduling the
	 * runnable to run.
	 */
	void run( PoolRunnable runnable ) throws Exception;
	
	/**
	 * A runnable which can throw an exception.
	 */
	public interface PoolRunnable
	{
		/**
		 * @throws Exception
		 */
		public void run() throws Exception;

		/**
		 * Reports an exception thrown by the run method.
		 * @param e
		 */
		public void exception( Exception e );
	}
}

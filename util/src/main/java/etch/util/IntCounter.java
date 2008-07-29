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

package etch.util;

/**
 * A safe integer counter.
 */
public class IntCounter
{
	/**
	 * Adjusts the value of the counter by k.
	 * @param k the adjustment to the counter.
	 * @return the new value of the counter.
	 */
	public synchronized int adjust( int k )
    {
        value += k;
        return value;
    }

	/**
	 * @return the value of the counter.
	 */
	public int get()
    {
        return value;
    }
	
	private int value;
}
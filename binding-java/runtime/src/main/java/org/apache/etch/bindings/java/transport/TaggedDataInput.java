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

package org.apache.etch.bindings.java.transport;

import java.io.IOException;

import org.apache.etch.bindings.java.msg.Message;
import org.apache.etch.util.FlexBuffer;


/**
 * A TaggedDataInput reads type tagged values from an input buf.
 */
public interface TaggedDataInput
{
	/**
	 * Reads a message from the buf.
	 * @param buf the flex buffer containing the message.
	 * @return a message read from the buf.
	 * @throws IOException
	 */
	public Message readMessage( FlexBuffer buf ) throws IOException;
}
"""
$Id$

# Copyright 2007-2008 Cisco Systems Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy
# of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.
#
"""
from __future__ import absolute_import

class MessageHandler(object):
    """
    Interface used to deliver messages from a message source.
    """

    # TODO: original signature 'boolean message(Who sender, Message msg)', maybe call this 'queueMessage'??
    def deliverMessage(self, sender, msg):
        """
        Delivers a message from a message source.
        
        @param sender - the message sender (meaning depends upon the message source)
        @param msg - the message from the message source
        @return - True if the message was processed
        @raise Exception
        """
        raise UnimplementedInterfaceMethodException
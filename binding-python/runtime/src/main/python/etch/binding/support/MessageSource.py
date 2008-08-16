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

class MessageSource(object):
    """
    A message source is used to model the origin of a message to a stub so that
    a reply might be sent.
    """
    
    def messagex(self, recipient, msg):
        """
        Sends a message to a message source. The message is encoded in some way
        (e.g., compressed binary format or xml), and then delivered to a transport
        (e.g., packetized data stream or http response).
        
        @param recipient - a transport specific opaque value which identifies
        the sender of a message. Delivered by a message handler to the stub
        and may be passed here to send a message back to the original sender.
        Passing None means "use the default recipient".
        
        @param msg - the message to send.
        
        @raises Exception
        """
        raise UnimplementedInterfaceMethod


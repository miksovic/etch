/* $Id$ 
 * 
 * Licensed to the Apache Software Foundation (ASF) under one or more 
 * contributor license agreements. See the NOTICE file distributed with  
 * this work for additional information regarding copyright ownership. 
 * The ASF licenses this file to you under the Apache License, Version  
 * 2.0 (the "License"); you may not use this file except in compliance  
 * with the License. You may obtain a copy of the License at 
 * 
 * http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and 
 * limitations under the License. 
 */ 

/*
 * etch_transportmsg.c
 * i_transportmessage interface
 */

#include "etch_transport_message.h"
#include "etch_message.h"
#include "etch_objecttypes.h"
#include "etch_log.h"
#include "etch_mem.h"



/*
 * etch_msghandler_defmessage()
 * default virtual implementation 
 * @param sender cller retains
 * @param msg  
 */
int etchtransportmsg_def_transportmessage (void* data, void* sender, void* msg)
{
      return -1;
}

/*
 * destroy_transportmessage()
 * i_transportmessage destructor
 */
int destroy_transportmessage(void* data)
{
  i_transportmessage* sm = (i_transportmessage*)data;
    if (NULL == sm) return -1;

    if (!is_etchobj_static_content(sm))
    {   etch_free(sm->itransport);
    }
            
    return destroy_objectex((etch_object*)sm);
}

/**
 * new_transportmsg_interface()
 * i_transportmessage constructor
 * @param itransport transport interface virtual function overrides, 
 * caller relinquishes ownership of this memory
 * @param itransport transport interface virtual function overrides, 
 * caller relinquishes ownership of this memory
 */
i_transportmessage* new_transportmsg_interface(void* thisx, 
    etch_transport_message tm, i_transport* itransport)  
{
    i_transportmessage* newi = (i_transportmessage*) new_object
        (sizeof(i_transportmessage), ETCHTYPEB_TRANSPORTMSG, CLASSID_TRANSPORTMSG);

    ((etch_object*)newi)->clone   = clone_null;
    ((etch_object*)newi)->destroy = destroy_transportmessage;  

    newi->transport_message = tm? tm: etchtransportmsg_def_transportmessage;

    newi->itransport = itransport? itransport: new_default_transport_interface();
    newi->transport_control = newi->itransport->transport_control; 
    newi->transport_notify  = newi->itransport->transport_notify;
    newi->transport_query   = newi->itransport->transport_query;
    newi->get_session       = newi->itransport->get_session;
    newi->set_session       = newi->itransport->set_session;

    newi->thisx = thisx;

    return newi;
}





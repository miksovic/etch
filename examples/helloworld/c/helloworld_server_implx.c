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

// This file automatically generated by:
//   Apache Etch 1.1.0-incubating (LOCAL-0) / c 1.1.0-incubating (LOCAL-0)
//   Fri Aug 28 15:58:20 CEST 2009
// This file is automatically created and should not be edited!

/*
 * helloworld_server_implx.c 
 * $helper.getImplName functions which would ordinarily not be subject to edit.
 */

#include "helloworld_server_impl.h"
#include "helloworld_remote_client.h"
#include "etch_objecttypes.h"
#include "etch_general.h"
#include "etch_url.h"

int destroy_helloworld_server_impl(helloworld_server_impl*);

/* - - - - - - - - - - - - - - - - - - - - - - - -   
 *helloworld_server_impl private construction / destruction 
 * - - - - - - - - - - - - - - - - - - - - - - - -    
 */

/**
 * init_helloworld_server_impl()
 * called by helloworld_server_impl constructor to instantiate server implementation 
 * object and initialize with default virtuals.
 * @param client the remote client, not owned.
 * @param usermem_dtor destructor for any custom memory allocations.
 */
helloworld_server_impl* init_helloworld_server_impl(helloworld_remote_client* client, 
    etch_object_destructor usermem_dtor)
{
    helloworld_server_impl* pserver = (helloworld_server_impl*) new_object (sizeof(helloworld_server_impl), 
        ETCHTYPEB_EXESERVERIMPL, get_dynamic_classid_unique(&CLASSID_HELLOWORLD_SERVER_IMPL));  
		
    pserver->client  = client;  /* not owned */
    pserver->object.destroy = destroy_helloworld_server_impl;  /* private destructor */
    pserver->destroyex = usermem_dtor;  /* user memory destructor */

    /* instantiate base and copy virtuals, if any, to this object */
    pserver->helloworld_server_base = new_helloworld_server_base(pserver, NULL); /* owned */

    pserver->ihelloworld = pserver->helloworld_server_base->ihelloworld;


    pserver->say_hello = pserver->helloworld_server_base->say_hello;


    pserver->iobjsession = pserver->helloworld_server_base->iobjsession;
    pserver->iobjsession->thisx = pserver;  /* set implementor reference */
    pserver->_session_control = pserver->helloworld_server_base->_session_control;
    pserver->_session_notify  = pserver->helloworld_server_base->_session_notify;
    pserver->_session_query   = pserver->helloworld_server_base->_session_query;

    return pserver;
}

/**
 * destroy_perf_server_impl()
 * perf_server_impl private destructor.
 * calls back to user destructor to effect cleanup of any perf_server_impl 
 * memory which may have been allocated in custom code added by user.
 */
int destroy_helloworld_server_impl (helloworld_server_impl* thisx)
{
    if (NULL == thisx) return -1;

    if (!is_etchobj_static_content(thisx))
    {    
        if(thisx->destroyex)
        {   /* call back to user memory destructor */
            thisx->destroyex(thisx);
        }
        if(thisx->helloworld_server_base)
        {
            destroy_helloworld_server_base(thisx->helloworld_server_base);
        }
    }
            
    return destroy_objectex(thisx);
}

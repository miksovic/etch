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

#include "helloworld_client_impl.h"
#include "etch_url.h"
#include "etch_arrayval.h"
#include "etch_binary_tdo.h"
#include "etch_exception.h"
#include "etch_general.h"
#include "etch_log.h"

#include <stdio.h>

unsigned short CLASSID_HELLOWORLD_CLIENT_IMPL;	
	
	
char* HELLOWORLD_ETCHCIMP = "CIMP";

/* generated signatures */
int destroy_helloworld_client_implx(void*);
helloworld_client_impl* init_helloworld_client_impl(struct helloworld_remote_server*, etch_object_destructor);


/* - - - - - - - -    
 * instantiation
 * - - - - - - - -   
 */

/**
 * new_helloworld_client_impl()
 * helloworld_client_impl constructor.
 * add your custom initialization and virtual method overrides here.
 */
helloworld_client_impl* new_helloworld_client_impl(struct helloworld_remote_server* server) 
{
    helloworld_client_impl* pclient  /* allocate object and assign default virtuals */
        = init_helloworld_client_impl(server, destroy_helloworld_client_implx);	
    /* add virtual method overrides, if any, here */
    //etchmap_insertxw(pclient_base->virtuals, example_valufact_get_static()->str_example_xxx, implementation, FALSE);

    return pclient;
}


/**
 * destroy_helloworld_client_implx()
 * destructor for any user allocated memory.
 * this code is invoked by the private perf_client_impl destructor,
 * via perf_client.destroyex(). add code here to destroy any memory you  
 * may have allocated for your custom perf_client implementation.
 */
int destroy_helloworld_client_implx(void* data)
{
    /*
      helloworld_client_impl* thisx = (helloworld_client_impl*)data;
     */

    return 0;
}

/* - - - - - - - - - - - - - - - - - - -
 * session interface method overrides
 * - - - - - - - - - - - - - - - - - - -
 */

 /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * implementations of helloworld_client messages from server, if any 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 */
 

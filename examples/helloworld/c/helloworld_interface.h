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

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include "etch_object.h"
#include "etch_mailbox.h"

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned short CLASSID_HELLOWORLD_SERVICE_INTERFACE;
extern unsigned short CLASSID_HELLOWORLD_USER;
extern unsigned short CLASSID_HELLOWORLD_USERUNKNOWNEXCEPTION;

//typedef struct helloworld_user helloworld_user;





/**
 * helloworld_user 
 * helloworld service value object user 
 */
typedef struct helloworld_user
{
    etch_object object;


    int id;
    etch_string* name;
 
 } helloworld_user;

helloworld_user* new_helloworld_user();
helloworld_user* clone_helloworld_user(helloworld_user* other); 
int is_helloworld_user(void* obj); 

/**
 * helloworld_UserUnknownException 
 * helloworld service value object userunknownexception 
 */
typedef struct helloworld_UserUnknownException
{
    etch_object object;

    etch_string*    message;
    uint32          errorcode;
    excptype_t      excptype;

    etch_string* mes;
 
 } helloworld_UserUnknownException;

helloworld_UserUnknownException* new_helloworld_UserUnknownException();
helloworld_UserUnknownException* clone_helloworld_UserUnknownException(helloworld_UserUnknownException* other); 
int is_helloworld_UserUnknownException(void* obj); 



typedef etch_string* (*helloworld_say_hello)(void* thisx, helloworld_user* to_whom);

//typedef struct i_mailbox i_mailbox;

typedef i_mailbox* (*helloworld_async_begin_say_hello)(void* thisx, helloworld_user* to_whom);

typedef etch_string* (*helloworld_async_end_say_hello)(void* thisx, i_mailbox*);

/**
 * i_helloworld
 * helloworld service interface
 */
typedef struct i_helloworld
{
    etch_object object;

    /* - - - - - - - - - - -
     * service virtuals
     * - - - - - - - - - - -
     */
    helloworld_say_hello say_hello;
     
    /* - - - - - - - - - - -
     * service data
     * - - - - - - - - - - -
     */
    helloworld_user* user;
    helloworld_UserUnknownException* UserUnknownException;

} i_helloworld;

i_helloworld* new_helloworld_service_interface();

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* HELLOWORLD_H */

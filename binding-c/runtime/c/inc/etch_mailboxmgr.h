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
 * etch_mailboxmgr.h
 * i_mailboxmgr interface
 */
#ifndef ETCHIMAILBOXMGR_H
#define ETCHIMAILBOXMGR_H

#if(0)

 MAILBOXMANAGER
 |  transportCall(Who to, message)  
 |  redeliver(Who from, message)
 |  unregister(mailbox)
 |- SESSIONMESSAGE<SessionData>
 |  |  sessionMessage(Who from, message)  
 |   - SESSION
 |       sessionQuery(); sessionControl(); sessionNotify();
  - TRANSPORTMESSAGE  
    |  transportMessage(to, Message);
     - TRANSPORT
          transportQuery(); transportControl(); transportNotify();
          getSession(); setSession();
#endif

#include "etch_mailboxint.h"
#include "etch_sessionmsg.h"
#include "etch_transportmsg.h"
#include "etchmutex.h"

typedef int (*etch_mbm_transport_call) (void* thisx, void* whoto, void* msg, void** out);
typedef int (*etch_mbm_redeliver)  (void* thisx, void* whofrom, void* msg);
typedef int (*etch_mbm_unregister) (void* thisx, void* mailbox);


/**
 * i_mailbox_manager
 * mailbox manager interface
 */
typedef struct i_mailbox_manager
{
    unsigned int    hashkey;  
    unsigned short  obj_type; 
    unsigned short  class_id;
    struct objmask* vtab;  
    int  (*destroy)(void*);
    void*(*clone)  (void*); 
    obj_gethashkey  get_hashkey;
    struct objmask* parent;
    etchresult*     result;
    unsigned int    refcount;
    unsigned int    length;
    unsigned char   is_null;
    unsigned char   is_copy;
    unsigned char   is_static;
    unsigned char   reserved;

    void* thisx; /* object which is the interface implementor */

    /**
     * transport_call()
     * sends a message which begins a call after allocating a mailbox 
     * to receive responses.
     * @param whoto recipient. caller retains.
     * @param message the message which begins the call.
     * caller relinquishes on success, retains on other than success.  
     * @param out pointer to location to return the i_mailbox which will 
     * receive responses to the call.
     * @return 0 success, -1 error
     */
    etch_mbm_transport_call transport_call;

    /**
     * redeliver()
     * redelivers messages extant from a closed mailbox.
     * @param whofrom sender. caller retains.
     * @param message. caller relinquishes on success, retains on other than success.  
     * @return 0 success, -1 error
     */
    etch_mbm_redeliver      redeliver;

    /**
     * unregister()
     * removes specified mailbox from the set of mailboxes receiving responses to messages.
     * @param mailbox the mailbox to remove. caller does not own it.
     * @return 0 success, -1 error
     */
    etch_mbm_unregister     unregister;

    /* implements session message interface */
    i_sessionmessage*    ism;
    etch_session_message session_message;
    etch_session_control session_control;
    etch_session_notify  session_notify;
    etch_session_query   session_query;

    /* implements transport message interface */
    i_transportmessage*    itm;  
    etch_transport_message transport_message;
    etch_transport_control transport_control;  
    etch_transport_notify  transport_notify;   
    etch_transport_query   transport_query;   
    etch_transport_get_session  get_session;   
    etch_transport_set_session  set_session;

    etchmutex* rwlock;  /* not owned */

} i_mailbox_manager;


/**
 * new_mailboxmgr_interface()
 * i_mailbox_manager constructor.
 * @param thisx the mailbox manager object.
 * @param itm transportmesssage interface, caller retains, can be null.
 * @param ism sessionmessage interface, caller retains, can be null.
 */
i_mailbox_manager* new_mailboxmgr_interface(void* thisx, 
    i_transportmessage*, i_sessionmessage*);  

#endif /* ETCHIMAILBOXMGR_H */
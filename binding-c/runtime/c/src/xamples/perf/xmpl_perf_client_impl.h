/*
 * xmpl_perf_client_impl.h 
 */

#ifndef PERF_CLIENT_IMPL_H
#define PERF_CLIENT_IMPL_H

#include "xmpl_perf_client.h"
#include "etch_transport.h"

unsigned short CLASSID_PERFCLIENTBASE_IMPL;
typedef struct perf_remote_server perf_remote_server;

/**
 * perf_client_impl
 * your custom implementation of perf_base_client. add methods here 
 * to provide implementations of messages from the client, if any.
 */
typedef struct perf_client_impl
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

    i_perf_client*  perf_client_base;  /* owned */
    i_perf*         iperf;         /* not owned */
    perf_remote_server* server;    /* not owned */

    int (*destroyex) (void*);  /* user memory destructor */

    /* - - - - - - - - - - - -
     * objsession
     * - - - - - - - - - - - -
     */
    i_objsession* iobjsession;  /* owned by base */
    /* note that iobjsession->thisx is set to this perf_client_impl* */
    etch_session_control _session_control;
    etch_session_notify  _session_notify;
    etch_session_query   _session_query;

    /* - - - - - - - - - - - -
     * base service virtuals
     * - - - - - - - - - - - -
     */
    perf_add      add;
    perf_sum      sum;
    perf_report   report;
    perf_dist     dist;
    perf_add2     add2;
    perf_report2  report2;


    /* - - - - - - - - - - - -
     * base service data
     * - - - - - - - - - - - -
     */
    perf_point* point;   /* owned by base */


    /* - - - - - - - - - - - - -
     * custom instance data 
     * - - - - - - - - - - - - -
     */
    char* exampleobj;

} perf_client_impl;



/* constructor */
perf_client_impl* new_perf_client_impl (perf_remote_server*);


#endif /* PERF_CLIENT_IMPL_H */


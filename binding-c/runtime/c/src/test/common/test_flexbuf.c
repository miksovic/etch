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
 * test_flexbuf.c
 * test flex buffer
 */
#include "apr_time.h" /* some apr must be included first */
#include "etchthread.h"
#include <limits.h>
#include <float.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>

#include "cunit.h"
#include "basic.h"
#include "automated.h"

#include "etchflexbuf.h"
#include "etch_global.h"


int apr_setup(void);
int apr_teardown(void);
int this_setup();
int this_teardown();
apr_pool_t* g_apr_mempool;
const char* pooltag = "etchpool";


/* - - - - - - - - - - - - - - 
 * unit test infrastructure
 * - - - - - - - - - - - - - -
 */

int init_suite(void)
{
    apr_setup();
    etch_runtime_init(TRUE);
    return this_setup();
}

int clean_suite(void)
{
    this_teardown();
    etch_runtime_cleanup(0,0); /* free memtable and cache etc */
    apr_teardown();
    return 0;
}

int g_is_automated_test, g_bytes_allocated;

#define IS_DEBUG_CONSOLE FALSE

/*
 * apr_setup()
 * establish apache portable runtime environment
 */
int apr_setup(void)
{
    int result = apr_initialize();
    if (result == 0)
    {   result = etch_apr_init();
        g_apr_mempool = etch_apr_mempool;
    }
    if (g_apr_mempool)
        apr_pool_tag(g_apr_mempool, pooltag);
    else result = -1;
    return result;
}

/*
 * apr_teardown()
 * free apache portable runtime environment
 */
int apr_teardown(void)
{
    if (g_apr_mempool)
        apr_pool_destroy(g_apr_mempool);
    g_apr_mempool = NULL;
    apr_terminate();
    return 0;
}

int this_setup()
{
    etch_apr_mempool = g_apr_mempool;
    return 0;
}

int this_teardown()
{    
    return 0;
}

etch_flexbuffer* fbuf = 0;


/**
 * returns number of errors
 */
int check_buf(etch_flexbuffer* buf, const int len, const int ndx, const int avl)
{
    int errors = 0, avail = (int) etch_flexbuf_avail(buf);
    if (buf->datalen != len) errors++;
    if (buf->index   != ndx) errors++;
    if (avail        != avl) errors++;
    return errors;
}

void testCreateAndDestroy0(void)
{
    fbuf = new_flexbuffer(0);
    CU_ASSERT_PTR_NOT_NULL(fbuf);
    
    CU_ASSERT(etch_flexbuf_avail(fbuf) == 0);
    
    destroy_etch_flexbuffer(fbuf);
}

void testCreateAndDestroy1(void)
{
    fbuf = new_flexbuffer(-1);
    CU_ASSERT_PTR_NOT_NULL(fbuf);
    
    fbuf = new_flexbuffer(1);
    CU_ASSERT_PTR_NOT_NULL(fbuf);
    CU_ASSERT(etch_flexbuf_avail(fbuf) == 0);

    destroy_etch_flexbuffer(fbuf);
    
    fbuf = new_flexbuffer(4*1024*1024+1);
    CU_ASSERT_PTR_NOT_NULL(fbuf);
    destroy_etch_flexbuffer(fbuf); /* takes NULL */
}

void testCreateAndDestroy2(void)
{
    void *ptr = etch_malloc(1024, 0);
    fbuf = etch_flexbuf_create_b(ptr, 1024, 0);
    CU_ASSERT_PTR_NOT_NULL(fbuf);
    CU_ASSERT(etch_flexbuf_avail(fbuf) == 0);

    destroy_etch_flexbuffer(fbuf);
}

void testCreateAndDestroy3(void)
{
    void *ptr = etch_malloc(1024, 0);
    fbuf = etch_flexbuf_create_bi(ptr, 1024, 100, 0);
    CU_ASSERT_PTR_NOT_NULL(fbuf);
    CU_ASSERT(etch_flexbuf_avail(fbuf) == 100);

    destroy_etch_flexbuffer(fbuf);
}

void testPutAndGet(void)
{
    byte test_bytes[] = "testbytes";
    void *test_buffer = etch_malloc(128, 0);
    size_t n;
    int i;
    etch_flexbuffer *efb2;

    fbuf = new_flexbuffer(0);

    etch_flexbuf_put(fbuf, test_bytes, 0, strlen(test_bytes));

    /* rewind the buffer */
    etch_flexbuf_set_index(fbuf, 0);
    n = etch_flexbuf_get(fbuf, test_buffer, 0, strlen(test_bytes));
    CU_ASSERT(memcmp(test_buffer, test_bytes, n) == 0);

    /* test put byte */
    etch_flexbuf_set_index(fbuf, 0);
    for(i = 0; i < (int) strlen(test_bytes); i++)
        etch_flexbuf_put_byte(fbuf, test_bytes[i]);    

    etch_flexbuf_set_index(fbuf, 0);
    n = etch_flexbuf_get(fbuf, test_buffer, 0, strlen(test_bytes));
    CU_ASSERT(memcmp(test_buffer, test_bytes, n) == 0);

    /* test put from another buffer */
    efb2 = new_flexbuffer(0);
    etch_flexbuf_set_index(fbuf, 0);
    etch_flexbuf_put_from(efb2, fbuf, n);

    etch_flexbuf_set_index(efb2, 0);
    n = etch_flexbuf_get(efb2, test_buffer, 0, strlen(test_bytes));
    CU_ASSERT(memcmp(test_buffer, test_bytes, n) == 0);

    etch_free(test_buffer);
    destroy_etch_flexbuffer(fbuf);
    destroy_etch_flexbuffer(efb2);
}

void testPutAndGetFully(void)
{
    byte test_bytes[] = "testbytes";
    void *test_buffer = etch_malloc(128, 0);
    size_t n;

    fbuf = new_flexbuffer(0);

    etch_flexbuf_put(fbuf, test_bytes, 0, strlen(test_bytes));

    /* rewind the buffer */
    etch_flexbuf_set_index(fbuf, 0);
    n = etch_flexbuf_get_fully(fbuf, test_buffer, strlen(test_bytes));
    CU_ASSERT(memcmp(test_buffer, test_bytes, n) == 0);

    etch_flexbuf_set_index(fbuf, 0);
    n = etch_flexbuf_get_fully(fbuf, test_buffer, 4);
    CU_ASSERT(memcmp(test_buffer, test_bytes, 4) == 0);

    etch_flexbuf_set_index(fbuf, 0);
    n = etch_flexbuf_get_fully(fbuf, test_buffer, 32);
    CU_ASSERT(memcmp(test_buffer, test_bytes, min(strlen(test_bytes), 32)) == 0);

    etch_free(test_buffer);
    destroy_etch_flexbuffer(fbuf);
}


void testPutAndGetByte(void)
{
    byte test_bytes[] = "testbytes";
    void *test_buffer = etch_malloc(128, 0);
    size_t n;
    int i;

    fbuf = new_flexbuffer(0);

    etch_flexbuf_set_index(fbuf, 0);
    for(i = 0; i < (int)strlen(test_bytes); i++)
        etch_flexbuf_put_byte(fbuf, test_bytes[i]);    

    etch_flexbuf_set_index(fbuf, 0);
    n = etch_flexbuf_get(fbuf, test_buffer, 0, strlen(test_bytes));
    CU_ASSERT(memcmp(test_buffer, test_bytes, n) == 0);


    etch_free(test_buffer);
    destroy_etch_flexbuffer(fbuf);
}

void testPutAndGetShort(void)
{
    short test_shorts[] = {SHRT_MIN, SHRT_MAX, 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 0x7FFF, \
        0xFFFF, 0xFFFE, -8192, -4096, -2048, -1024, -512, -256, -128, -64, -32, -16, -8, -4, -2, -1};

    int i, result; short value = 0;

    fbuf = new_flexbuffer(0);

    for(i = 0; i < sizeof(test_shorts)/sizeof(short); i++)
        etch_flexbuf_put_short(fbuf, test_shorts[i]);    

    etch_flexbuf_set_index(fbuf, 0);

    for(i = 0; i < sizeof(test_shorts)/sizeof(short); i++)
    {
        result = etch_flexbuf_get_short(fbuf, &value);
        CU_ASSERT_EQUAL(result, 0);
        CU_ASSERT_EQUAL(test_shorts[i], value); 
    }   

    destroy_etch_flexbuffer(fbuf);
}


void testPutAndGetInt(void)
{
    int test_ints[] = {INT_MIN, INT_MAX, 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 0x7FFF, \
        0xFFFF, 0xFFFFF, 0xFFFFFF, 0xFFFFFFF, 0xFFFFFFE,0x7FFFFFFF, 0xFFFFFFFF, 0xF7FFFFFF, 0xF6FFFFFF, \
        0xF5FFFFFF, 0xF4FFFFFF, 0xF3FFFFFF, 0xF2FFFFFF, 0xF1FFFFFF, 0xF0FFFFFF, 0xFF0FFFFF, \
        -8192, -4096, -2048, -1024, -512, -256, -128, -64, -32, -16, -8, -4, -2, -1};

    int i;

    fbuf = new_flexbuffer(0);

    for(i = 0; i < sizeof(test_ints)/sizeof(int); i++)
        etch_flexbuf_put_int(fbuf, test_ints[i]);    

    etch_flexbuf_set_index(fbuf, 0);
    for(i = 0; i < sizeof(test_ints)/sizeof(int); i++)
    {   
        int n = 0, m = test_ints[i], result;
        result = etch_flexbuf_get_int(fbuf, &n);
        CU_ASSERT_EQUAL(result, 0);
        CU_ASSERT_EQUAL(n,m); 
    }   

    destroy_etch_flexbuffer(fbuf);
}


void testPutAndGetInt64(void)
{
    int64 test_int64s[] = {LONG_MIN, LONG_MAX, 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 0x7FFF, \
        0xFFFF, 0xFFFFF, 0xFFFFFF, 0xFFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF, 0xF7FFFFFF, 0xF6FFFFFF, 0x7FFFFFFFFFFFFFFF,\
        0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFF0, 0xFFFFFFFFFFFFFF00, 0xFFFFFFFFFFFFF000, 0xFFFFFFFFFFFFF000, \
        0xF5FFFFFF, 0xF4FFFFFF, 0xF3FFFFFF, 0xF2FFFFFF, 0xF1FFFFFF, 0xF0FFFFFF, 0xFF0FFFFF, \
        -8192, -4096, -2048, -1024, -512, -256, -128, -64, -32, -16, -8, -4, -2, -1};

    int i, result;

    fbuf = new_flexbuffer(0);

    for(i = 0; i < sizeof(test_int64s)/sizeof(int64); i++)
        etch_flexbuf_put_long(fbuf, test_int64s[i]);    

    etch_flexbuf_set_index(fbuf, 0);

    for(i = 0; i < sizeof(test_int64s)/sizeof(int64); i++)
    {   
        int64 n = 0, m = test_int64s[i];
        result = etch_flexbuf_get_long(fbuf, &n);
        CU_ASSERT_EQUAL(result, 0);
        CU_ASSERT_EQUAL(n,m); 
    }   

    destroy_etch_flexbuffer(fbuf);
}


void testPutAndGetFloat(void)
{
    float test_floats[] = {FLT_MIN, 0.0f, 1.1f, 2.2f, 4.4f, 8.8f, 16.16f, 32.32f, 64.64f, 128.128f, 256.256f, 512.512f,\
        1024.1024f, 2048.2048f, 4096.4096f, 8192.8192f, FLT_MAX};

    int i, result;

    fbuf = new_flexbuffer(0);

    for(i = 0; i < sizeof(test_floats)/sizeof(float); i++)
        etch_flexbuf_put_float(fbuf, test_floats[i]);    

    etch_flexbuf_set_index(fbuf, 0);

    for(i = 0; i < sizeof(test_floats)/sizeof(float); i++)
    {  
        float x = 0.0; double diff; int is_equal;
        const float y = test_floats[i];
        result = etch_flexbuf_get_float(fbuf, &x);
        CU_ASSERT_EQUAL(result, 0);
        diff = (double) (y - x);
        is_equal = fabs(diff) < 0.00001;
        CU_ASSERT_EQUAL(is_equal, TRUE);
    }
            

    destroy_etch_flexbuffer(fbuf);
}

void testPutAndGetDouble(void)
{
    double test_doubles[] = {DBL_MIN, 0.0, 1.1, 2.2, 4.4, 8.8, 16.16, 32.32, 64.64, 128.128, 256.256, 512.512,\
        1024.1024, 2048.2048, 4096.4096, 8192.8192, DBL_MAX};

    int i, result;

    fbuf = new_flexbuffer(0);

    for(i = 0; i < sizeof(test_doubles)/sizeof(double); i++)
        etch_flexbuf_put_double(fbuf, test_doubles[i]);    

    etch_flexbuf_set_index(fbuf, 0);

    for(i = 0; i < sizeof(test_doubles)/sizeof(double); i++)
    {   
        double x, y = test_doubles[i];
        result = etch_flexbuf_get_double(fbuf, &x);
        CU_ASSERT_EQUAL(result, 0);
        CU_ASSERT(x == y);  
    }  

    destroy_etch_flexbuffer(fbuf);
}

void testSetSize(void)
{
    etch_flexbuffer *fbuf = new_flexbuffer(0);

    CU_ASSERT_EQUAL(0, etch_flexbuf_set_length(fbuf, 1024));
    CU_ASSERT_EQUAL(0, check_buf(fbuf, 1024, 0, 1024));
   
    CU_ASSERT_EQUAL(0, etch_flexbuf_set_length(fbuf, 0));
    CU_ASSERT_EQUAL(0, check_buf(fbuf, 0, 0, 0));

    destroy_etch_flexbuffer(fbuf);
}

void testCompact(void)
{
    int i;
    etch_flexbuffer *fbuf = new_flexbuffer(128);

    for(i = 0; i < 10; i++)
        etch_flexbuf_put_short(fbuf, 1);

    etch_flexbuf_set_index(fbuf, 0);
    etch_flexbuf_compact(fbuf);
    CU_ASSERT(fbuf->index ==0);
    CU_ASSERT(etch_flexbuf_avail(fbuf) == (10*sizeof(short)));

    destroy_etch_flexbuffer(fbuf);
}


int _tmain(int argc, _TCHAR* argv[])
{
    char c=0;
    CU_pSuite ps = NULL;
    g_is_automated_test = argc > 1 && 0 != wcscmp(argv[1], L"-a");
    if (CUE_SUCCESS != CU_initialize_registry()) return 0;
    ps = CU_add_suite("suite flexbuffer", init_suite, clean_suite);
    CU_set_output_filename("../test_flexbuffer");
    etch_watch_id = 0; 

    CU_add_test(ps, "testCreateAndDestroy0", testCreateAndDestroy0);
    CU_add_test(ps, "testCreateAndDestroy1", testCreateAndDestroy1);
    CU_add_test(ps, "testCreateAndDestroy2", testCreateAndDestroy2);
    CU_add_test(ps, "testCreateAndDestroy3", testCreateAndDestroy3);
    CU_add_test(ps, "testPutAndGet", testPutAndGet);
    CU_add_test(ps, "testPutAndGetFully", testPutAndGetFully);
    CU_add_test(ps, "testPutAndGetByte", testPutAndGetByte);
    CU_add_test(ps, "testPutAndGetShort", testPutAndGetShort);
    CU_add_test(ps, "testPutAndGetInt", testPutAndGetInt);
    CU_add_test(ps, "testPutAndGetInt64", testPutAndGetInt64);
    CU_add_test(ps, "testPutAndGetFloat", testPutAndGetFloat);
    CU_add_test(ps, "testPutAndGetFloat", testPutAndGetDouble);
    CU_add_test(ps, "testSetSize", testSetSize);
    CU_add_test(ps, "testCompact", testCompact);

    if (g_is_automated_test)    
        CU_automated_run_tests();    
    else
    {   CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
    }

    if (!g_is_automated_test) { printf("any key ..."); while(!c) c = _getch();  printf("\n"); }     
    CU_cleanup_registry();
    return CU_get_error(); 
}
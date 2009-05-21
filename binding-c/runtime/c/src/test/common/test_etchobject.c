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
 * test_etchobject.c.c -- test etch object inheritance and primitives
 */
#include "apr_time.h" /* some apr must be included first */
#include "etchthread.h"
#include <tchar.h>
#include <stdio.h>
#include <conio.h>

#include "cunit.h"
#include "basic.h"
#include "automated.h"

#include "etch_global.h"
#include "etchobj.h"

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

/**
 * class_a: base class
 */
typedef struct class_a
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

    etch_string* a_string;
     
} class_a;


/**
 * class_a destructor
 */
int destroy_class_a(class_a* thisp)
{
    if (thisp->a_string)
        thisp->a_string->destroy(thisp->a_string);

    destroy_object((objmask*) thisp);
    return 0;
}

/**
 * class_a copy consttructor
 */
class_a* clone_class_a(class_a* origobj)
{
    class_a* newobj = (class_a*) new_object(sizeof(class_a), 413, 0);
    memcpy(newobj, origobj, sizeof(objmask));
    newobj->a_string = new_string(origobj->a_string->v.valw, ETCH_ENCODING_UTF16);   
    return newobj; 
}


/**
 * class_a constructor
 */
class_a* new_class_a(const wchar_t* strval)
{
    class_a* newobj  = (class_a*) new_object(sizeof(class_a), 403, 0);
    newobj->destroy  = destroy_class_a;
    newobj->clone    = clone_class_a;
    newobj->a_string = new_string(strval, ETCH_ENCODING_UTF16);
    return newobj;
}


/**
 * class_b: inherits from class_a
 */
typedef struct class_b
{
    unsigned int    hashkey;    
    unsigned short  obj_type; 
    unsigned short  class_id;
    struct objmask* vtab;
    int  (*destroy)(void*);
    void*(*clone)  (void*);  
    obj_gethashkey  get_hashkey;           
    class_a*        parent;
    etchresult*     result;
    unsigned int    refcount;
    unsigned int    length;     
    unsigned char   is_null;
    unsigned char   is_copy;
    unsigned char   is_static;
    unsigned char   reserved;

    char* data; 
    int   datasize;  

} class_b;


/**
 * class_b destructor
 */
int destroy_class_b(class_b* thisp)
{
    etch_free(thisp->data);
    destroy_object((objmask*) thisp);
    return 0;
}


/**
 * class_b copy consttructor
 */
class_b* clone_class_b(class_b* origobj)
{
    class_b* newobj  = (class_b*) new_object(sizeof(class_b), 415, 0);
    memcpy(newobj, origobj, sizeof(objmask));

    newobj->parent = origobj->parent? 
        origobj->parent->clone(origobj->parent): 
        new_class_a(NULL);

    if (origobj->data)
    {
        newobj->data     = etch_malloc(origobj->datasize, 412); 
        newobj->datasize = origobj->datasize;
        memcpy(newobj->data, origobj->data, origobj->datasize); 
    }
 
    return newobj;
}


/**
 * class_b constructor
 */
class_b* new_class_b(class_a* parent, const int datalen)
{
    class_b* newobj = (class_b*) new_object(sizeof(class_b), 404, 0);
    newobj->parent  = parent? parent: new_class_a(NULL);
    newobj->destroy = destroy_class_b;
    newobj->clone   = clone_class_b;
    newobj->data    = etch_malloc(datalen, 402);
    memset(newobj->data, 'x', datalen);
    newobj->datasize = datalen;
    return newobj;
}


/**
 * class_c: inherits from class_b
 */
typedef struct class_c
{
    unsigned int    hashkey;    
    unsigned short  obj_type; 
    unsigned short  class_id;
    struct objmask* vtab;
    int  (*destroy)(void*);
    void*(*clone)  (void*);  
    obj_gethashkey  get_hashkey;           
    class_b*        parent;
    etchresult*     result;
    unsigned int    refcount;
    unsigned int    length;
    unsigned char   is_null;
    unsigned char   is_copy;
    unsigned char   is_static;
    unsigned char   reserved;

    int* intarray;
    int  numitems;

} class_c;


/**
 * class_c destructor
 */
int destroy_class_c(class_c* thisp)
{
    etch_free(thisp->intarray);
    destroy_object((objmask*) thisp);
    return 0;
}


/**
 * class_c copy consttructor
 */
class_c* clone_class_c(class_c* origobj)
{
    class_c* newobj  = (class_c*) new_object(sizeof(class_c), 410, 0);
    memcpy(newobj, origobj, sizeof(objmask));

    if  (origobj->parent)
         newobj->parent = origobj->parent->clone(origobj->parent);
    else newobj->parent = new_class_b(NULL, 0);

    if (origobj->intarray)
    {
        newobj->intarray = etch_malloc(origobj->numitems * sizeof(int), 411);
        newobj->numitems = origobj->numitems;
        memcpy(newobj->intarray, origobj->intarray, origobj->numitems * sizeof(int)); 
    }

    return newobj; 
}


/**
 * class_c constructor
 */
class_c* new_class_c(class_b* parent)
{
    int i = 0;
    class_c* newobj  = (class_c*) new_object(sizeof(class_b), 400, 0);
    newobj->parent   = parent? parent: new_class_b(NULL, 0);
    newobj->destroy  = destroy_class_c;
    newobj->clone    = clone_class_c;

    newobj->numitems = 4;
    newobj->intarray = etch_malloc(4 * sizeof(int), 401);
    for(; i < 4; i++) newobj->intarray[i] = i;

    return newobj;
}


/**
 * test_inheritance()
 * test that in scenario c inherits from b inherits from a,
 * destroying c destroys b destroys a.
 */
void test_inheritance(void)
{
    class_a* class_toplevel = NULL;
    class_b* class_midlevel = NULL;
    class_c* class_lowlevel = NULL;

    class_toplevel = new_class_a(L"it works!");
    class_midlevel = new_class_b(class_toplevel, 128);
    class_lowlevel = new_class_c(class_midlevel);
 
    /* any object destructor should recursively destroy() its superclasses */
    CU_ASSERT_PTR_NOT_NULL_FATAL(class_lowlevel->parent);
    CU_ASSERT_PTR_NOT_NULL_FATAL(class_midlevel->parent);
    CU_ASSERT_PTR_NULL_FATAL(class_toplevel->parent);

    class_lowlevel->destroy(class_lowlevel);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);  /* verify all memory freed */
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();  /* start fresh for next test */   
}


/**
 * test_clone()
 * test validity of cloned objects, also test construction of inherited object
 * when the parent(s) implementation(s) is/are not specified.
 * clones must be disposable, i.e. they must own all their memory
 * including that of their superclasses, such that if c inherits from b 
 * inherits from a, and I clone c giving c', and I then destroy c, then 
 * I can subsequently destroy c' via normal channels.
 */
void test_clone(void)
{
    class_c* class_lowlevel = NULL;
    class_b* class_midlevel = NULL;
    class_a* class_toplevel = NULL;

    class_c* clone_lowlevel = NULL;
    class_b* clone_midlevel = NULL;
    class_a* clone_toplevel = NULL;

    /* construct class c and all its superclasses */
    class_lowlevel = new_class_c(NULL);

    /* verify that superclasses were created */
    class_midlevel = (class_b*) class_lowlevel->parent;
    CU_ASSERT_PTR_NOT_NULL_FATAL(class_midlevel);
    class_toplevel = (class_a*) class_midlevel->parent;
    CU_ASSERT_PTR_NOT_NULL_FATAL(class_toplevel);
    CU_ASSERT_PTR_NULL_FATAL(class_toplevel->parent);

    /* clone class c and all its superclasses */
    clone_lowlevel = class_lowlevel->clone(class_lowlevel);

    /* verify that superclasses were created */
    clone_midlevel = (class_b*) clone_lowlevel->parent;
    CU_ASSERT_PTR_NOT_NULL_FATAL(clone_midlevel);
    clone_toplevel = (class_a*) clone_midlevel->parent;
    CU_ASSERT_PTR_NOT_NULL_FATAL(clone_toplevel);
    CU_ASSERT_PTR_NULL_FATAL(clone_toplevel->parent);

    /* verify that superclass and data clones are not references to old memory */
    CU_ASSERT_NOT_EQUAL_FATAL(class_midlevel, clone_midlevel);
    CU_ASSERT_NOT_EQUAL_FATAL(class_toplevel, clone_toplevel);
   
    if (class_midlevel->data != 0 && clone_midlevel->data != 0)
        CU_ASSERT_NOT_EQUAL_FATAL(class_midlevel->data, clone_midlevel->data);
    if (class_toplevel->a_string != 0 && clone_toplevel->a_string != 0)
        CU_ASSERT_NOT_EQUAL_FATAL(class_toplevel->a_string, clone_toplevel->a_string);

    /* we don't need to do this for the test, but here we illustrate   
     * the etch C way of accessing superclass data from a subclass, 
     * which is to traverse the parent chain to the class you want, 
     * and cast the parent* to that class, if it is not so cast already. 
     */
    clone_midlevel->datasize = 1024; 
    clone_midlevel->data = etch_malloc(clone_midlevel->datasize, 419);
    memset(clone_midlevel->data, '-',  clone_midlevel->datasize);
 
    /* destroy class c with all its superclasses and associated instance data */
    class_lowlevel->destroy(class_lowlevel);

    /* destroy class c clone and all its superclasses 
     * if the clone of class_c had not properly cloned all its superclasses and 
     * data, this would crash on attempt to free dangling pointer.
     */
    clone_lowlevel->destroy(clone_lowlevel);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);  /* verify all memory freed */
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();  /* start fresh for next test */   
}


void test_primitive_byte(void)
{
    signed char v = 255;
    etch_byte* newobj = new_byte(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(v, newobj->value);

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();  
}

void test_primitive_bool(void)
{
    etch_boolean* newobj = new_boolean(100);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value, TRUE); 

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();   
}

void test_primitive_int8(void)
{
    signed char v = -1;
    etch_int8* newobj = new_int8(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value,v); 

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();   
}

void test_primitive_int16(void)
{
    short v = -1;
    etch_int16* newobj = new_int16(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value,v); 

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();   
}

void test_primitive_int32(void)
{
    int v = 1 << 31;
    etch_int32* newobj = new_int32(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value,v); 

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();   
}

void test_primitive_int64(void)
{
    int64 v = ((int64)(1)) << 63;
    etch_int64* newobj = new_int64(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value,v);  

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();  
}

void test_primitive_float(void)
{
    float v = (float)(3.14159);
    etch_float* newobj = new_float(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value,v); 

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();   
}

void test_primitive_double(void)
{
    double v = (1 << 31) + 3.14159;
    etch_double* newobj = new_double(v);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(newobj->value,v); 

    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();  
}

void test_primitive_string(void)
{
    wchar_t* v = L"it works!";
    etch_string* newobj = new_string(v, ETCH_ENCODING_UTF16);
    CU_ASSERT_PTR_NOT_NULL_FATAL(newobj); 
    CU_ASSERT_EQUAL(wcscmp(v, newobj->v.valw), 0);
    
    newobj->destroy(newobj); 
    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_nativearray_ctordtor()
 * test that we can create and destroy an etch_nativearray with all memory accounted for
 */
void test_nativearray_ctordtor(void)
{
    etch_nativearray* bytearray_1x4 = new_nativearray(CLASSID_ARRAY_BYTE, sizeof(byte), 1, 4, 0, 0);  
    CU_ASSERT_PTR_NOT_NULL_FATAL(bytearray_1x4); 

    bytearray_1x4->destroy(bytearray_1x4);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_nativearray_1x1x4()
 * test that we can populate and access a 1-dimensional array of byte
 */
void test_nativearray_1x1x4(void)
{
    int   i = 0, result = 0;
    char  x[4] = {'a','b','c','d'}, thisx = 0;
    const int numdimensions = 1, itemcount = 4;

    etch_nativearray* a = new_nativearray 
        (CLASSID_ARRAY_BYTE, sizeof(byte), numdimensions, itemcount, 0, 0);  
    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 

    for(i = 0; i < itemcount; i++)     /* populate array */
    {
        result = a->put1(a, &x[i], i); /* insert value of i to ith slot */
        CU_ASSERT_EQUAL(result, 0); 
    }

    for(i = 0; i < itemcount; i++)      /* read values out of array */
    {
        result = a->get1(a, &thisx, i); /* get value of ith slot into thisx */
        CU_ASSERT_EQUAL(result, 0); 
        CU_ASSERT_EQUAL(x[i], thisx); 
    }

    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_nativearray_1x4x4()
 * test that we can populate and access a 1-dimensional array of int
 */
void test_nativearray_1x4x4(void)
{
    int i = 0, j = 0, result = 0;
    const int numdimensions = 1, itemcount = 4;

    etch_nativearray* a = new_nativearray 
        (CLASSID_ARRAY_INT32, sizeof(int), numdimensions, itemcount, 0, 0);  
    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 

    for(i = 0; i < itemcount; i++)  /* populate array */
    {
        result = a->put1(a, &i, i); /* insert value of i to ith slot */
        CU_ASSERT_EQUAL(result, 0); 
    }

    for(i = 0; i < itemcount; i++)  /* read values out of array */
    {
        result = a->get1(a, &j, i); /* get value of ith slot into j */
        CU_ASSERT_EQUAL(result, 0); 
        CU_ASSERT_EQUAL(i, j); 
    }

    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_nativearray_1xstruct()
 * test that we can populate and access a 1-dimensional array of struct
 */
void test_nativearray_1xstruct(void)
{
    int i = 0, result = 0;
    const int numdimensions = 1, itemcount = 4;
    struct x { int n; char c; };
    struct x xgot  = {-1,'?'};
    struct x xs[4] = { {0,'a'}, {1,'b'}, {2,'c'}, {3,'d'}, };

    etch_nativearray* a = new_nativearray 
        (CLASSID_ARRAY_STRUCT, sizeof(struct x), numdimensions, itemcount, 0, 0);  
    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 

    for(i = 0; i < itemcount; i++)      /* populate array */
    {
        result = a->put1(a, &xs[i], i); /* insert xs[i] to ith slot */
        CU_ASSERT_EQUAL(result, 0); 
    }

    for(i = 0; i < itemcount; i++)      /* read values out of array */
    {
        result = a->get1(a, &xgot, i);  /* get value of ith slot into xgot */
        CU_ASSERT_EQUAL(result, 0); 
        result = memcmp(&xgot, &xs[i], sizeof(struct x));
        CU_ASSERT_EQUAL(result, 0); 
    }

    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_nativearray_2x1x4()
 * test that we can populate and access a 2-dimensional array of byte
 */
void test_nativearray_2x1x4(void)
{
    int   i = 0, j = 0, result = 0;
    char  x[2][4] = { {'a','b','c','d'}, {'e','f','g','h'}, }, thisx = 0;
    const int numdimensions = 2, dim0count = 4, dim1count = 2;

    /* note when creating arrays, the dimensions are specified in reverse,
     * low-order dimension (dim0) first, e.g., for x[2][3][4], 
     * dim0count is 4, dim1count is 3, dim2count is 2.
     */
    etch_nativearray* a = new_nativearray 
        (CLASSID_ARRAY_BYTE, sizeof(byte), numdimensions, dim0count, dim1count, 0);  

    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 

    for(i = 0; i < dim1count; i++)         /* populate array */
    {
        for(j = 0; j < dim0count; j++)      
        {                                  /* insert x[i][j] to array[i][j] */
            result = a->put2(a, &x[i][j], i, j); 
            CU_ASSERT_EQUAL(result, 0); 
        }
    }

    for(i = 0; i < dim1count; i++)         /* read array */
    {
        for(j = 0; j < dim0count; j++)     /* read values out of array */
        {                                  /* get array[i][j] into thisx */
            result = a->get2(a, &thisx, i, j); 
            CU_ASSERT_EQUAL(result, 0); 
            CU_ASSERT_EQUAL(x[i][j], thisx); 
        }
    }

    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_nativearray_3xstruct()
 * test that we can populate and access a 3-dimensional array of struct
 */
void test_nativearray_3xstruct(void)
{
    int i = 0, j = 0, k = 0, result = 0;
    struct x  { int n; char c; };
    struct x  xgot  = {-1,'?'};
    struct x *xthis = 0;

    struct x xs[2][3][4] = 
    {   
      {      
         {  
            {0,'a'}, {1,'b'}, {2,'c'}, {3,'d'},  
         },
         {  
            {0,'e'}, {1,'f'}, {2,'g'}, {3,'h'},  
         },
         {  
            {0,'i'}, {1,'j'}, {2,'k'}, {3,'l'},  
         },
      },
      {
         {  
            {0,'m'}, {1,'n'}, {2,'o'}, {3,'p'},  
         },
         {  
            {0,'q'}, {1,'r'}, {2,'s'}, {3,'t'},  
         },
         {  
            {0,'u'}, {1,'v'}, {2,'w'}, {3,'x'},  
         },
      },    
    };

    const int numdimensions = 3, dim0count = 4, dim1count = 3, dim2count = 2;

    etch_nativearray* a = new_nativearray (CLASSID_ARRAY_STRUCT, sizeof(struct x), 
        numdimensions, dim0count, dim1count, dim2count);  

    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 

    for(i = 0; i < dim2count; i++)   /* write array */       
    {
        for(j = 0; j < dim1count; j++)
        {
            for(k = 0; k < dim0count; k++)      
            {                                   
                result = a->put3(a, &xs[i][j][k], i, j, k); 
                CU_ASSERT_EQUAL(result, 0); 
            }
        }
    }

    for(i = 0; i < dim2count; i++)     /* read array */
    {
        for(j = 0; j < dim1count; j++)
        {
            for(k = 0; k < dim0count; k++)      
            {                                   
                result = a->get3(a, &xgot, i, j, k);   
                CU_ASSERT_EQUAL(result, 0); 
                xthis = &xs[i][j][k];
                result = memcmp(&xgot, xthis, sizeof(struct x));
                CU_ASSERT_EQUAL(result, 0); 
            }
        }
    }

    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_arrayfrom_2x1x4()
 * test that we can access a static 2-dimensional array of byte.
 * also validates that our array subscripting calculations match those of
 * the C compiler, since we map and access an array mapped by the compiler.
 * also validates that the etch_nativearray will not attempt to destroy
 * the byte vector of an array created in this manner. 
 */
void test_arrayfrom_2x1x4(void)
{
    int   i = 0, j = 0, result = 0;
    char  x[2][4] = { {'a','b','c','d'}, {'e','f','g','h'}, }, thisx = 0;
    const int numdimensions = 2, dim0count = 4, dim1count = 2;

    etch_nativearray* a = new_nativearray_from(&x, CLASSID_ARRAY_BYTE,  
        sizeof(byte), numdimensions, dim0count, dim1count, 0);  

    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 

    for(i = 0; i < dim1count; i++)         /* read array */
    {
        for(j = 0; j < dim0count; j++)     /* read values out of array */
        {                                  /* get array[i][j] into thisx */
            result = a->get2(a, &thisx, i, j); 
            CU_ASSERT_EQUAL(result, 0); 
            CU_ASSERT_EQUAL(x[i][j], thisx); 
        }
    }

    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/** 
 * test_subarray()
 * test that we can create a one-dimensional subarray from a 2-dimensional 
 * array of byte, and that all memory is accounted for.
 */
void test_subarray(void)
{
    int   i = 0, j = 0, result = 0;
    char  x[2][4] = { {'a','b','c','d'}, {'e','f','g','h'}, }, thisx = 0;
    const int numdimensions = 2, dim0count = 4, dim1count = 2;
    etch_nativearray *a0 = NULL, *a1 = NULL, *a2 = NULL;

    etch_nativearray* a = new_nativearray_from(&x, CLASSID_ARRAY_BYTE,  
        sizeof(byte), numdimensions, dim0count, dim1count, 0);  

    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 
    a->content_obj_type = ETCHTYPEB_BYTE;
    a->content_class_id = CLASSID_NONE; /* unwrapped content */

    a0 = new_subarray(a, 0); /* test index 0 */
    CU_ASSERT_PTR_NOT_NULL_FATAL(a0); 

    CU_ASSERT_EQUAL(a0->is_content_owned, FALSE);
    CU_ASSERT_EQUAL(a0->numdims,   a->numdims-1);
    CU_ASSERT_EQUAL(a0->bytecount, a->bytecount/2);
    CU_ASSERT_EQUAL(a0->itemsize,  a->itemsize);

    CU_ASSERT_EQUAL(a0->content_obj_type, a->content_obj_type);
    CU_ASSERT_EQUAL(a0->content_class_id, a->content_class_id);

    /* recall that dimension and dimsize are stored low-order 
     * dimension first, so dimension[0] and dimsize[0] are 
     * the same for byte x[2][4] as for x[4] */
    CU_ASSERT_EQUAL(a0->dimension[0], a->dimension[0]);  
    CU_ASSERT_EQUAL(a0->dimsize[0],   a->dimsize[0]);  

    for(i = 0; i < dim0count; i++)      
    {                                  
        result = a0->get1(a0, &thisx, i); 
        CU_ASSERT_EQUAL(result, 0); 
        CU_ASSERT_EQUAL(x[0][i], thisx); 
    }

    a1 = new_subarray(a, 1); /* test index 1 */
    CU_ASSERT_PTR_NOT_NULL_FATAL(a1); 

    CU_ASSERT_EQUAL(a1->is_content_owned, FALSE);
    CU_ASSERT_EQUAL(a1->numdims,   a->numdims-1);
    CU_ASSERT_EQUAL(a1->bytecount, a->bytecount/2);
    CU_ASSERT_EQUAL(a1->itemsize,  a->itemsize);

    CU_ASSERT_EQUAL(a1->content_obj_type, a->content_obj_type);
    CU_ASSERT_EQUAL(a1->content_class_id, a->content_class_id);

    /* recall that dimension and dimsize are stored low-order 
     * dimension first, so dimension[0] and dimsize[0] are 
     * the same for byte x[2][4] as for x[4] */
    CU_ASSERT_EQUAL(a1->dimension[0], a->dimension[0]);
    CU_ASSERT_EQUAL(a1->dimsize[0],   a->dimsize[0]);

    for(i = 0; i < dim0count; i++)      
    {                                  
        result = a1->get1(a1, &thisx, i); 
        CU_ASSERT_EQUAL(result, 0); 
        CU_ASSERT_EQUAL(x[1][i], thisx); 
    }

    a2 = new_subarray(a, 2); /* test nonexistent index 2 */
    CU_ASSERT_PTR_NULL(a2); 

    a1->destroy(a1);
    a0->destroy(a0);
    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/*
 * test_if_busted_subarray()
 * this test is here to debug something that was either broken in subarray,
 * or that was not broken, but rather the validator test using it was broken.
 * verdict: subarray itemsize was broken, is fixed.
 */
void test_if_busted_subarray(void)  
{
    short x[2][3][4] = 
      { { { 1,1,1,1, }, { 1,1,1,1, }, { 1,-1,32767, -32768, }, },
        { { 1,1,1,1, }, { 1,1,1,1, }, { 1,-1,0xfffe,0xffff, }, },
      };
    const int numdimensions = 3, dim0count = 4, dim1count = 3, dim2count = 2;
    int i=0, j=0, k=0;

    etch_nativearray* a1 = new_nativearray_from(&x, CLASSID_ARRAY_INT16,  
         sizeof(short), numdimensions, dim0count, dim1count, dim2count);  
    a1->content_obj_type = ETCHTYPEB_INT16;
    a1->content_class_id = CLASSID_NONE; /* unwrapped */

    for(i = 0; i < dim2count; i++)
    {
        etch_nativearray* a2 = (etch_nativearray*) etch_nativearray_get_element(a1, i); 
        CU_ASSERT_EQUAL_FATAL(is_etch_nativearray(a2), TRUE);
        CU_ASSERT_EQUAL_FATAL(a2->bytecount,   a1->bytecount/a1->dimension[2]);
        CU_ASSERT_EQUAL_FATAL(a2->numdims,     a1->numdims-1);
        CU_ASSERT_EQUAL_FATAL(a2->dimsize[0],  a1->dimsize[0]);  
        CU_ASSERT_EQUAL_FATAL(a2->dimsize[1],  a1->dimsize[1]);
        CU_ASSERT_EQUAL_FATAL(a2->dimension[0],a1->dimension[0]);
        CU_ASSERT_EQUAL_FATAL(a2->dimension[1],a1->dimension[1]);
        CU_ASSERT_EQUAL_FATAL(a2->dimension[1],dim1count);

        for(j = 0; j < dim1count; j++)
        {
            etch_nativearray* a3 = (etch_nativearray*) etch_nativearray_get_element(a2, j); 
            CU_ASSERT_EQUAL_FATAL(is_etch_nativearray(a3), TRUE);
            CU_ASSERT_EQUAL_FATAL(a3->bytecount,   a2->bytecount/a2->dimension[1]);
            CU_ASSERT_EQUAL_FATAL(a3->numdims,     a2->numdims-1);
            CU_ASSERT_EQUAL_FATAL(a3->dimsize[0],  a2->dimsize[0]);
            CU_ASSERT_EQUAL_FATAL(a3->dimension[0],a2->dimension[0]);
            CU_ASSERT_EQUAL_FATAL(a3->dimension[0],dim0count);

            for(k = 0; k < dim0count; k++)
            {   
                short n_expected = 0, n_actual = 0;
                etch_int16* shortobj  = (etch_int16*) etch_nativearray_get_element(a3, k); 
                CU_ASSERT_EQUAL_FATAL(is_etch_int16(shortobj), TRUE);
                n_expected = x[i][j][k];
                n_actual   = shortobj->value;
                CU_ASSERT_EQUAL_FATAL(n_expected, n_actual);

                shortobj->destroy(shortobj);
            }

            a3->destroy(a3);
        } 

        a2->destroy(a2);   
    }

    a1->destroy(a1);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);  
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();  /* start fresh for next test */
}


/** 
 * test_get_element()
 * test that we can get element[i] of a native array, and that element
 * is another native array, or a wrapped etch object the same type as
 * the array's content_obj_type and possibly content_class_id.
 */
void test_get_element(void)
{
    int   i = 0, j = 0, result = 0;
    char  x[2][4] = { {'a','b','c','d'}, {'e','f','g','h'}, }, thisx = 0;
    const int numdimensions = 2, dim0count = 4, dim1count = 2;
    etch_nativearray *a1  = NULL;
    objmask*   returnobj  = NULL;
    etch_byte* retbyteobj = NULL;

    etch_nativearray* a = new_nativearray_from(&x, CLASSID_ARRAY_BYTE,  
        sizeof(byte), numdimensions, dim0count, dim1count, 0);  

    CU_ASSERT_PTR_NOT_NULL_FATAL(a); 
    a->content_obj_type = ETCHTYPEB_BYTE;
    a->content_class_id = CLASSID_NONE; /* unwrapped content */

    /* get element[1] from the array, expecting a byte[4] native array */
    returnobj = etch_nativearray_get_element(a, 1); 

    CU_ASSERT_EQUAL_FATAL(is_etch_nativearray(returnobj), TRUE);

    a1 = (etch_nativearray*) returnobj;

    CU_ASSERT_EQUAL(a1->is_content_owned, FALSE);
    CU_ASSERT_EQUAL(a1->numdims,   a->numdims-1);
    CU_ASSERT_EQUAL(a1->bytecount, a->bytecount/2);
    CU_ASSERT_EQUAL(a1->itemsize,  a->itemsize);

    CU_ASSERT_EQUAL(a1->content_obj_type, a->content_obj_type);
    CU_ASSERT_EQUAL(a1->content_class_id, a->content_class_id);
    CU_ASSERT_EQUAL(a1->dimension[0], a->dimension[0]);
    CU_ASSERT_EQUAL(a1->dimsize[0],   a->dimsize[0]);

    for(i = 0; i < dim0count; i++)      
    {   
        /* get element[i] from the subarray, expecting an etch_byte object */                               
        returnobj = etch_nativearray_get_element(a1, i); 
        CU_ASSERT_PTR_NOT_NULL_FATAL(returnobj); 
        CU_ASSERT_EQUAL_FATAL(returnobj->class_id, CLASSID_PRIMITIVE_BYTE);

        retbyteobj = (etch_byte*) returnobj; /* verify that wrapped byte */
        thisx = retbyteobj->value;           /* matches original array */
        CU_ASSERT_EQUAL(x[1][i], thisx); 

        retbyteobj->destroy(retbyteobj);
    }

    a1->destroy(a1);
    a->destroy(a);

    g_bytes_allocated = etch_showmem(0, IS_DEBUG_CONSOLE);   
    CU_ASSERT_EQUAL(g_bytes_allocated, 0);  
    memtable_clear();    
}


/**
 * main   
 */
int _tmain(int argc, _TCHAR* argv[])
{
    char c=0;
    CU_pSuite ps = NULL;
    g_is_automated_test = argc > 1 && 0 != wcscmp(argv[1], L"-a");
    if (CUE_SUCCESS != CU_initialize_registry()) return 0;
    CU_set_output_filename("../test_etchobject");
    ps = CU_add_suite("etchobject test suite", init_suite, clean_suite);
    etch_watch_id = 0; 

    CU_add_test(ps, "test primitive byte",    test_primitive_byte); 
    CU_add_test(ps, "test primitive boolean", test_primitive_bool); 
    CU_add_test(ps, "test primitive int8",    test_primitive_int8); 
    CU_add_test(ps, "test primitive int16",   test_primitive_int16); 
    CU_add_test(ps, "test primitive int32",   test_primitive_int32); 
    CU_add_test(ps, "test primitive int64",   test_primitive_int64); 
    CU_add_test(ps, "test primitive float",   test_primitive_float); 
    CU_add_test(ps, "test primitive double",  test_primitive_double); 
    CU_add_test(ps, "test primitive string",  test_primitive_string); 

    CU_add_test(ps, "test tri-level inheritance", test_inheritance); 
    CU_add_test(ps, "test clone and auto-construct superclass", test_clone); 

    CU_add_test(ps, "test native array ctor",  test_nativearray_ctordtor);
    CU_add_test(ps, "test 1-dim byte array",   test_nativearray_1x1x4);
    CU_add_test(ps, "test 1-dim int array",    test_nativearray_1x4x4);
    CU_add_test(ps, "test 1-dim struct array", test_nativearray_1xstruct);
    CU_add_test(ps, "test 2-dim byte array",   test_nativearray_2x1x4);
    CU_add_test(ps, "test 3-dim struct array", test_nativearray_3xstruct);
    CU_add_test(ps, "test static 2-dim byte array", test_arrayfrom_2x1x4);
    CU_add_test(ps, "test subarray",           test_subarray);
    CU_add_test(ps, "test get array element",  test_get_element);
    CU_add_test(ps, "test 3-dim int16 subarray ", test_if_busted_subarray);

    if (g_is_automated_test)    
        CU_automated_run_tests();    
    else
    {   CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
    }

    if (!g_is_automated_test) { printf("any key ..."); while(!c) c = _getch(); wprintf(L"\n"); }     
    CU_cleanup_registry();
    return CU_get_error(); 
}


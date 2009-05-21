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

/**
 * etch_arraylist.c -- implementation of arraylist.
 */

#include <stdio.h>
#include "etch_arraylist.h"
#include "etch_global.h"
#include "etchmutex.h"

int destroy_arraylist(etch_arraylist* list);



/**
 * new_arraylist()
 * constructor for an etch_arraylist, which implements i_iterable.
 * passed initial size, and initial expansion delta, both expressed as 
 * number of entries.
 */
etch_arraylist* new_arraylist(const unsigned initsize, const unsigned deltsize)
{
    etch_arraylist* list = (etch_arraylist*) new_object
        (sizeof(etch_arraylist), ETCHTYPEB_ARRAYLIST, CLASSID_ETCH_ARRAYLIST); 
   
    list->size  = initsize > 0? initsize: ETCHARRAYLIST_DEFSIZE;
    list->delta = deltsize > 0? deltsize: list->size;
    list->size *= sizeof(void**); list->delta *= sizeof(void**);
    list->base  = etch_malloc(list->size, ETCHTYPEB_BYTES);
    memset(list->base, 0, list->size);

    list->destroy = destroy_arraylist;

    new_iterable(&list->iterable, NULL, arraylist_iterable_first, 
        arraylist_iterable_next, arraylist_iterable_has_next); 

    return list;
}


/**
 * new_arraylist_from()
 */
etch_arraylist* new_arraylist_from(etch_arraylist* thatlist)
{
    etch_arraylist* thislist
     = new_arraylist(thatlist->size, thatlist->delta);

    arraylist_copyattrs(thislist, thatlist);

    memcpy(thislist->base, thatlist->base, thatlist->count * sizeof(void*));
    thislist->count = thatlist->count;

    return thislist;
}


/**
 * arraylist_destroy()
 * destructor for an etch_arraylist.
 * destroys the underlying list, the list shell, and the list content if requested.
 * note that arraylist always owns its buffer and mutex. setting static content on
 * an arraylist object applies only to the array content objects, if indeed content
 * consists of object. if content is other than object, static content has no effect
 * since the content buffer is freed regardless. 
 */
void arraylist_destroy(etch_arraylist* list, const int is_free_content) 
{    
  if (list->synchook) 
      if (0 != list->synchook(ETCH_SYNC_TRY, list->synclock))
          return;  /* disallow multiple destroy */

    if (list->refcount > 0)        /* if object is refcounted */                                     
        if (--list->refcount > 0) /* destroy only if last ref */
            return;   

    if (!is_etchobj_static_content(list)) /* clear and free content */
        arraylist_clear(list, is_free_content);

    etch_free(list->base);  /* arraylist always owns its buffer */

    if (list->synchook)    /* release and free mutex */
    {   list->synchook(ETCH_SYNC_REL, list->synclock);
        list->synchook(ETCH_SYNC_DEL, list->synclock);
    }

   if (!is_etchobj_static_shell(list))
       etch_free(list);    /* free list object */
}


int destroy_arraylist(etch_arraylist* list)
{
    arraylist_destroy(list, !list->is_readonly);
    return 0;
}



/* - - - - - - - - - - 
 * list maintenance
 * - - - - - - - - - - 
 */

/**
 * arraylist_realloc()
 * private method to resize an arraylist.
 * if a size greater than current size is specified, the list is realloced to that size,
 * otherwise it is realloced to current size plus the delta size specified at construction.
 * @note presumed that this is invoked only via arraylist_checksize, thus synchronized.
 */
int arraylist_realloc(etch_arraylist* list, const unsigned size)    
{
    unsigned int copylength = 0, newsize = 0;
    void* newbase = NULL;

    newsize = size > list->size? size: list->size + list->delta;
    newbase = etch_malloc(newsize, ETCHTYPEB_BYTES);
    memset(newbase, 0, newsize);

    copylength = list->count * sizeof(void**);
    memcpy(newbase, list->base, copylength); 

    etch_free(list->base);
    list->base = newbase;
    list->size = newsize;
    return 0;
}


/**
 * arraylist_checksize()
 * private method ensures list has space required for pending content insertion.
 */
int arraylist_checksize(etch_arraylist* list,
    const int pendingitems, const int is_locked)
{
    int result = 1;
    unsigned currsize = 0, newspace = pendingitems * sizeof(void**);

    if (list->synchook && !is_locked) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    currsize = list->count * sizeof(void**);

    if  (currsize + newspace > list->size)
         arraylist_realloc(list, newspace > list->delta? newspace: 0);
    else result = 0;

    if (list->synchook && !is_locked) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);

    return result;
}


/*
 * arraylist_clear() 
 * remove all content from the arraylist, freeing content memory only if requested. 
 * note that the list buffer does not shrink, rather retaining its current size.
 */
void arraylist_clear(etch_arraylist* list, const int is_free_content) 
{
    void** p = NULL;
    arraycallback callback = NULL;
    int items = 0, is_obj_content = 0, i = 0, freehandled = 0;
    if (NULL == list || NULL == list->base) return;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    is_obj_content = list->content_type == ETCHARRAYLIST_CONTENT_OBJECT;
    callback = list->freehook;
    items = list->count;
    p = list->base;

    if (is_free_content && !list->is_readonly)
        for(; i < (const int) items; i++, p++)
        {   
            /* optional callback to handle free */                                    
            freehandled = callback? callback(i, *p): FALSE; 

            /* if we've marked the array as having etch object content, 
             * we invoke the object's destructor. */
            if  (freehandled);
            else
            if  (is_obj_content)
                ((objmask*)*p)->destroy(*p);            
            else etch_free(*p);
        }

    memset(list->base, 0, items * sizeof(void**)); 
    list->count = 0;  

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);      
}


/* - - - - - - - - - - 
 * list api
 * - - - - - - - - - - 
 */

/*
 * arraylist_add_from() 
 * add entries to the end of the list.
 * returns count if items entered, or -1 if error.
 * note that if the target array is not marked read only, this method must be
 * used with great caution. since an arraylist not so marked will attempt to
 * destroy its content when destroyed, and since we are copying memory references
 * from one array to another here, the second destructor would attempt to free
 * memory already freed in the first destructor. so to be safe, this method 
 * should be used only with arrays marked is_readonly = TRUE, and content_type =
 * ETCHARRAYLIST_CONTENT_OBJECT.
 */
int arraylist_add_from(etch_arraylist* list, etch_arraylist* newitems, 
    etch_comparator compare) 
{
    int count = 0;
    etch_iterator iterator;
    if (!list || !list->base) return -1; 
    if (newitems->count == 0) return 0;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    set_iterator(&iterator, newitems, &newitems->iterable);

    while(iterator.has_next(&iterator))
    {
        if (arraylist_contains(list, iterator.current_value, 0, compare))
            continue;

        arraylist_checksize(list, 1, TRUE);  

        list->base[list->count++] = iterator.current_value;
        count++;

        iterator.next(&iterator); 
    }
 
    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);     

    return count;
}


/*
 * arraylist_add() 
 * add an entry to the end of the list.
 */
int arraylist_add(etch_arraylist* list, void* content) 
{
    if (!list || !list->base) return -1; 

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);
 
    arraylist_checksize(list, 1, TRUE);  

    list->base[list->count++] = content;

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);     

    return 0;
}


/*
 * arraylist_insert() 
 * add a node anywhere in the list, returning 0 if OK, or -1 if error.
 * this implementation cannot insert past the current end of list,
 * in other words to insert at index n, there must be at least n
 * entries currently in the list (list->count >= n), that is to say,
 * the insertion must expand the size of the list by exactly one slot.
 */
int arraylist_insert(etch_arraylist* list, const unsigned int i, void* content)
{
    unsigned shiftcount = 0, result = -1, j = 0;
    void **p = NULL, **q = NULL;
    if ((NULL == list) || (i < 0)) return -1;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    arraylist_checksize(list, 1, TRUE);

    if (i <= list->count)
    {
        shiftcount = list->count - i;  /* shift higher entries up */
        p = &list->base[list->count - 1];  
        q = &list->base[list->count];

        for(j = 0; j < (const unsigned) shiftcount; j++, p--, q--)
            *q = *p;
        
        list->base[i] = content;
        ++list->count;
        result = 0;
    }  

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);    

    return result;
}


/*
 * arraylist_containsp() 
 * return 1 or 0 indicating if the list contains the supplied content pointer.
 */
int arraylist_containsp(etch_arraylist* list, void* content, const unsigned startat)
{
    return arraylist_indexofp(list, content, startat) == -1? FALSE: TRUE;
}


/*
 * arraylist_indexofp() 
 * if the list contains the supplied content pointer, return its index;
 * return -1 if not found or if a parameter was in error.
 */
int arraylist_indexofp(etch_arraylist* list, void* content, const unsigned startat)
{
    void** p = NULL;
    int result = -1;
    unsigned int i = startat;
    if ((NULL == list) || (i < 0)) return result;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    if (i < list->count)
    {
        p = &list->base[i];

        for(; i < list->count; i++, p++)  
        {       
            if (*p == content) 
            {   result = i;
                break;
            }
        }
    }  

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);    
                 
    return result;
}


/*
 * arraylist_contains() 
 * return 1 or 0 indicating if the list contains the supplied content. 
 * caller must supply a comparator function int (*f)(void* this, void* that);  
 * which should return -2 bad params, -1 compares less, 0 equal, 1 greater. 
 */
int arraylist_contains(etch_arraylist* list, void* content, const unsigned startat,
    etch_comparator compare)
{
    return arraylist_indexof(list, content, startat, compare) == -1? FALSE: TRUE;
}


/*
 * arraylist_indexof() 
 * if the list contains the supplied content, return its index.
 * return -1 if a parameter was in error.
 * caller must supply a comparator function int (*f)(void* this, void* that); 
 * which should return -2 bad params, -1 compares less, 0 equal, 1 greater. 
 */
int arraylist_indexof(etch_arraylist* list, 
    void* content, const unsigned startat, etch_comparator compare)
{
    void** p   = NULL;
    unsigned i = startat;
    int result = -1;
    if ((NULL == list) || (i < 0)) return result;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    if (i < list->count)  
    {
        p = &list->base[i];

        for(; i < list->count; i++, p++)
        {  
            if (0 == compare(content, *p)) 
            {   result = i;
                break;
            }
        }
    }  

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);    
     
    return result;
}


/*
 * arraylist_set() 
 * replace content at specified index position.
 */
int arraylist_set (etch_arraylist* list, const unsigned i, void* content)
{
    int result = -1;
    if ((NULL == list) || (i < 0)) return -1;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    if (i < list->count)  
    {
        list->base[i] = content;
        result = 0;
    }

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);   

    return result;
}


/*
 * arraylist_get() 
 * return content at specified index position, or NULL if parameter error.
 * a non-disposable reference is returned. 
 * todo: mark arraylist content objects static, such that destroy() is benign,
 * unlocking them only at such time as the arraylist itself is cleared or 
 * destroyed, or a remove() with is_free_content is requested.
 */
void* arraylist_get (etch_arraylist* list, const unsigned i)
{
    void* result = NULL;
    if ((NULL == list) || (i < 0)) return NULL;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    if (i < list->count)  
        result = list->base[i];

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);  

    return result;
}


/*
 * arraylist_remove() 
 * remove entry at specified index position, freeing content memory if requested.
 * return -1 if a parameter was in error, or zero if OK.
 */
int arraylist_remove (etch_arraylist* list, const unsigned i, const int is_free_content)
{
    unsigned j = 0, newcount = 0, is_obj_content = 0, freehandled = 0, result = -1;
    arraycallback callback = NULL;
    void *content = NULL, **p = NULL, **q = NULL;
    if ((NULL == list) || (i < 0)) return -1;

    if (list->synchook) /* acquire lock */
        list->synchook(ETCH_SYNC_SET, list->synclock);

    if (i < list->count) 
    {
        is_obj_content = list->content_type == ETCHARRAYLIST_CONTENT_OBJECT;
        callback = list->freehook;
        
        if (is_free_content && !list->is_readonly)
        {
            if (content = list->base[i])
            {                                            
                freehandled = callback? callback(i, content): FALSE; 
                if  (freehandled);
                else
                if  (is_obj_content)
                    ((objmask*)content)->destroy(content);            
                else etch_free(content);
            }
        }
         
        newcount = list->count - 1;
        p = &list->base[i];      /* shift higher entries down */
        q = &list->base[i + 1];  /* we eschew platform-dependent memmove() */

        for(j = i; j < (const unsigned)newcount; j++, p++, q++)
            *p = *q;

        list->base[newcount] = NULL;  /* zero the now-extra slot */
        list->count = newcount;
        result = 0;
    }  

    if (list->synchook) /* release lock */
        list->synchook(ETCH_SYNC_REL, list->synclock);  

    return result;
}


/*
 * arraylist_remove_content() 
 * remove entry whose value is specified.
 */
int arraylist_remove_content(etch_arraylist* list, 
    void* content, const unsigned startat, etch_comparator compare)
{
    int result = -1, index = 0;
    if (NULL == list) return result;

    if (list->synchook)  
        list->synchook(ETCH_SYNC_SET, list->synclock);

    if (-1 != (index = arraylist_indexof(list, content, startat, compare)))     
        result = arraylist_remove(list, index, TRUE);  
     
    if (list->synchook)  
        list->synchook(ETCH_SYNC_REL, list->synclock);   

    return result; 
}


/* 
 * arraylist_copyattrs()
 * copy array attributes from one array to another
 */
void arraylist_copyattrs(etch_arraylist* to, etch_arraylist* from)
{
    to->class_id         = from->class_id;
    to->content_obj_type = from->content_obj_type;
    to->content_class_id = from->content_class_id; 
    to->is_static        = from->is_static;
    to->content_type     = from->content_type;
    to->is_readonly      = from->is_readonly;
    to->freehook         = from->freehook;
}


/* - - - - - - - - - - 
 * iteration lock
 * - - - - - - - - - - 
 */

/* 
 * arraylist_getlock()
 * explicitly set this list's synchronization lock, waiting if unavailable.
 * this should be used only for locking a list prior to iterating the list.   
 * for synchronization of list operations, the presence of list.synchook  
 * and list.synclock is sufficient. 
 */
int arraylist_getlock (etch_arraylist* list)
{
    ETCH_ASSERT(list && list->synchook && list->synclock);
    return list->synchook (ETCH_SYNC_SET, list->synclock);
}


/* 
 * arraylist_trylock()
 * explicitly set this list's synchronization lock, failing if unavailable.
 * this should be used only for locking a list prior to iterating the list.   
 * for synchronization of list operations, the presence of list.synchook  
 * and list.synclock is sufficient. 
 */
int arraylist_trylock (etch_arraylist* list)
{
    ETCH_ASSERT(list && list->synchook && list->synclock);
    return list->synchook (ETCH_SYNC_TRY, list->synclock);
}

 
/* 
 * arraylist_rellock()
 * release explicitly set this list's synchronization lock.
 * this should be used only for unlocking a list after iterating the list.   
 * for synchronization of list operations, the presence of list.synchook  
 * and list.synclock is sufficient. 
 */
int arraylist_rellock (etch_arraylist* list) 
{
    ETCH_ASSERT(list && list->synchook && list->synclock);
    return list->synchook (ETCH_SYNC_REL, list->synclock);
}


/* - - - - - - - - - - 
 * i_iterable
 * - - - - - - - - - - 
 */

/*
 * arraylist_iterable_first() 
 * i_iterable first() implementation
 */
int arraylist_iterable_first(etch_iterator* iter)
{
    etch_arraylist* list = NULL;
    if (!iter || !iter->collection)  return -1;
    list = iter->collection;
    if (!list->base || !list->count) return -1;

    iter->current_value = arraylist_get(list, 0);   
    iter->ordinal = iter->current_value? 1: 0;
    return iter->ordinal? 0: -1;
}


/*
 * arraylist_iterable_next() 
 * i_iterable next() implementation
 * functions as first() if there is no current position.
 */
int arraylist_iterable_next(etch_iterator* iter)
{
    etch_arraylist* list = iter? iter->collection: NULL;
    const int count = list? list->count: 0;
    if (!count || !iter->ordinal) return -1;
    
    iter->current_value = arraylist_get(list, iter->ordinal); 
    iter->ordinal = iter->current_value? ++iter->ordinal: 0;
    return iter->ordinal? 0: -1;
}


/*
 * arraylist_iterable_has_next() 
 * i_iterable has_next() implementation.
 */
int arraylist_iterable_has_next(etch_iterator* iter)
{
    etch_arraylist* list = iter? iter->collection: NULL;
    const int count = list? list->count: 0;
    return count && iter->ordinal && (iter->ordinal <= count);
}


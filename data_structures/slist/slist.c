/* 
* File Name: slist.c
* Description: Definitions of slist API functions
* Developer: Guy Chen
* Date: 11.06.2020
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "slist.h"



struct slist
{
	struct slist_node *head;
    struct slist_node *tail;
};

struct slist_node
{
    void *data;
    struct slist_node *next;
};
/******************************************************************************/

slist_t *SListCreate(void)
{
	
	slist_iter_t dummy = NULL;
	slist_t *slist_new = (slist_t *)malloc(sizeof(slist_t));
	if (NULL == slist_new)
	{
		return (NULL);
	}
	
	dummy = (slist_iter_t)malloc(sizeof(struct slist_node));
	if (NULL == dummy)
	{
		free(slist_new);
		return (NULL);
	}
		
	dummy->data = NULL;
	dummy->next = NULL;
	
	slist_new->tail = dummy;
	slist_new->head = SListEnd(slist_new);
	
	return (slist_new);
}

/******************************************************************************/

void SListDestroy(slist_t *slist)
{
	slist_iter_t next_temp = NULL;
	assert(slist);
	
	while(!SListIterIsEqual(SListBegin(slist), SListEnd(slist)))
	{
		next_temp = SListNext(slist->head);
		free(SListBegin(slist));
		slist->head = next_temp;
	}
	
	free(SListBegin(slist));
	slist->head = NULL;
	slist->tail = NULL;
	free(slist);
	slist = NULL;
}

/******************************************************************************/

slist_iter_t SListBegin(const slist_t *slist)
{
	assert(slist);
	
	return (slist->head);
}

/******************************************************************************/

slist_iter_t SListEnd(const slist_t *slist)
{
	assert(slist);
	
	return (slist->tail);
}

/******************************************************************************/

slist_iter_t SListNext(const slist_iter_t iter)
{
	assert(iter);
	
	return (iter->next);
}
/******************************************************************************/

void *SListGetData(const slist_iter_t iter)
{
	assert(iter);
	
	return (iter->data);
}
/******************************************************************************/

void SListSetData(slist_iter_t iter, void *data)
{
	assert(iter);
	
	iter->data = data;
}

/******************************************************************************/

int SListIterIsEqual(const slist_iter_t iter1, const slist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

/******************************************************************************/

int SListIsEmpty(const slist_t *slist)
{
	assert(slist);
	
	return (SListIterIsEqual(SListBegin(slist), SListEnd(slist)));
}

/******************************************************************************/

slist_iter_t SListInsert(slist_t *slist, slist_iter_t where, void *data)
{
	slist_iter_t new_node = NULL;
	
	assert(slist);
	assert(where);
	
	new_node = (slist_iter_t)malloc(sizeof(struct slist_node));
	if (NULL == new_node)
	{
		return (SListEnd(slist));
	}
	
	new_node->data = SListGetData(where);
	new_node->next = SListNext(where);
		
	where->data = data;
	where->next = new_node;
	
	if (SListEnd(slist) == where)
	{
		slist->tail = new_node;
	}
	
	if (SListIsEmpty(slist))
	{
		slist->head = where;
		slist->tail = new_node;
	}
	
	return (where);
}

/******************************************************************************/

slist_iter_t SListInsertAfter(slist_t *slist, slist_iter_t where, void *data)
{
	slist_iter_t new_node = NULL;
	
	assert(slist);
	assert(where);

	new_node = (slist_iter_t)malloc(sizeof(struct slist_node));
	if (NULL == new_node)
	{
		return (SListEnd(slist));
	}
	
	SListSetData(new_node, data);
	new_node->next = SListNext(where);
	where->next = new_node;
	
	return (new_node);
} 

/******************************************************************************/

slist_iter_t SListRemove(slist_t *slist, slist_iter_t iter)
{
    slist_iter_t temp_iter = NULL;
    
    assert(slist);
    assert(iter);
    
    temp_iter = SListNext(iter);
    SListSetData(iter->next, SListGetData(iter));
    iter->next = SListNext(temp_iter);

    if (NULL == SListNext(iter))
    {
        slist->tail = iter;
    }
    
    free(temp_iter);

    return(iter);  
}

/******************************************************************************/

size_t SListCount(const slist_t *slist)
{
	size_t slist_size = 0;
	slist_iter_t curr = NULL;
	
	assert(slist);

	/* for each */
	/* SListForEach(SListBegin(list), SListEnd(slist), CountFunc, &counter); */
	
	curr = SListBegin(slist);
	while (SListNext(curr))
	{
		++slist_size;
		curr = SListNext(curr);
	}
	
	return (slist_size);
}

/******************************************************************************/

slist_iter_t SListFind(const slist_iter_t from, 
                       const slist_iter_t to,
					   slist_is_match_func_t is_match, 
                       void *param)
{
	slist_iter_t temp_iter = NULL;
	
	assert(from);
	assert(to);
	assert(is_match);

	temp_iter = from;
	while (!SListIterIsEqual(temp_iter, to))
	{
		if(is_match(temp_iter->data, param))
		{
			return (temp_iter);
		}
		temp_iter = SListNext(temp_iter);
	}
	
	return (to);
}
/******************************************************************************/

int SListForEach(const slist_iter_t from, 
                       const slist_iter_t to,
					   slist_do_action_func_t do_action,
                       void *param)
{
	int is_succeeded = 0;
	slist_iter_t temp_iter = NULL;
	
	assert(from);
	assert(to);
	assert(do_action);

	temp_iter = from;
	while (!SListIterIsEqual(temp_iter, to) || !is_succeeded)
	{
		is_succeeded = do_action(temp_iter->data, param);
		temp_iter = SListNext(temp_iter);
	}
	
	return (is_succeeded);
}

/******************************************************************************/

void SListAppend(slist_t *dest, slist_t *src)
{
/*
	assert(dest);
    assert(src);

    dest->tail->data = SListGetData(SListBegin(src));
    dest->tail->next = SListNext(SListBegin(src));

    dest->tail = SListEnd(src);

    src->head->data = SListGetData(SListEnd(src));
    src->head->next = NULL;

    src->tail = NULL;
    */
	slist_iter_t dest_curr = NULL;

	assert(dest);
	assert(src);

	dest_curr = dest->head;
	
	if (0 == SListIsEmpty(src))
	{
		dest->tail->data = SListGetData(SListBegin(src));
    	dest->tail->next = SListNext(SListBegin(src));
    	dest->tail = SListEnd(src);
	}
	src->head->next = NULL;
	src->tail = src->head;
	
	while (dest_curr->next)
    {
        printf("%p \n", dest_curr->data);
        dest_curr = dest_curr->next;
    }
}


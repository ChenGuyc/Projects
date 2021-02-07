/* 
* File Name: dlist.c
* Description: Definition functions of dlist API functions
* Developer: Guy Chen
* Date: 19.06.2020
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc , free */
#include "dlist.h"

/*****************************************************************************/

#define TRUE 1
#define FALSE 0
#define INVALID_ADDRESS (void*)0xFEE1DEAD


enum DO_ACTION_STATUS
{
	SUCCESS = 0,
	FAILURE
};


/*****************************************************************************/

struct dlist
{
	struct dlist_node *head; /* dummy at the beginning*/
    struct dlist_node *tail; /* dummy at the end*/
};


struct dlist_node
{
    void *data;
    struct dlist_node *next;
    struct dlist_node *prev;	
};

/* Decleration of utility function */
static dlist_iter_t CreateNewNode(void);

/*****************************************************************************/

dlist_t *DListCreate(void)
{
	dlist_t *dlist = NULL;
	

	dlist = (dlist_t*)malloc(sizeof(struct dlist));
	if (NULL == dlist)
	{
		return (NULL);
	}
	/* set the tail dummy */	
	dlist->tail = CreateNewNode();
	if (NULL == dlist->tail)
	{
		free (dlist);
		dlist = NULL;
		return (NULL);
	}
	/* set the head dummy */
	dlist->head = CreateNewNode();
	if (NULL == dlist->head)
	{
		free (dlist->tail);	
		dlist->tail = NULL;		
		free (dlist);
		dlist = NULL;
		return (NULL);
	}
	
	/*set Attributes */
	dlist->tail->data = INVALID_ADDRESS;
	dlist->tail->next = NULL;
	dlist->tail->prev = dlist->head;
	dlist->head->data = INVALID_ADDRESS;
	dlist->head->next = dlist->tail;	
	dlist->head->prev = NULL;

	return (dlist);
}

/*****************************************************************************/

void DListDestroy(dlist_t *dlist)
{
	dlist_iter_t curr_iter = NULL;
	assert (dlist);	

	curr_iter = dlist->head;
	while(NULL != curr_iter->next)
	{
	
		curr_iter = curr_iter->next;
		free(curr_iter->prev);		
		curr_iter->prev = NULL;		
		
	}
	free(curr_iter);
	curr_iter = NULL;
	free(dlist);
	dlist = NULL;
}

/*****************************************************************************/ 

dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert (dlist);
	return (DListNext(dlist->head));
}

/*****************************************************************************/ 

dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(dlist);
	return (dlist->tail);
}

/*****************************************************************************/ 

dlist_iter_t DListNext(const dlist_iter_t iter)
{
	assert(iter);

	return (iter->next);
}

/*****************************************************************************/ 

dlist_iter_t DListPrev(const dlist_iter_t iter)
{
	assert(iter);

	return (iter->prev);
}

/*****************************************************************************/ 

void *DListGetData(const dlist_iter_t iter)
{
	assert(iter);	

	return (iter->data);
}

/*****************************************************************************/ 

void DListSetData(dlist_iter_t iter, void *data)
{
	assert(iter);

	iter->data = data;
}

/*****************************************************************************/ 
int DListIterIsEqual(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);

	return (iter1 == iter2);
}

/*****************************************************************************/ 

int DListIsEmpty(const dlist_t *dlist)
{
	assert (dlist);

	return (DListIterIsEqual(DListBegin(dlist), DListEnd(dlist)));
}

/*****************************************************************************/ 

dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t where, void *data)
{
	dlist_iter_t new_element = NULL;
	
	assert (dlist);		
	assert(where);	

	new_element = CreateNewNode();
	if(NULL == new_element)
	{
		return (DListEnd(dlist));
	}
	/*set the atrributes for the new node */
	DListSetData(new_element, data);
	new_element->prev = DListPrev(where);	
	(DListPrev(where))->next = new_element;	
	new_element->next = where;
	where->prev = new_element; 	
	

	return (new_element);
}

/*****************************************************************************/ 

size_t DListSize(const dlist_t *dlist)
{
	size_t counter = 0;
	dlist_iter_t curr_iter = NULL;

	assert (dlist);
	
	curr_iter = DListBegin(dlist);	
	while(curr_iter != DListEnd(dlist))
	{
		++counter;
		curr_iter = DListNext(curr_iter);
	}
	
	return (counter);
}

/*****************************************************************************/ 

dlist_iter_t DListRemove(dlist_iter_t iter)
{

    dlist_iter_t temp = NULL;
    assert(iter);

   	(DListPrev(iter))->next = DListNext(iter);
    DListNext(iter)->prev = DListPrev(iter);

    temp = iter;
    iter = DListNext(iter);

    free(temp);
    temp = NULL;

    return (iter);
}

/*****************************************************************************/ 
dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	dlist_iter_t where = NULL;	

	assert (dlist);

	where = DListBegin(dlist);	
	
	return (DListInsert(dlist,where,data));
}

/*****************************************************************************/

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	dlist_iter_t where = NULL;	
	
	assert (dlist);

	where = DListEnd(dlist);	
	return (DListInsert(dlist,where,data));
}

/*****************************************************************************/

void *DListPopFront(dlist_t *dlist)
{
	void *curr_iter_data = NULL;
	dlist_iter_t curr_iter = DListBegin(dlist);

	assert (dlist);
		
	curr_iter_data = DListGetData(curr_iter);
	DListRemove(curr_iter);
	
	return (curr_iter_data);
}

/*****************************************************************************/

void *DListPopBack(dlist_t *dlist)
{
	void *curr_iter_data = NULL;
	dlist_iter_t curr_iter = (DListEnd(dlist))->prev;	

	assert (dlist);
			
	curr_iter_data = DListGetData(curr_iter);
	DListRemove(curr_iter);
	
	return (curr_iter_data);
}
	
/*****************************************************************************/

dlist_iter_t DListFind(const dlist_iter_t from, const dlist_iter_t to,
					   dlist_is_match_func_t is_match, void *param)
{
	dlist_iter_t temp = from;
	void *iter_data = NULL;
	
	assert(from);	
	assert(to);

	iter_data = DListGetData(temp);	
	while(temp != to)
	{
		if (is_match(iter_data, param))
		{
			return (temp);
		}
		temp = DListNext(temp);
		iter_data = DListGetData(temp);	
	}
	return (to);
}

/*****************************************************************************/	

int DListForEach(dlist_iter_t from, const dlist_iter_t to, 
				 dlist_do_action_func_t do_action, void *param)
{
	dlist_iter_t temp = from;
	void *iter_data = NULL;
	int do_action_res = 0;
	
	assert(from);	
	assert(to);

	iter_data = DListGetData(temp);	
	while(temp != to)
	{
		do_action_res = do_action(iter_data, param);
		if (do_action_res)
		{
			return (do_action_res);
		}
		temp = DListNext(temp);
		iter_data = DListGetData(temp);	
	}	
	return (SUCCESS);
}	

/*****************************************************************************/

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_iter_t prev_where = DListPrev(where);
	dlist_iter_t prev_from = DListPrev(from);
	dlist_iter_t prev_to = DListPrev(to);	
	
	assert(from);	
	assert(to);
	assert(where);

	prev_from->next = to;
	to->prev = prev_from;

	from->prev = prev_where;
	prev_where->next = from;

	where->prev = prev_to;
	prev_to->next = where;
		
	return (prev_to); 
}

/*****************************************************************************/

/* Utility Function to create Nodes */

static dlist_iter_t CreateNewNode(void)
{
	dlist_iter_t new_node = NULL;
	
	new_node = (dlist_iter_t)malloc(sizeof (struct dlist_node));

	return(new_node);
}














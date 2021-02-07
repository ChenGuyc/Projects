/* 
* File Name:queue.c
* Description: Defenition of functions for queue DS
* Developer: Guy Chen
* Date: 15.06.2020
*/


#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include "slist.h"

enum API_STATUS
{
	SUCCESS = 0,
	FAILURE
};


struct queue
{
    slist_t *slist;
};

/*****************************************************************************/

queue_t *QCreate(void)
{
	queue_t *queue_ptr = NULL;
	
	queue_ptr = (queue_t*)malloc(sizeof(queue_t));	
	if (NULL == queue_ptr)
	{
		return (NULL);
	}
	queue_ptr->slist = SListCreate();
	if (NULL == queue_ptr->slist)
	{
		free (queue_ptr);
		queue_ptr = NULL;
		return (NULL);
	}	

	return (queue_ptr);
}

/*****************************************************************************/

void QDestroy(queue_t *queue)
{
	assert (queue);
    SListDestroy(queue->slist);
    queue->slist = NULL;
    free (queue);
    queue = NULL;
}

/*****************************************************************************/

size_t QSize(const queue_t *queue)
{
	size_t counter = 0;

	assert (queue);
	counter = SListCount(queue->slist);
	
	return (counter);
}

/*****************************************************************************/

int QIsEmpty(const queue_t *queue)
{
	assert (queue);
	return (SListIsEmpty(queue->slist));
}

/*****************************************************************************/

int QEnqueue(queue_t *queue, void *data)
{
	
	assert (queue);
	if (QIsEmpty(queue))
	{
		if (NULL == SListInsert(queue->slist, SListEnd(queue->slist), data))
		{	
			return (FAILURE);	
		}
	}
	if (NULL == SListInsertAfter(queue->slist, SListBegin(queue->slist), data))
	{	
	 	return (FAILURE);	
	}
	return (SUCCESS);	
}

/*****************************************************************************/

void *QPeek(const queue_t *queue)
{
	return (SListBegin(queue->slist));
}

/*****************************************************************************/

void QDequeue(queue_t *queue)
{
	assert (queue);
	
	SListRemove(queue->slist,SListBegin(queue->slist));
}

/*****************************************************************************/

void QAppend(queue_t *dest, queue_t *src)
{
	SListAppend(dest->slist, src->slist);
}

/*****************************************************************************/









































/* 
* File Name: pqueue.c
* Description: Definition pqueue API functions
* Developer: Guy Chen
* Date: 28.06.2020
*/

#include <stddef.h>	/* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h>
#include "heap.h"
#include "pqueue.h"

struct pqueue
{
	void *param;
    heap_t *heap;
	pqueue_cmp_func_t compare;
};

/*---------------------------------------------------------------------------*/

pqueue_t *PQCreate(pqueue_cmp_func_t cmpare, void *param)
{
    pqueue_t *pq = (pqueue_t *) malloc(sizeof(pqueue_t));
	if (pq)
	{
		pq->heap = HeapCreate(cmpare, param);
		if(pq->heap)
		{
			pq->compare= cmpare;
			pq->param = param;
		}
		else
		{
			free(pq);
			pq = NULL;
		}	
	}
	return (pq);
}

/*---------------------------------------------------------------------------*/

void PQDestroy(pqueue_t *pqueue)
{
    assert(pqueue);

	HeapDestroy(pqueue->heap);

	free(pqueue);

	pqueue = NULL; 
}

/*---------------------------------------------------------------------------*/

size_t PQSize(const pqueue_t *pqueue)
{
    assert(pqueue);
    return (HeapSize(pqueue->heap));
}

/*---------------------------------------------------------------------------*/

int PQIsEmpty(const pqueue_t *pqueue)
{
    assert(pqueue);
    return (HeapIsEmpty(pqueue->heap));
}

/*---------------------------------------------------------------------------*/

int PQEnqueue(pqueue_t *pqueue, void *data)
{
    assert(pqueue);
    return (HeapPush(pqueue->heap, data));
}

/*---------------------------------------------------------------------------*/

void *PQDequeue(pqueue_t *pqueue)
{
    assert(pqueue);
    return (HeapPop(pqueue->heap));
}

/*---------------------------------------------------------------------------*/

void *PQPeek(const pqueue_t *pqueue)
{
    assert(pqueue);
    return (HeapPeek(pqueue->heap));
}

/*---------------------------------------------------------------------------*/

void PQClear(pqueue_t *pqueue)
{
    assert(pqueue);

    while(!PQIsEmpty(pqueue))
    {
        HeapPop(pqueue->heap);
    }
}

/*---------------------------------------------------------------------------*/

void *PQErase(pqueue_t *pqueue, void *data, pqueue_is_match_func_t is_match, void *param)
{
    return (HeapRemove(pqueue->heap, data, is_match, param));
}


/*---------------------------------------------------------------------------*/


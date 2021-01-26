/* 
* File Name: heap.c
* Description: Definition of heap API functions
* Developer: Guy Chen
* Date: 28.06.2020
*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "heap.h"
#include "heapify.h"
#include "vector.h"

struct heap
{
    vector_t *vector;
    heap_cmp_func_t cmp;
    void *param;
};

enum exit_status
{
    success, fail
};

/******************************************************************************/

heap_t* HeapCreate(heap_cmp_func_t cmp, void *param)
{
    heap_t *heap = NULL;

    heap = (heap_t *)malloc(sizeof(heap_t));

    if(NULL == heap)
    {
        return (NULL);
    }

    heap->vector = VectorCreate(10);

    if(NULL == heap->vector)
    {
        free(heap);

        return (NULL);
    }

    heap->cmp = cmp;
    heap->param = param;

    return(heap);
}

/******************************************************************************/

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    VectorDestroy(heap->vector);

    heap->vector = NULL;

    free(heap);

    heap = NULL;
}

/******************************************************************************/

int HeapPush(heap_t *heap, void *data)
{
    if(VectorPushBack(heap->vector, data))
    {
        return (fail);
    }

    else
    {
        HeapifyUp(VectorGetArr(heap->vector), VectorSize(heap->vector), VectorSize(heap->vector) - 1, sizeof(void *), heap->cmp, heap->param);
    }
    
    return (success);
}

/******************************************************************************/

void *HeapPeek(heap_t *heap)
{
    assert(heap);

    if(VectorSize(heap->vector) == 0)
    {
        return (NULL);
    }

    else
    {
        return (VectorGetElement((heap->vector), 0));
    }
}

/******************************************************************************/

size_t HeapSize(heap_t *heap)
{
    assert(heap);

    return (VectorSize(heap->vector));
}

/******************************************************************************/

int HeapIsEmpty(heap_t *heap)
{
    assert(heap);

    if(HeapSize(heap) == 0)
    {
        return (1);
    }

    return (0);
}

/******************************************************************************/

void *HeapPop(heap_t *heap)
{
    void *result = NULL;

    assert(heap);

    result = HeapPeek(heap);

    VectorSetElement(heap->vector, 0, VectorGetElement(heap->vector, HeapSize(heap) - 1));

    VectorPopBack(heap->vector);

    HeapifyDown(VectorGetArr(heap->vector), HeapSize(heap), 0, sizeof(void *), heap->cmp, heap->param);

    return (result);
}

/******************************************************************************/

void *HeapRemove(heap_t *heap, void *data, heap_is_match_func_t is_match, void *param)
{
    size_t i = 0;
    void *result = NULL;
    size_t heap_size = HeapSize(heap);

    assert(heap);

    for(i = 0; i < heap_size; ++i)
    {
        if(is_match(data, VectorGetElement(heap->vector, i), param))
        {
            result = VectorGetElement(heap->vector, i);
            VectorSetElement(heap->vector, i, VectorGetElement(heap->vector, HeapSize(heap) - 1));
            VectorPopBack(heap->vector);
            HeapifyDown(VectorGetArr(heap->vector), HeapSize(heap), i, sizeof(void *), heap->cmp, heap->param);
            
            break;
        }
    }

    return (result);
}

/******************************User Functions**********************************/

void PrintIntVector(heap_t *heap)
{
    size_t i = 0;

    printf("\nElements are:\n");

    for(i = 0; i < VectorSize(heap->vector); ++i)
    {
        printf("%d, ", *(int *)VectorGetElement(heap->vector, i));
    }

    printf("\n");
}

/******************************************************************************/

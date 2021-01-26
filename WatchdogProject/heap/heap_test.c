/* 
* File Name: heap_test.c
* Description: Definition of test functions for heap API functions
* Developer: Guy Chen
* Date: 28.06.2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"
#include "heapify.h"
#include "heap.h"

/****************************user functions************************************/

int IntCompareWithPtr(const void *data1, const void *data2, void *param);
int IntCompare(const void *data1, const void *data2, void *param);
void PrintIntVectorTest(heap_t *heap);
int IsMatch(const void *data1, const void *data2, void *param);
void HeapSort(void *base, size_t nmemb, size_t size, heap_cmp_func_t cmp, 
               void *arg);

/*******************************Test Functions*********************************/

heap_t* HeapCreateTest(heap_cmp_func_t cmp, void *param);
void HeapDestroyTest(heap_t *heap);
void HeapPushTest(heap_t *heap, void *data);
void HeapPeekTest(heap_t *heap);
void HeapSizeTest(heap_t *heap);
void HeapIsEmptyTest(heap_t *heap);
void HeapPopTest(heap_t *heap);
void HeapRemoveTest(heap_t *heap, void *data, heap_is_match_func_t is_match, void *param);

/********************************Test Case*************************************/

void TestCase(void);
void HeapSortTestCase(void);

/**********************************main****************************************/

int main(void)
{
    printf("-------------------------------------------------\n");
    TestCase();
    printf("-------------------------------------------------\n");
    HeapSortTestCase();
    printf("-------------------------------------------------\n");

    return (0);
}

/**********************User Functions Implementations**************************/

int IntCompareWithPtr(const void *data1, const void *data2, void *param)
{
	assert(data1);
	assert(data2);

	(void)param;

	if(**(int **)data1 < **(int **)data2)
	{
		return (-1);
	}

	if(**(int **)data1 == **(int **)data2)
	{
		return (0);
	}

	return (1);
}

/***********************************************************/

int IntCompare(const void *data1, const void *data2, void *param)
{
	assert(data1);
	assert(data2);

	(void)param;

	if(*(int *)data1 < *(int *)data2)
	{
		return (-1);
	}

	if(*(int *)data1 == *(int *)data2)
	{
		return (0);
	}

	return (1);
}

/***********************************************************/

int IsMatch(const void *data1, const void *data2, void *param)
{
    (void)param;

	return (*(int *)data1 == *(int *)data2);
}

/**********************Test Functions Implementations**************************/

heap_t* HeapCreateTest(heap_cmp_func_t cmp, void *param)
{
    heap_t *heap = NULL;

    heap = HeapCreate(cmp, param);

    if (heap)
    {
        printf("Create was successed.\n");
    }

    else
    {
        printf("Create was failed.\n");
    }
    
    return (heap);
}

/***********************************************************/

void HeapDestroyTest(heap_t *heap)
{
    HeapDestroy(heap);

    printf("Heap was desroyed.\n");
}

/***********************************************************/

void HeapPushTest(heap_t *heap, void *data)
{
    if(!HeapPush(heap, data))
    {
        printf("%d was pushed successfully.\n", *(int *)data);
    }

    else
    {
        printf("%d was not pushed successfully.\n", *(int *)data);
    }
}

/***********************************************************/

void HeapPeekTest(heap_t *heap)
{
    printf("The top element in the array is: %d\n", *(int *)HeapPeek(heap));
}

/***********************************************************/

void PrintIntVectorTest(heap_t *heap)
{
    PrintIntVector(heap);
}

/***********************************************************/

void HeapSizeTest(heap_t *heap)
{
    printf("No. of elements in the heap is: %ld\n", HeapSize(heap));
}

/***********************************************************/

void HeapIsEmptyTest(heap_t *heap)
{
    if(HeapIsEmpty(heap))
    {
        printf("Heap is Empty.\n");
    }

    else
    {
        printf("Heap is not Empty.\n");
    } 
}

/***********************************************************/

void HeapPopTest(heap_t *heap)
{
    printf("Pop Test: the root was: %d", *(int *)HeapPop(heap));
}

/***********************************************************/

void HeapRemoveTest(heap_t *heap, void *data, heap_is_match_func_t is_match, void *param)
{
    int num = *(int *)HeapRemove(heap, data, is_match, param);

    printf("%d was removed from the heap.\n", num);
}

/***************************Test Case Implemenation****************************/

void TestCase(void)
{
    heap_t *heap = NULL;
    int num1 = 30;
    int num2 = 21;
    int num3 = 29;
    int num4 = 15;
    int num5 = 35;

    int *num1_ptr = &num1;
    int *num2_ptr = &num2;
    int *num3_ptr = &num3;
    int *num4_ptr = &num4;
    int *num5_ptr = &num5;
    
    heap = HeapCreateTest(IntCompareWithPtr, NULL);
    HeapIsEmptyTest(heap);
    HeapSizeTest(heap);

    HeapPushTest(heap, num5_ptr);
    HeapPushTest(heap, num4_ptr);
    HeapPushTest(heap, num3_ptr);
    HeapPushTest(heap, num2_ptr);
    HeapPushTest(heap, num1_ptr);

    HeapIsEmptyTest(heap);
    HeapSizeTest(heap);
    PrintIntVectorTest(heap);

    HeapPeekTest(heap);   
    HeapPopTest(heap);
    PrintIntVectorTest(heap);

    HeapRemoveTest(heap, num3_ptr, IsMatch, NULL);
    PrintIntVectorTest(heap);

    HeapDestroyTest(heap);
}

/******************************************************************************/

void HeapSortTestCase(void)
{
    /*int arr[10] = {3,19,5,8,4,2,1,6,9,10};
    int len = 10;*/

    int arr[15] = {30,21,29,15,35,3,19,5,8,4,2,1,6,9,10};
    int len = 15;

    int i = 0;

    printf("Heap Sort:\n");

    for(i = 0; i < len; ++i)
    {
        printf("%d, ", arr[i]);
    }

    printf("\n\n");

    HeapSort(arr, len, sizeof(int), IntCompare, NULL);

    printf("After heap Sort:\n");

    for(i = 0; i < len; ++i)
    {
        printf("%d, ", arr[i]);
    }

    printf("\n");
}

/******************************************************************************/

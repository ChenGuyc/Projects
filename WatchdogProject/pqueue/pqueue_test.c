/* 
* File Name: pqueue_test.c
* Description: Definition of test functions for pqueue API functions
* Developer: Guy Chen
* Date: 28.06.2020
*/

#include <stdio.h>  /* printf */
#include "pqueue.h"


int PQCmp(const void *data1, const void *data2, void *param);
int IsMatch(const void *data1, const void *data2, void *param);
static void TestPQCreateDstroy(void);
static void TestPQSize(void);
static void TestPQIsEmpty(void);
static void TestPQEnqueue(void);
static void TestPQPeek(void);
static void TestPQDequeue(void);
static void TestPQClear(void);
static void TestPQErase(void);


int main()
{
	printf("******* Test 1: Create and destroy PQ *******\n");
	TestPQCreateDstroy();
	printf("\n******* Test 2: Size of PQ (empty) *******\n");
	TestPQSize();
	printf("\n******* Test 3: Is PQ empty *******\n");
	TestPQIsEmpty();
	printf("\n******* Test 4: Enqueue *******\n");
	TestPQEnqueue();
	printf("\n******* Test 5: Peek *******\n");
	TestPQPeek();
	printf("\n******* Test 6: Dequeue *******\n");
	TestPQDequeue();
	printf("\n******* Test 7: Clear PQ *******\n");
	TestPQClear();
	printf("\n******* Test 8: Erase from PQ *******\n");
	TestPQErase();
	
	return 0;
}


static void TestPQCreateDstroy(void)
{
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);
	if(new_pqueue)
	{
		printf("pqueue created successfuly\n");
	}

	PQDestroy(new_pqueue);
}


static void TestPQSize(void)
{
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);
	printf("Size of PQ: %ld\n", PQSize(new_pqueue));

	PQDestroy(new_pqueue);
}


static void TestPQIsEmpty(void)
{
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);
	printf("Is PQ Empty: %d\n", PQIsEmpty(new_pqueue));

	PQDestroy(new_pqueue);
}


static void TestPQEnqueue(void)
{
	int element1 = 44;
	
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);

	printf("Was Enqueue successful: %d\n", PQEnqueue(new_pqueue, &element1));
	PQDestroy(new_pqueue);
}


static void TestPQPeek(void)
{
	int element1 = 10;
	int element2 = 5;
	
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);

	printf("Is first Enqueue successful (element = 10): %d\n", 
								PQEnqueue(new_pqueue, &element1));
	printf("Is second Enqueue successful (element = 5): %d\n", 
									PQEnqueue(new_pqueue, &element2));

	printf("Peak: %d\n", *(int *)PQPeek(new_pqueue));

	PQDestroy(new_pqueue);
}


static void TestPQDequeue(void)
{
	int element1 = 200;
	int element2 = 100;
	
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);

	printf("Is first Enqueue successful (element = 200): %d\n", 
								PQEnqueue(new_pqueue, &element1));
	printf("Is second Enqueue successful (element = 100): %d\n", 
									PQEnqueue(new_pqueue, &element2));

	printf("Peak: %d\n", *(int *)PQPeek(new_pqueue));

	printf("Dequeue: %d\n", *(int *)PQDequeue(new_pqueue));

	printf("Peak: %d\n", *(int *)PQPeek(new_pqueue));

	PQDestroy(new_pqueue);
}


static void TestPQClear(void)
{
	int element1 = 3;
	int element2 = 2;
	int element3 = 1;
	
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);

	printf("Is first Enqueue successful: %d\n", 
								PQEnqueue(new_pqueue, &element1));
	printf("Is second Enqueue successful: %d\n", 
									PQEnqueue(new_pqueue, &element2));
	printf("Is third Enqueue successful: %d\n", 
									PQEnqueue(new_pqueue, &element3));
	printf("Size of PQ: %ld\n", PQSize(new_pqueue));
	
	PQClear(new_pqueue);

	printf("Size of PQ after clear: %ld\n", PQSize(new_pqueue));

	PQDestroy(new_pqueue);
}


static void TestPQErase(void)
{
	int element1 = 97;
	int element2 = 485;
	int element3 = 66;
	int to_remove = 97;
	
	pqueue_t *new_pqueue = PQCreate(PQCmp, NULL);

	printf("Is first Enqueue successful (element = 97): %d\n", 
								PQEnqueue(new_pqueue, &element1));
	printf("Is second Enqueue successful (element = 485): %d\n", 
									PQEnqueue(new_pqueue, &element2));
	printf("Is third Enqueue successful (element = 66): %d\n", 
									PQEnqueue(new_pqueue, &element3));
	printf("Size of PQ: %ld\n", PQSize(new_pqueue));
	
	printf("Erase 97: %d\n",
					 *(int *)PQErase(new_pqueue, &to_remove, IsMatch, NULL));

	printf("Size of PQ after Erase: %ld\n\n", PQSize(new_pqueue));

	printf("Dequeue: %d\n", *(int *)PQDequeue(new_pqueue));

	printf("Peak: %d\n", *(int *)PQPeek(new_pqueue));
	
	printf("Dequeue: %p\n", PQDequeue(new_pqueue));

	printf("Size of PQ: %ld\n", PQSize(new_pqueue));

	PQDestroy(new_pqueue);
}


int PQCmp(const void *data1, const void *data2, void *param)
{
	int **ptr_ptr_data1 = (int **)data1;
	int **ptr_ptr_data2 = (int **)data2;
	int *ptr_data1 = *ptr_ptr_data1;
	int *ptr_data2 = *ptr_ptr_data2;

	(void)(param);

	if(*(int *)ptr_data1 < *(int *)ptr_data2)
	{
		return -1;
	}
	else if(*(int *)ptr_data1 > *(int *)ptr_data2)
	{
		return 1;
	}
	return 0;
}


int IsMatch(const void *data1, const void *data2, void *param)
{
	(void)(param);

    return (*(int *)data1 == *(int *)data2);
}


















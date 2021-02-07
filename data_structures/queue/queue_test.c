/* 
* File Name:queue_test.c
* Description: Defenition of functions for queue DS
* Developer: Guy Chen
* Date: 15.06.2020
*/


#include <stdio.h>
#include <stddef.h>
#include "queue.h"

/************************** Function Declerations ****************************/
/*
static void PrintQueue(queue_t* queue); 
*/
static queue_t *QCreateteTest(void);
static void QDestroyTest(queue_t *queue);
static void QSizeTest(const queue_t *queue);
static void QIsEmptyTest(const queue_t *queue);
static void QEnqueueTest(queue_t *queue, void *data);
static void QPeekTest(const queue_t *queue);
static void QDequeueTest(queue_t *queue);
static void  QAppendTest(queue_t *dest, queue_t *src);

/*************************** main Function ***********************************/

int main(void)
{
	int num1 = 1;
	float num2= 3.4;
	char str[] = "hellow world";

	queue_t *new_queue = NULL;
	queue_t *new_queue2 = NULL;	


	new_queue = QCreateteTest();
	new_queue2 = QCreateteTest();	
	QSizeTest(new_queue);
	QIsEmptyTest(new_queue);
	QEnqueueTest(new_queue, &num1); 
	QEnqueueTest(new_queue, &num2); 
	QEnqueueTest(new_queue, str); 
	QPeekTest(new_queue);
	QDequeueTest(new_queue);
	QDestroyTest(new_queue);

	return (0);
}






/************************ Function Defenitions *******************************/ 


/* Function to print the queue */
/*static void PrintQueue(queue_t* queue) 
{ 
    queue_t* temp = queue; 
    while (temp->slist->head != NULL)
	{ 
        printf("%p  ",(void *) temp->slist->data); 
        temp->slist = temp->slist->next; 
    } 
	printf ("\n");
} 

*/

static queue_t *QCreateteTest(void)
{
	queue_t *queue = NULL;
	
	queue = QCreate();
	printf("The queue has been created\n");
	return (queue);
}

/*****************************************************************************/

static void QDestroyTest(queue_t *queue)
{
	QDestroy(queue);

	printf("The queue has been destroyed\n");
}

/*****************************************************************************/

static void QSizeTest(const queue_t *queue)
{
	size_t counter = 0;
	
	counter = QSize(queue);
	
	printf("The number of elements in the queue is: %lu\n", counter);
}	

/*****************************************************************************/

static void QIsEmptyTest(const queue_t *queue)
{
	
	if (QIsEmpty(queue))
	{
		printf("The queue is empty\n");
	}
	else
	{
		printf("The queue is not empty\n");
	}
}

/*****************************************************************************/

static void QEnqueueTest(queue_t *queue, void *data)
{
	if (QEnqueue(queue,data))
	{
		printf("The insertion didn't succeed\n");
	}
	else
	{
		printf("The insertion succeeded\n");
	}
	
}	



/*****************************************************************************/

static void QPeekTest(const queue_t *queue)
{
	void *first_in_queue = NULL;
	
	first_in_queue = QPeek(queue);
	
	printf("The first element in the queue is: %p\n",  first_in_queue);
}

/*****************************************************************************/

static void QDequeueTest(queue_t *queue)
{
	QPeekTest(queue);
	QDequeue(queue);
	QPeekTest(queue);
}
		
/*****************************************************************************/

static void  QAppendTest(queue_t *dest, queue_t *src)
{
	QAppend(dest, src);
	printf("Q1 size after append action: %ld \n",(queue_t *) dest); 
	QSizeTest(dest);
	QSizeTest(src);
}

/*****************************************************************************/































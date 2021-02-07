/* 
* File Name:stack_test.c
* Description: testing the functions of stack.c file
* Developer: Guy Chen
* Reviewer: ori Komemi
* Date: 03.06.2020
*/

#include <stdio.h>

#include "stack.h"


/******************** Test Functions Declarations *****************************/


static stack_t *StackCreateTest(stack_t *stack);
static void StackDestroyTest(stack_t *stack);
static void StackIsEmptyTest(stack_t *stack);
static void StackPushTest(stack_t *stack);
static void StackPeekTest(stack_t *stack);
static void StackPopTest(stack_t *stack);
static void StackSizeTest(stack_t *stack);


/**************************** imt main **************************************/

int main(void)
{
	stack_t *stack = NULL;
	
	stack = StackCreateTest(stack);	

	StackPushTest(stack);
	StackPushTest(stack);
	StackSizeTest(stack);	
	StackPushTest(stack);
	StackSizeTest(stack);	
	StackPeekTest(stack);
	StackIsEmptyTest(stack);	
	StackPushTest(stack);
	StackPushTest(stack);
	StackPopTest(stack);
	StackSizeTest(stack);
	StackPopTest(stack);
	StackSizeTest(stack);
	StackPopTest(stack);
	StackSizeTest(stack);	
	StackIsEmptyTest(stack);
	StackDestroyTest(stack);
	
	return (0);
}







/******************** Test Functions Defenitions *****************************/


/* The function test StackCreate function */

static stack_t *StackCreateTest(stack_t *stack)
{
	size_t capacity = 4;
	void * status = NULL;
	
	stack = StackCreate(capacity);	
	status = stack;
	if (NULL != status)
	{
		printf("The creation of the stack succeeded\n");
	}
	else 
	{
		 printf("The creation of the stack didn't succeed\n");
	}
	return stack;
}
	


/* The function test StackDestroy function */

static void StackDestroyTest(stack_t *stack)
{
	StackDestroy(stack);
	printf("The stack has been destroyed\n");
}



/* The function test StackPush function */

static void StackPushTest(stack_t *stack)
{
	int push_status = 0;
	char *	element = "hey";
	
	
	push_status = StackPush(stack, element);
	if (0 == push_status)
	{
		printf("push element to the stack succeeded\n");
	}
	else 
	{
		 printf("push element to the stack didn't succeed\n");
	}		
}


/* The function test StackPeek function */

static void StackPeekTest(stack_t *stack)
{
	char *res = NULL;
	res = StackPeek(stack);
	
	printf("%s \n", res);

}


/* The function test StackPop function */

static void StackPopTest(stack_t *stack)
{
	
	printf("Before pop \n");
	StackPeekTest(stack);
	StackPop(stack);
	printf("After pop \n");
	StackPeekTest(stack);
}


/* The function test StackSize function */

static void StackSizeTest(stack_t *stack)
{
	size_t size = 0;
	size = StackSize(stack);
	printf("The current size of the stack is %lu\n", size);
}


/* The function test StackIsEmpty function */

static void StackIsEmptyTest(stack_t *stack)
{
	int res = 0;
	
	res = StackIsEmpty(stack);
	if (res)
	{
		printf("The stack is empty\n");
	}
	else 
	{
		printf("The stack is not empty\n");		
	}
}





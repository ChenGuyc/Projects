/* 
* File Name:stack.c
* Description: Defenitions of stack API functions
* Developer: Guy Chen
* Reviewer: ori Komemi
* Date: 03.06.2020
*/


#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>


enum Push_Status
{
	SUCCESS = 0,
	FAIL = 1
};

struct stack
{
	void **head;
	size_t top_index; /* holds the index of the next free space */
	size_t capacity;
};

typedef struct stack stack_t; 


/*****************************************************************************/

stack_t* StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	if (NULL == stack)
	{
		return NULL;
	} 
	
	stack->head = malloc(capacity * sizeof(void*));	
	if(NULL == stack->head)
	{
		free (stack);
		stack = NULL; 
		return NULL;
	}
	
	/* set attributes */
	stack->capacity = capacity;
	stack->top_index = 0;

	return (stack);
}

/*****************************************************************************/

void StackDestroy(stack_t *stack)
{
	assert(stack);	
	
	free(stack->head);
	stack->head = NULL;	
	free(stack);
	stack = NULL;
}


/*****************************************************************************/

/* The function will return 1 if stack is full, otherwise 0 */

static int StackIsFull (stack_t *stack) 
{
	return (stack->top_index == stack->capacity );
}

/*****************************************************************************/

int StackIsEmpty(stack_t *stack)
{
	return (!!(stack->top_index == (size_t) 0));
}

/*****************************************************************************/

int StackPush(stack_t *stack, void *element)
{
	if (StackIsFull(stack))
	{
		return (FAIL);
	}
	stack->head[stack->top_index++] = element;
	return (SUCCESS);
}

/*****************************************************************************/
	
void StackPop(stack_t *stack)
{
	if (!StackIsEmpty(stack))
	{
		--(stack->top_index);
	}
}

/*****************************************************************************/

void *StackPeek(stack_t *stack)
{
	if (StackIsEmpty(stack))
	{
		return NULL;
	}
	return (stack->head[stack->top_index - 1]);
}
 
/*****************************************************************************/

size_t StackSize(stack_t *stack)
{
	return (stack->top_index);
}

/*****************************************************************************/










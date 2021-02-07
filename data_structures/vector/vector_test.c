/* 
* File Name: vector_test.c
* Description: Defenitions of test function for vector API functions
* Developer: Guy Chen
* Date: 07.06.2020
*/

#include <stdio.h>
#include "vector.h"


/********************** Test Functions Declerations **************************/

static vector_t *VectorCreateTest(vector_t *vector);
static void VectorDestroyTest(vector_t *vector);
static void VectorGetElementTest(const vector_t *vector);
static void VectorSetElementTest(vector_t *vector);
static void VectorPushBackTest(vector_t *vector);
static void VectorPopBackTest(vector_t *vector);
static void VectorSizeTest(const vector_t *vector);
static void VectorCapacityTest(const vector_t *vector);
static void VectorReserveTest(vector_t *vector);
static void VectorShrinkToFitTest(vector_t *vector);


/***************************** main Function *********************************/

int main(void)
{
	vector_t *vector = NULL;
	
	vector = VectorCreateTest(vector);
	VectorCapacityTest(vector);	
	VectorSizeTest(vector);
	VectorPushBackTest(vector);
	VectorPushBackTest(vector);
	VectorPushBackTest(vector);
	VectorPushBackTest(vector);
	VectorGetElementTest(vector);
	VectorSetElementTest(vector);
	VectorGetElementTest(vector);
	VectorCapacityTest(vector);	
	VectorSizeTest(vector);
	VectorPopBackTest(vector);
	VectorPopBackTest(vector);
	VectorCapacityTest(vector);	
	VectorSizeTest(vector);	
	VectorPopBackTest(vector);
	VectorCapacityTest(vector);	
	VectorSizeTest(vector);
	VectorPopBackTest(vector);
	VectorCapacityTest(vector);	
	VectorSizeTest(vector);
	VectorReserveTest(vector);
	VectorCapacityTest(vector);	
	VectorSizeTest(vector);
	VectorShrinkToFitTest(vector);

	VectorDestroyTest(vector);
	return (0);
}



/********************** Test Functions Defenitions ***************************/


/* Test function for VectorCreate function */

static vector_t *VectorCreateTest(vector_t *vector)
{
	const size_t capacity =  3;
	
	vector = VectorCreate(capacity);	
	if (NULL == vector)
	{
		printf("The creation of vector didn't succeed\n");
	}
	else 
	{
 		printf("The creation of vector did succeeded\n");
	}
	return (vector);	
}


/* Test function for VectorDestroy function */

static void VectorDestroyTest(vector_t *vector)
{
	VectorDestroy(vector);
	printf("The vector has been destroyed\n");
}


/* Test function for VectorGetElement function */

static void VectorGetElementTest(const vector_t *vector)
{
	size_t index = 3;
	void *res = NULL;
	
	res = VectorGetElement(vector, index);
	printf("the address at index %lu is: %p\n", index, res);
}


/* Test function for VectorSetElement function */

static void VectorSetElementTest(vector_t *vector)
{
	char *element = "hello";
	size_t index = 3; 
	VectorSetElement(vector, index, element);

	printf("the element in index %lu, is: %p\n", index, VectorGetElement(vector, index)); 
}


/* Test function for VectorPushBack function */

static void VectorPushBackTest(vector_t *vector)
{
	int push_status = 0;	
	char *element = "hey";
	
	push_status = VectorPushBack(vector, element);
	if (0 == push_status)
	{
		printf("push element to the vector succeeded\n");
	}
	else 
	{
		 printf("push element to the vector didn't succeed\n");
	}		
}


/* Test function for VectorPopBack function */

static void VectorPopBackTest(vector_t *vector)
{
	VectorPopBack(vector);
	printf("The last element popped\n");
}


/* Test function for VectorSize function */

static void VectorSizeTest(const vector_t *vector)
{
	size_t size = 0;

	size = VectorSize(vector);
	printf("The amount of element in the vector are: %lu\n", size);
}


/* Test function for VectorCapacity function */

static void VectorCapacityTest(const vector_t *vector)
{
	size_t capacity = 0;
	
	capacity = VectorCapacity(vector);
	printf("The capacity of the vector is: %lu\n", capacity);
}


/* Test function for VectorReserve function */

static void VectorReserveTest(vector_t *vector)
{
	int status = 0;
	size_t new_capacity = 10;
	
	status = VectorReserve(vector, new_capacity);
	if (!status)
	{	
		printf("THe increasing of the vector succeeded\n");
	}
	else
	{
		printf("THe increasing of the vector didn't succeed\n");
	}

}


/* Test function for VectorShrinkToFit function */

static void VectorShrinkToFitTest(vector_t *vector)
{
	VectorShrinkToFit(vector);
	printf("The new capacity of vector is: %lu\n", VectorCapacity(vector)); 
	printf("The new size of vector is: %lu\n", VectorSize(vector)); 
}


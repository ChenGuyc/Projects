/* 
* File Name: fsa.c
* Description: Defenitions of test function for fsa API functions
* Developer: Guy Chen
* Date: 07.07.2020
*/


#include <stdio.h>
#include <stdlib.h> /* malloc, free */

#include "fsa.h"


/************************ Functions Declarations *****************************/

static void FSARequiredPoolSizeTest(void);
static void FSAInitTest(void);
static void FSAFreeBlocksTest(fsa_t *fsa);
static void FSAAllocTest(fsa_t *fsa);
static void FSAFreeTest(void *block);


/**************************** main Functions *********************************/

int main(void)
{
	fsa_t *fsa = NULL;
	size_t pool_size = 0;
	size_t num_of_blocks = 1000;
	size_t block_size = 37; 
	void *pool = NULL;	

	FSARequiredPoolSizeTest();
	FSAInitTest(); 
		
	printf("\n\n");

/********************* Example of main Program ******************************/
	
	pool_size = FSARequiredPoolSize(num_of_blocks, block_size);
	pool = calloc( pool_size, sizeof(char));
	if (NULL == pool)  
	{
		return (1);
	}

	fsa = FSAInit(pool, pool_size, block_size);
	printf("num of free blocks in pool: %lu\n", 	FSAFreeBlocks(fsa));
	FSAAllocTest(fsa);
	FSAAllocTest(fsa);  
	FSAAllocTest(fsa); 
	printf("num of free blocks in pool: %lu\n", FSAFreeBlocks(fsa));
	FSAFree(FSAAlloc(fsa)); 	
	free(pool);

	return (0);
}
 
/*****************************************************************************/

static void FSARequiredPoolSizeTest(void)
{
	size_t num_of_blocks = 1000;
	size_t block_size = 37;
	
	printf("The pool size shuld be: %lu\n", \
			FSARequiredPoolSize(num_of_blocks, block_size));
}

/*****************************************************************************/

static void FSAFreeBlocksTest(fsa_t *fsa)
{
	size_t amount_of_free_blocks = 0;	

	amount_of_free_blocks = FSAFreeBlocks(fsa);

	if (amount_of_free_blocks)
	{
		printf("There are %lu free blocks left fot use\n", \
				amount_of_free_blocks);
	}
	else
	{
		printf("There is no free block for use\n");
	}
}

/*****************************************************************************/

static void FSAInitTest(void)
{
		fsa_t *fsa = NULL;
		size_t pool_size = 56016;
		size_t block_size = 37; 

		void *pool = calloc(pool_size, sizeof(char)); 		
		if (NULL == pool)  
		{
			return;
		}

		printf("%p\n", (void*)pool);
		fsa = FSAInit(pool,pool_size, block_size);
		printf("%p\n", (void*)fsa);
		FSAFreeBlocksTest(fsa);		
		FSAAllocTest(fsa); 
		FSAAllocTest(fsa); 
		FSAFreeBlocksTest(fsa);			
		FSAAllocTest(fsa); 
		FSAAllocTest(fsa); 
		FSAFreeBlocksTest(fsa);	

		FSAFreeTest((void*)(FSAAlloc(fsa))); 
		FSAFree(FSAAlloc(fsa)); 
		FSAAllocTest(fsa);
		FSAFreeBlocksTest(fsa);		
		free(pool);
}

/*****************************************************************************/

static void FSAAllocTest(fsa_t *fsa)
{
	void *new_block = NULL;
	
	new_block = FSAAlloc(fsa);
	printf("%p\n", (void*)new_block);
	
}

/*****************************************************************************/

static void FSAFreeTest(void *block)
{
	FSAFree(block);
}
	






















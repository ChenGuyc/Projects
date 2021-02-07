/* 
* File Name: fsa.c
* Description: Defenitions of fsa API functions
* Developer: Guy Chen
* Date: 07.07.2020
*/


#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

struct fixed_sized_alloc
{
	size_t size;
	void* next;
};

struct block
{
	void *next;
	void *data;
};

typedef struct block block_t; 
	

/****************************************************************************/

size_t FSARequiredPoolSize(size_t num_of_blocks, size_t block_size)
{
	size_t aligned_block_size = 0;
	
	block_size += sizeof(struct block);
	aligned_block_size = block_size;
	
	if (0 != block_size % WORD_SIZE)	
	{
		aligned_block_size = ((block_size / WORD_SIZE) + 1) * WORD_SIZE;
	}

	return (aligned_block_size * num_of_blocks + sizeof(fsa_t));
}

/****************************************************************************/

fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t block_size)
{	
	fsa_t *fsa = NULL;
	block_t *new_block = NULL;	
	size_t i = 0;

	assert(mem_pool);

	if (pool_size < block_size + sizeof(block_t))
	{
		return (NULL);
	}


	while ((size_t)mem_pool % WORD_SIZE )
	{
		mem_pool = ((char*)mem_pool + 1) ;
	}
	
	fsa =(fsa_t*) mem_pool;
	fsa->next = (fsa_t*)mem_pool + (sizeof(fsa_t) ) ; 
	fsa->size = (pool_size - sizeof(fsa)) / (block_size +(WORD_SIZE - 
				(block_size % WORD_SIZE)) + sizeof(block_t));
	new_block= fsa->next;	

	for(i = 1; i < fsa->size; ++i)
	{
		new_block->next = (char*)new_block + sizeof(block_t) + block_size + 
						  (WORD_SIZE -(block_size % WORD_SIZE)) ;	
		new_block = new_block->next; 
	}
	new_block->next = NULL;
	return (fsa);
}

/****************************************************************************/	

void *FSAAlloc(fsa_t *fsa)
{	
	block_t *new_block = NULL;

	assert(fsa);

	/* if the pool is not full we can allocate a block for the user */
	if (FSAFreeBlocks(fsa))
	{	
		/* the block we alloocte is the first empty block */	
		new_block = fsa->next;
		new_block->data = fsa;
/* after the allocatiion the block is out of the list and fsa point to next empty block */ 
		fsa->next = new_block->next;
		--fsa->size;
		/*return the blockto user */
		return((char*)new_block + sizeof(block_t) );
	}
	return (NULL);	 
}

/****************************************************************************/	

size_t FSAFreeBlocks(fsa_t *fsa)
{
	assert(fsa);

	return (fsa->size);
}

/****************************************************************************/	

void FSAFree(void *block)
{
	block_t *new_block = NULL;
	fsa_t *fsa = NULL;
	/* moving to start of block struct */	
	new_block = (block_t *)((char *)block - sizeof(block_t));
	
	fsa = new_block->data; 
	/* increse the size by 1 since adding new empty block */	
	++(fsa->size); 
	/* update the next of block to point to next empty block */	
	new_block->next = fsa->next; 
	/* fsa should point to the new block */
	fsa->next = new_block;
}
	
/****************************************************************************/
	















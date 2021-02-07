/* 
* File Name: vsa.c
* Description: Defenitions of vsa API functions
* Developer: Guy Chen
* Date: 09.07.2020
*/


#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "vsa.h"


typedef struct block block_t; 

struct variable_sized_alloc
{
	size_t current_biggest_free_block;
	void *next;
};

struct block
{
	block_t *next;
	size_t size;
	int flag; /*flag for free or not, 1 for free 0 for not free */

};

static const size_t WORD_SIZE = sizeof(size_t);
static const int FREE = 1;
static const int NOT_FREE = 0;
static const size_t block_t_size = sizeof(block_t);
static const size_t handle_size = sizeof(vsa_t);

static size_t ActualBlockSize(size_t block_size);
	
/*****************************************************************************/

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	block_t *new_block = NULL;	
	
	assert (mem_pool);
	
	if(pool_size <= (handle_size + block_t_size))
	{
		return (NULL);
	}
	/* aligned mem_pool */
	while ((size_t)mem_pool & (WORD_SIZE - 1) )
	{
		mem_pool = ((char*)mem_pool + 1) ;
	}

	/* set the attrivutes for the list */
	vsa = (vsa_t*)mem_pool;
	vsa->next = (block_t*)((char*)vsa + handle_size);
	new_block = vsa->next;
	new_block->size = pool_size - handle_size;
	new_block->next = NULL;
	new_block->flag = FREE;
	vsa->current_biggest_free_block = pool_size - handle_size - block_t_size; 

	return (vsa);
}

/*****************************************************************************/
size_t VSABiggestFreeBlock(vsa_t *vsa)
{
	block_t *temp = NULL;
	size_t biggest_free = vsa->current_biggest_free_block;

	assert(vsa);	

	temp = vsa->next;

	while (NULL != temp->next)
	{
		if(temp->flag == FREE && (temp->size - block_t_size) > biggest_free)
		{
			biggest_free = temp->size;
		}
		temp = temp->next;
	}
	vsa->current_biggest_free_block = biggest_free; 	
	return(vsa->current_biggest_free_block);
}

/*****************************************************************************/

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	size_t actual_block_size = 0;
	block_t *new_block = NULL;
	block_t *temp = NULL;	
	size_t biggest_free = 0;
	
	assert(vsa);
	
	biggest_free = vsa->current_biggest_free_block;
	temp = vsa->next; 
	actual_block_size = ActualBlockSize(block_size);
	/*defragmentation */		
	if(biggest_free <= actual_block_size)
	{ 
		while (NULL != temp->next)
		{	
			if((FREE == temp->flag) && (FREE == (temp->next)->flag))
			{
				temp->size += (temp->next)->size;
				if(temp->size > biggest_free)
				{
					biggest_free = temp->size;
					temp->next = temp->next->next;
				}
			}
		
			temp = temp->next;
		}
	} 
	vsa->current_biggest_free_block = biggest_free;
	temp = vsa->next;
	if(biggest_free > actual_block_size)
	{
	/* move over the pool to find the first fit space to allocate */
		while(NULL != temp)
		{
			new_block = temp;
			if (FREE == temp->flag && temp->size > actual_block_size)
			{
			/*	new_block = temp; */
				if(NULL == new_block->next)
				{
					new_block->next = (block_t*)((char*)new_block + 
									   	actual_block_size) ;
					new_block->next->flag = FREE;
					new_block->next->next = NULL;
				}
				else
				{
					new_block->next = (block_t*)((char*)new_block + 
					actual_block_size) ;
				}				
				new_block->next->size = biggest_free - actual_block_size;
			/*	new_block->next->flag = FREE; */
				new_block->flag = NOT_FREE;
				new_block->size = actual_block_size ;
				vsa->current_biggest_free_block -= actual_block_size; 
				return ((char*)new_block + block_t_size);
			}
			temp = temp->next;
		}
	}
	/* if after defragmentation there is no enough space return NULL */
	return (NULL);	
}

/*****************************************************************************/

void VSAFree(void *block)
{
	block_t *new_block = NULL;
	
	new_block = (block_t*)((char*)block - block_t_size);
	new_block->flag = FREE;
}

/*****************************************************************************/

static size_t ActualBlockSize(size_t block_size)
{
	size_t actual_block_size = block_t_size + block_size;

	while (actual_block_size & (WORD_SIZE - 1))
	{
		++actual_block_size;
	}		

	return (actual_block_size);
}






/* 
* File Name: vector.c
* Description: Defenitions of vector API functions
* Developer: Guy Chen
* Date: 07.06.2020
*/

#ifndef ILRD_VECTOR_H
#define ILRD_VECTOR_H

#include <stddef.h>	/* size_t */
#include <stdlib.h> /* malloc, free */

typedef enum  
{
	SUCCESS, FAILURE
} status_t;

typedef struct vector 
{
	size_t size;
	size_t init_capacity;
	size_t curr_capacity;
	void** arr;
} vector_t; 

/*---------------------------------------------------------------------------*/

vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t*)malloc(sizeof(vector_t));
	if(vector != NULL)
	{
		vector->arr = (void**)malloc(sizeof(void*) * capacity);
		if(vector->arr != NULL)
		{
			vector->size = 0;
			vector->init_capacity = capacity;
			vector->curr_capacity = capacity;
		}
		else
		{
			free(vector);
			vector = NULL;
			return (vector);
		}
	}
	else
	{
		return (NULL);
	}
	return (vector);
}

/*---------------------------------------------------------------------------*/

void VectorDestroy(vector_t *vector)
{
	free(vector->arr);
	vector->arr = NULL;
	free(vector);
	vector = NULL;
}

/*---------------------------------------------------------------------------*/

void *VectorGetElement(const vector_t *vector, size_t index)
{
	return(vector->arr[index]); 
}

/*---------------------------------------------------------------------------*/

void VectorSetElement(vector_t *vector, size_t index, void *element)
{
	vector->arr[index] = element;
}

/*---------------------------------------------------------------------------*/

int VectorPushBack(vector_t *vector, void *element)
{
	vector_t *temp_vector = NULL;
	temp_vector = vector;
	
	if(vector->size == vector->curr_capacity)
	{
		temp_vector->arr = (void **)realloc(vector->arr, (vector->curr_capacity) * 2 * sizeof(void*));
		if(temp_vector->arr == NULL)
		{
			return (FAILURE);
		}
		vector->curr_capacity *= 2;
		vector->arr = temp_vector->arr;
	}
	vector->arr[vector->size] = element;
	++vector->size;
	return (SUCCESS);
}

/*---------------------------------------------------------------------------*/

void VectorPopBack(vector_t *vector)
{
	vector_t *temp_vector;

	if(vector->size > 0)
	{
		--(vector->size);
	}
	if(vector->size <= (0.25 * vector->curr_capacity) && 
		((vector->curr_capacity / 2) > vector->init_capacity))
	{
		temp_vector = vector;
		temp_vector->arr = (void**)realloc(vector->arr, ((vector->curr_capacity) / 2) * sizeof(void*));
		if(temp_vector->arr == NULL)
		{
			return;
		}
		vector->curr_capacity = vector->curr_capacity / 2;
		vector->arr = temp_vector->arr;
		return;
	}
	else if(vector->size <= (0.25 * vector->curr_capacity) && 
		((vector->curr_capacity / 2) <= vector->init_capacity) &&
			vector->size < vector->init_capacity)
	{
		temp_vector = vector;
		temp_vector->arr = (void**)realloc(vector->arr, vector->init_capacity * sizeof(void*));
		if(temp_vector->arr == NULL)
		{
			return;
		}
		vector->curr_capacity = vector->init_capacity;
		vector->arr = temp_vector->arr;
	}
}

/*---------------------------------------------------------------------------*/

size_t VectorSize(const vector_t *vector)	
{
	return (vector->size);
}


/*---------------------------------------------------------------------------*/

size_t VectorCapacity(const vector_t *vector)
{
	return(vector->curr_capacity);
}

/*---------------------------------------------------------------------------*/

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	vector_t *temp_vector;

	if(new_capacity > vector->curr_capacity)
	{
		temp_vector = vector;
		temp_vector->arr = (void*) realloc(vector->arr, new_capacity*sizeof(void*));
		if(temp_vector->arr == NULL)
		{
			return (FAILURE);
		}
		vector->curr_capacity = new_capacity;
		vector->arr = temp_vector->arr;
		return (SUCCESS);
	}
	return (FAILURE);
}

/*---------------------------------------------------------------------------*/

void VectorShrinkToFit(vector_t *vector)
{
	vector_t *temp_vector;

	if(vector->size < vector->init_capacity)
	{
		temp_vector = vector;
		temp_vector->arr = (void*) realloc(vector->arr, vector->init_capacity*sizeof(void*));
		if(temp_vector->arr == NULL)
		{
			return;
		}
		vector->curr_capacity = vector->init_capacity;
		vector->arr = temp_vector->arr;
		return;
	}
	else if (vector->size < vector->curr_capacity)
	{
		temp_vector = vector;
		temp_vector->arr = (void*) realloc(vector->arr, vector->size * sizeof(void*));
		if(temp_vector->arr == NULL)
		{
			return;
		}
		vector->curr_capacity = vector->size;
		vector->arr = temp_vector->arr;
	}
}

/*---------------------------------------------------------------------------*/

void **VectorGetArray(const vector_t *vector)
{
	return (vector->arr);
}
#endif /* ILRD_VECTOR_H */






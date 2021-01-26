/* 
* File Name: heapify.c
* Description: Definition of heapify functions
* Developer: Guy Chen
* Date: 28.06.2020
*/

#include <assert.h>

#include "heapify.h"

/**************************utility functions***********************************/

static void Swap(void *element1, void *element2, size_t size);
size_t PickLeftChild(size_t index);
size_t PickRightChild(size_t index);
size_t PickParent(size_t index);
size_t PickSmaller(void *base, size_t nmemb, size_t left_child, size_t right_child, size_t elem_size, heapify_cmp_func_t cmp, void *param);

/***************************Functions implemintations**************************/

void HeapifyUp(void *base, size_t nmemb, size_t index, size_t elem_size,     
               heapify_cmp_func_t cmp, void *param)
{
    size_t parent = PickParent(index);

    assert(base);
    (void)nmemb;
    
    while(index > 0 && 
          cmp((char *)base + parent * elem_size, (char *)base + index * elem_size, param) == 1)
    {
        Swap((char *)base + parent * elem_size, (char *)base + index * elem_size, elem_size);
        index = parent;
        parent = PickParent(parent);
    }
}

/******************************************************************************/

void HeapifyDown(void *base, size_t nmemb, size_t index, size_t elem_size,     
                 heapify_cmp_func_t cmp, void *param)
{
    size_t left_child = 0;
    size_t right_child = 0;
    size_t smaller = 0;

    assert(base);

    if(index <= ((nmemb - 2) / 2) && nmemb > 1)
    {
        left_child = PickLeftChild(index);
        right_child = PickRightChild(index);
        smaller = PickSmaller(base, nmemb, left_child, right_child, elem_size, cmp, param);

        while ((index <= ((nmemb - 2) / 2)) && cmp((char *)base + index * elem_size, (char *)base + smaller * elem_size, param) == 1)
        {
            Swap((char *)base + index * elem_size, (char *)base + smaller * elem_size, elem_size);
            index = smaller;
            left_child = PickLeftChild(index);
            right_child = PickRightChild(index);
            smaller = PickSmaller(base, nmemb, left_child, right_child, elem_size, cmp, param);
        }
    }
}

/******************************************************************************/

static void Swap(void *element1, void *element2, size_t size)
{
	char *dest = NULL;
	char *src = NULL;
	char temp = 0;
	size_t i = 0;
	
	assert(element1);
	assert(element2);

	dest = element1;
	src = element2;

	for (i = 0; i < size; ++i)
	{ 
		temp = *dest;
		*dest = *src;
		*src = temp;

		++dest;
		++src;
	}
}

/******************************************************************************/

size_t PickLeftChild(size_t index)
{
    return (index * 2 + 1);
}

/******************************************************************************/

size_t PickRightChild(size_t index)
{
    return (index * 2 + 2);
}

/******************************************************************************/

size_t PickParent(size_t index)
{
    return ((index - 1) / 2);
}

/******************************************************************************/

size_t PickSmaller(void *base, size_t nmemb, size_t left_child, size_t right_child, size_t elem_size, heapify_cmp_func_t cmp, void *param)
{
    if(right_child >= nmemb)
    {
        return (left_child);
    }

    else if(cmp((char *)base + left_child * elem_size, (char *)base + right_child * elem_size, param) == 1)
    {
        return (right_child);
    }

    else
    {
        return (left_child);
    }
}

/******************************************************************************/

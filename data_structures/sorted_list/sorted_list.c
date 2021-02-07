/* 
* File Name: sorted_list.c
* Description: Definition functions of sorted_list API functions
* Developer: Guy Chen
* Date: 22.06.2020
*/


#include <stdlib.h> /* malooc, free */
#include <assert.h> /* assert */
#include <stdio.h>

#include "sorted_list.h"

/*****************************************************************************/

#define TRUE 1
#define FALSE 0

/*****************************************************************************/
struct sorted_list
{
	dlist_t *dlist;
	sorted_list_is_before_func_t is_before; 
	void *param;
};


/*****************************************************************************/

sorted_list_t *SortedListCreate(sorted_list_is_before_func_t is_before,
								void * param)

{
	sorted_list_t *sorted_list = NULL;
	
	sorted_list = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	if (NULL == sorted_list)
	{
		return (NULL);
	}
	sorted_list->dlist = DListCreate();
	if (NULL == sorted_list->dlist)
	{
		free(sorted_list);
		sorted_list = NULL;
		return (NULL);
	}
	sorted_list->param = param;
	sorted_list->is_before = is_before;	
	
	return (sorted_list);
}

/*****************************************************************************/

void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert (sorted_list);
	DListDestroy(sorted_list->dlist);
	sorted_list->dlist = NULL;
	free (sorted_list);
	sorted_list = NULL;
}
	
/*****************************************************************************/

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
    sorted_list_iter_t iter;
	
	assert(sorted_list);

    iter.internal_iter = DListBegin(sorted_list->dlist);
    return(iter);
}


/*****************************************************************************/	

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
    sorted_list_iter_t iter;
	
	assert(sorted_list);

    iter.internal_iter = DListEnd(sorted_list->dlist);
    return(iter);
}

/*****************************************************************************/
		
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	sorted_list_iter_t tmp_iter;
	assert(iter.internal_iter);
	
	tmp_iter.internal_iter = DListNext(iter.internal_iter);

	return (tmp_iter);
}

/*****************************************************************************/

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	sorted_list_iter_t tmp_iter;
	assert(iter.internal_iter);
	
	tmp_iter.internal_iter= DListPrev(iter.internal_iter);

	return (tmp_iter);
}


/*****************************************************************************/

void *SortedListGetData(sorted_list_iter_t iter)
{
	assert(iter.internal_iter);
	
	return (DListGetData(iter.internal_iter));
}

/*****************************************************************************/

int SortedListIterIsEqual(sorted_list_iter_t iter1,
						  sorted_list_iter_t iter2)
{
	assert(iter1.internal_iter);
	assert(iter2.internal_iter);
	
	return (DListIterIsEqual(iter1.internal_iter, iter2.internal_iter));
}

/*****************************************************************************/

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert (sorted_list);	

	return (DListIsEmpty(sorted_list->dlist));
} 

/*****************************************************************************/

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{

	sorted_list_iter_t new_elem; 

	assert(sorted_list);
	
	new_elem = SortedListBegin(sorted_list);
	
	/* intert element in case the list is empty */
	if(SortedListIsEmpty(sorted_list))
	{
		new_elem.internal_iter = (DListInsert(sorted_list->dlist, 
									SortedListEnd(sorted_list).internal_iter,
	 								data));
		return (new_elem);
	}
	/* moving over the list to find the place to insert */
	while(!SortedListIterIsEqual(new_elem, SortedListEnd(sorted_list)))
	{
		if (!sorted_list->is_before(SortedListGetData
								   (new_elem), data,sorted_list->param))
			{
				new_elem.internal_iter = (DListInsert(sorted_list->dlist, 
											new_elem.internal_iter, data));
				return (new_elem);									
			}
		new_elem = SortedListNext(new_elem);
	}
	/* in case all the other elements are greater or equal than the data, 
	   the data will be insert in the end */ 
	new_elem.internal_iter = (DListInsert(sorted_list->dlist, 
								SortedListEnd(sorted_list).internal_iter,
								data));	
	return (new_elem);	
}

/*****************************************************************************/

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	size_t counter = 0;
	sorted_list_iter_t temp_iter = {0};  
	
	assert(sorted_list);
	
	temp_iter = SortedListBegin(sorted_list);
	while(!SortedListIterIsEqual(temp_iter, SortedListEnd(sorted_list)))	
	{
		++counter;
		temp_iter = SortedListNext(temp_iter);
	}
	return (counter);	
}

/*****************************************************************************/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	sorted_list_iter_t temp_iter;
	
	assert(iter.internal_iter);
	
	temp_iter.internal_iter = (DListRemove(iter.internal_iter));
	
	return (temp_iter);
}

/*****************************************************************************/

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	
	void *data_of_elem = NULL;
	assert(sorted_list);
	
	data_of_elem = SortedListGetData(SortedListBegin(sorted_list));
	SortedListRemove(SortedListBegin(sorted_list)); 
	
	return (data_of_elem);
}

/*****************************************************************************/

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	void *data_of_elem = NULL;
	assert(sorted_list);
	
	data_of_elem = SortedListGetData(SortedListPrev(SortedListEnd(sorted_list)));
	SortedListRemove(SortedListPrev(SortedListEnd(sorted_list)));
	
	return (data_of_elem);
}

/*****************************************************************************/	
	
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
									sorted_list_iter_t to,
									sorted_list_is_match_func_t is_match, 
									void *param)
{
	sorted_list_iter_t tmp_iter;	

	tmp_iter.internal_iter = DListFind(from.internal_iter, to.internal_iter,
									   is_match, param);
	return(tmp_iter);
}

/*****************************************************************************/	

sorted_list_iter_t SortedListFind(sorted_list_t *sorted_list,
								  sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  void *to_find)
{
	sorted_list_iter_t temp_iter = from;
	
	assert(sorted_list);
	while (!SortedListIterIsEqual(to,temp_iter) && 
		    sorted_list->is_before(SortedListGetData(temp_iter), to_find, NULL)) 
	{
		temp_iter = SortedListNext(temp_iter);
	}
	if (!SortedListIterIsEqual(temp_iter, to) &&
		!sorted_list->is_before(to_find, SortedListGetData(temp_iter),
								sorted_list->param))
	{
		return (temp_iter);
	}
	
	return (to);
}

/*****************************************************************************/	

int SortedListForEach(sorted_list_iter_t from, 
					  sorted_list_iter_t to, 
					  sorted_list_do_action_func_t do_action, 
					  void *param)
{
	assert(from.internal_iter);	
	assert(to.internal_iter);
	
	return(DListForEach(from.internal_iter, to.internal_iter, do_action, param));
	
}

/*****************************************************************************/

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t from = {0};
	sorted_list_iter_t to = {0};
	sorted_list_iter_t dest_iter;
	sorted_list_iter_t src_iter;

	assert(dest);
	assert(dest);
	
	dest_iter = SortedListBegin(dest);
	src_iter = SortedListBegin(src);
	from = SortedListBegin(src);
	to = SortedListBegin(src);

	while (!SortedListIterIsEqual(src_iter, SortedListEnd(src)) &&
		   !SortedListIterIsEqual(dest_iter, SortedListEnd(dest)))
	{
		while(!dest->is_before(SortedListGetData(dest_iter),
							  SortedListGetData(src_iter), dest->param))
		{
			to = SortedListNext(to);
			src_iter = to;
		}

		if(!SortedListIterIsEqual(from, to))
		{
			DListSplice(from.internal_iter, to.internal_iter, 
						dest_iter.internal_iter);
			from = to;
		}
			
		dest_iter = SortedListNext(dest_iter);
	}

	if (SortedListIterIsEqual(dest_iter, SortedListEnd(dest)) &&
		!SortedListIterIsEqual(src_iter, SortedListEnd(src)))
	{
		dest_iter = SortedListEnd(dest);
		to =  SortedListEnd(src);
		DListSplice(from.internal_iter, to.internal_iter, 
					dest_iter.internal_iter);  		
	}
}

/*****************************************************************************/
























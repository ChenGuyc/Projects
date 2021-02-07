/* 
* File Name: sorted_list_test.c
* Description: Definition of test functions for sorted_list API functions
* Developer: Guy Chen
* Date: 22.06.2020
*/


#include <stdio.h>
#include "sorted_list.h"

#define TRUE 1
#define FALSE 0

enum DO_ACTION_STATUS
{
	SUCCESS = 0,
	FAILURE
};


/************************** Functions Decleration ****************************/

int is_before(const void *data1, const void *data2);

/*****************************************************************************/

static sorted_list_t *SortedListCreateTest(void);
static void SortedListDestroyTest(sorted_list_t *sorted_list);
static void SortedListBeginTest(const sorted_list_t *sorted_list);
static void SortedListEndTest(const sorted_list_t *sorted_list);
static void SortedListNextTest(sorted_list_t *sorted_list);
static void SortedListPrevTest(sorted_list_t *sorted_list);
static void SortedListGetDataTest(sorted_list_t *sorted_list);
static void SortedListIterIsEqualTest(sorted_list_t *sorted_list);
static void SortedListIsEmptyTest(const sorted_list_t *sorted_list);
static void SortedListInsertTest(sorted_list_t *sorted_list);
static void SortedListInsertTest1(sorted_list_t *sorted_list);
static void SortedListSizeTest(const sorted_list_t *sorted_list);
static void SortedListRemoveTest(sorted_list_t *sorted_list);
static void SortedListPopFrontTest(sorted_list_t *sorted_list);
static void SortedListPopBackTest(sorted_list_t *sorted_list);
static void SortedListFindIfTest(sorted_list_t *sorted_list);
static void SortedListFindTest(sorted_list_t *sorted_list);
static void SortedListForEachTest(sorted_list_t *sorted_list);
static void SortedListMergeTest(void);


/*****************************************************************************/

int Is_Match(const void *data, void *param);
int IsBefore(const void *data1, const void *data2, void *param);
int Do_Action(void *data, void *param);



/**************************** main function **********************************/

int main(void)
{
	sorted_list_t *sorted_list = NULL;
	
	sorted_list = SortedListCreateTest();
	SortedListSizeTest(sorted_list);
	
	SortedListEndTest(sorted_list);	
	SortedListInsertTest1(sorted_list);
	SortedListInsertTest1(sorted_list);	
	SortedListInsertTest(sorted_list);
	SortedListSizeTest(sorted_list);
	SortedListInsertTest1(sorted_list);
	SortedListSizeTest(sorted_list);
	SortedListFindTest(sorted_list);		
	SortedListFindIfTest(sorted_list);
	SortedListForEachTest(sorted_list);	
	SortedListRemoveTest(sorted_list);
	SortedListBeginTest(sorted_list);
	SortedListSizeTest(sorted_list);
	SortedListPopBackTest(sorted_list); 
	SortedListSizeTest(sorted_list);	
	SortedListDestroyTest(sorted_list);
	SortedListMergeTest();

	return (0);
}


/************************** Functions Defenition ****************************/

int IsBefore(const void *data1, const void *data2, void *param)
{

	return ((int*) data1 < (int*) data2);
}

/*****************************************************************************/	

static sorted_list_t *SortedListCreateTest(void)
{
	sorted_list_t *sorted_list = NULL;
	void *param = NULL;	

	sorted_list = SortedListCreate(&IsBefore, param);
	
	if(sorted_list)
	{
		printf("The creation of sorted list succeeded\n");
	}
	else
	{
		printf("The creation of sorted list didn't succeed\n");
	}
	
	return (sorted_list);
}

/*****************************************************************************/	

static void SortedListDestroyTest(sorted_list_t *sorted_list)
{
	SortedListDestroy(sorted_list);
	printf("The sorted list has been destroyed\n");
}

/*****************************************************************************/	

static void SortedListBeginTest(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter_begin;
	iter_begin = SortedListBegin(sorted_list);
	
	printf("The element in the beginning of the list is: %p\n",\
			SortedListGetData (iter_begin));
}

/*****************************************************************************/	

static void SortedListEndTest(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter_end;
	iter_end = SortedListEnd(sorted_list);
	
	printf("The element in the end of the list is: %p\n",\
			SortedListGetData(iter_end));
}

/*****************************************************************************/	

static void SortedListNextTest(sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter_next ;

	iter_next =  SortedListNext(SortedListBegin(sorted_list));
	printf("The next element to the curent iter in the list is: %p\n",iter_next);
}			
	
/*****************************************************************************/	

static void SortedListPrevTest(sorted_list_t *sorted_list)
{	
	sorted_list_iter_t iter_prev ;
	
	iter_prev =  SortedListPrev(SortedListEnd(sorted_list));
	printf("The previous element to the curent iter in the list is: %p\n",\
			iter_prev);
}

/*****************************************************************************/

static void SortedListGetDataTest(sorted_list_t *sorted_list)
{
	void *data = NULL;

	data =  SortedListGetData(SortedListBegin(sorted_list));
	printf("The data in the curent element in the list is: %p\n", data);
}	

/*****************************************************************************/

static void SortedListIterIsEqualTest(sorted_list_t *sorted_list)
	
{	
	if(SortedListIterIsEqual((SortedListBegin(sorted_list)),
							 SortedListNext(SortedListBegin(sorted_list))))
	{
		printf("The two iterators are equals\n");
	}
	else
	{
		printf("The two iterators are equals\n");
	}	
}		

/*****************************************************************************/

static void SortedListIsEmptyTest(const sorted_list_t *sorted_list)
{
	if (SortedListIsEmpty(sorted_list))
	{
		printf("The list is empty\n");
	}
	else
	{
		printf("The list is not empty\n");
	}
}

/*****************************************************************************/

static void SortedListInsertTest(sorted_list_t *sorted_list)
{
	void *data = (int*) 5;
	sorted_list_iter_t elem_to_insert = SortedListInsert(sorted_list, data);
	
	if(SortedListIterIsEqual(SortedListEnd(sorted_list), elem_to_insert))
	{
		printf("The isertion of new element didn't succeed\n");
	}
	else
	{
		printf("The isertion of new element succeeded\n");
		printf("The new element is %p\n", SortedListGetData(elem_to_insert));
	}
}

/*****************************************************************************/

static void SortedListInsertTest1(sorted_list_t *sorted_list)
{
	void *data = (int*) 3;
	sorted_list_iter_t elem_to_insert = SortedListInsert(sorted_list, data);
	
	if(SortedListIterIsEqual(SortedListEnd(sorted_list), elem_to_insert))
	{
		printf("The isertion of new element didn't succeed\n");
	}
	else
	{
		printf("The isertion of new element succeeded\n");
		printf("The new element is %p\n",SortedListGetData (elem_to_insert));
	}
}

/*****************************************************************************/

static void  SortedListSizeTest(const sorted_list_t *sorted_list)
{
	size_t size = 0;
			

	size = SortedListSize(sorted_list);
	
	printf("The size of the sorted list is: %lu\n", size);
}
	
/*****************************************************************************/

static void SortedListRemoveTest(sorted_list_t *sorted_list)
{
	sorted_list_iter_t elem_to_remove;
	sorted_list_iter_t iter;
	iter = SortedListBegin(sorted_list);
	printf("The element to remove in adrees %p\n", SortedListGetData(iter));
	elem_to_remove = SortedListRemove(iter);
	printf("The next element to the one that removed is in adrees %p\n",\
			elem_to_remove);
}
	
/*****************************************************************************/

static void SortedListPopFrontTest(sorted_list_t *sorted_list)
{
	void *data = NULL;
	
	data = SortedListPopFront(sorted_list);
	printf("The data of element popped from the begining of the list is %p\n",\
			 data);
}

/*****************************************************************************/


static void SortedListPopBackTest(sorted_list_t *sorted_list)
{
	void *data = NULL;
	
	data = SortedListPopBack(sorted_list);
	printf("The data of element popped from the end of the list is %p\n",\
			 data);
}

/*****************************************************************************/

int Is_Match(const void *data, void *param)
{
    return ((int *)data == (int *)param);
}

/*****************************************************************************/

static void SortedListFindIfTest(sorted_list_t *sorted_list)
{
	sorted_list_iter_t res_iter = {0};
	int num = 10;
	int num_par = 5;
	void *data = &num;
	void *param = &num_par;

	res_iter = SortedListFindIf(SortedListBegin(sorted_list), 
								SortedListPrev(SortedListEnd(sorted_list)), 
						 		&Is_Match, 
								param);

	if(SortedListIterIsEqual(res_iter, 
	   						 SortedListPrev(SortedListEnd(sorted_list))))
	{
		printf ("there is no match\n");
	}
	else
	{
		printf ("there is a match\n");	
	}
}		
	
/*****************************************************************************/

static void SortedListFindTest(sorted_list_t *sorted_list)	  
{
	sorted_list_iter_t temp_iter = {0};

	int num_par = 5;

	void *param = &num_par;

	temp_iter = SortedListFind(sorted_list, SortedListBegin(sorted_list),
							   SortedListEnd(sorted_list), param);
	printf("The place found is: %p\n", SortedListGetData(temp_iter));
}

/*****************************************************************************/

int Do_Action(void *data, void *param)
{
/*
    (int*)data += (int*) param; 
	
*/
    return (0);
}

/*****************************************************************************/
static void SortedListForEachTest(sorted_list_t *sorted_list)
{
	int do_action_status = FAILURE;
	int y = 5;
	void *param = &y;
	

	do_action_status = SortedListForEach(SortedListBegin(sorted_list), 
					   SortedListEnd(sorted_list), &Do_Action, param);
	if  (!do_action_status)
	{
		printf("the action succeeded for all the elements\n");
	}
	else
	{
		printf("the action didn't succeed for all the elements\n");
	}
}
	
/*****************************************************************************/

static void SortedListMergeTest(void)
{	
	sorted_list_t *dest1;
	sorted_list_t *src1;
	sorted_list_iter_t elem_to_insert;
	void *param = NULL;
	dest1 = SortedListCreate(&IsBefore,param);
	src1 = SortedListCreate(&IsBefore,param);
	
	elem_to_insert = SortedListInsert(dest1, (int*)1);
	elem_to_insert = SortedListInsert(dest1, (int*)7);
	elem_to_insert = SortedListInsert(dest1, (int*)4);
	elem_to_insert = SortedListInsert(dest1, (int*)9);	

	elem_to_insert = SortedListInsert(src1, (int*)0);
	elem_to_insert = SortedListInsert(src1, (int*)2);
	elem_to_insert = SortedListInsert(src1, (int*)3);
	elem_to_insert = SortedListInsert(src1, (int*)6);
	elem_to_insert = SortedListInsert(src1, (int*)9);
	elem_to_insert = SortedListInsert(dest1, (int*)10);
	elem_to_insert = SortedListInsert(dest1, (int*)11);	
	
	printf("The size of the dest before merge %lu\n", SortedListSize(dest1));
	printf("The size of the src before merge %lu\n", SortedListSize(src1));	
	SortedListMerge(dest1, src1);
	printf("The size of the dest after merge %lu\n", SortedListSize(dest1));
	printf("The size of the src after merge %lu\n", SortedListSize(src1));	
	
	elem_to_insert = SortedListBegin(dest1);
	while (!SortedListIterIsEqual(elem_to_insert,  SortedListEnd(dest1)))
	{
		printf("%d ", (int*)SortedListGetData(elem_to_insert));
		elem_to_insert = SortedListNext(elem_to_insert);
	}
	printf("\n");
	SortedListDestroy(dest1);
	SortedListDestroy(src1);
}

/*****************************************************************************/


	
























 


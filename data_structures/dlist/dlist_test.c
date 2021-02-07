/* 
* File Name: dlist_test.c
* Description: Test functions for dlist API functions
* Developer: Guy Chen
* Date: 19.06.2020
*/

#include <stdio.h>
#include "dlist.h"

#define TRUE 1
#define FALSE 0

enum DO_ACTION_STATUS
{
	SUCCESS = 0,
	FAILURE
};


/************************** Functions Decleration ****************************/

static dlist_t *DListCreateTest(void);
static void DListDestroyTest(dlist_t *dlist);
static void DListBeginTest(const dlist_t *dlist);
static void DListEndTest(const dlist_t *dlist);
static void DListNextTest(dlist_t *dlist);
static void DListPrevTest(dlist_t *dlist);
static void DListGetDataTest(dlist_t *dlist);
static void DListSetDataTest(dlist_t *dlist);
static void DListIterIsEqualTest(dlist_t *dlist);
static void DListIsEmptyTest(dlist_t *dlist);
static void DListInsertTest(dlist_t *dlist);
static void DListSizeTest(dlist_t *dlist);
static void DListRemoveTest(dlist_t *dlist);
static void DListPushFrontTest(dlist_t *dlist);
static void DListPushBackTest(dlist_t *dlist);
static void DListPopFrontTest(dlist_t *dlist);
static void DListPopBackTest(dlist_t *dlist);
static void DListFindTest(dlist_t *dlist);
static void DListForEachTest(dlist_t *dlist);
static void DListSpliceTest(dlist_t *src, dlist_t *dest);

static void TestCaseAPI1(void);
static void TestCaseAPI2(void);
/*****************************************************************************/

int DListIs_Match(const void *data, void *param);
int DListDo_Action(void *data, void *param);

/**************************** main function **********************************/

int main(void)
{
    dlist_t *dlist = NULL;    
 
    dlist = DListCreateTest();
   	/* DListEndTest(dlist);
    DListNextTest(dlist);
    */
    DListDestroyTest(dlist);

	TestCaseAPI1();
	TestCaseAPI2();
	return (0);
}

/************************** Functions Defenition ****************************/

static dlist_t *DListCreateTest(void)
{
	dlist_t *dlist = NULL;
	
	dlist = DListCreate();
	if (NULL != dlist)
	{
		printf("The creation of dlist succeeded\n");
	}
	else
	{
		printf("The creation of dlist didn't succeeded\n");
    }
  
    return (dlist);
}

/*****************************************************************************/

static void DListDestroyTest(dlist_t *dlist)
{
    DListDestroy(dlist);
    printf("The dlist has been destroyed\n");
}

/*****************************************************************************/

static void DListBeginTest(const dlist_t *dlist)
{
    dlist_iter_t iter_begin = NULL;
    
    iter_begin = DListBegin(dlist);
    printf("The first elements is in adress %p\n",(void*) iter_begin);
}

/*****************************************************************************/

static void DListEndTest(const dlist_t *dlist)
{
    dlist_iter_t iter_end = NULL;
    
    iter_end = DListEnd(dlist);
    printf("The list ends with the uterator %p\n",(void*) iter_end);
}

/*****************************************************************************/

static void DListNextTest(dlist_t *dlist)
{
    dlist_iter_t iter_next = NULL;
    dlist_iter_t curr_iter = DListBegin(dlist);    

    iter_next = DListNext(curr_iter);
    printf("The curr iteris: %p, the next element is:%p\n",
            (void*) curr_iter, (void*) iter_next);
}   
/*****************************************************************************/

static void DListPrevTest(dlist_t *dlist)
{
    dlist_iter_t iter_prev = NULL;
    dlist_iter_t curr_iter = DListEnd(dlist);  
    
    iter_prev = DListPrev(curr_iter);
     printf("The curr iteris: %p, the prev element is:%p\n",
            (void*) curr_iter, (void*) iter_prev);
}      

/*****************************************************************************/
  
static void DListGetDataTest(dlist_t *dlist)
{
    dlist_iter_t curr_iter = DListBegin(dlist);  
    void * data = NULL;

    data = DListGetData(curr_iter);

    printf("the data in elment %p is %ls\n", (void*)curr_iter, (int*)data);
}

/*****************************************************************************/

static void DListSetDataTest(dlist_t *dlist)
{
    dlist_iter_t curr_iter = DListBegin(dlist);  
    void *data = NULL;
    
    DListSetData(curr_iter, data);
    if(data == DListGetData(curr_iter))
    {
        printf("set data succeeded\n");
    }
    else
    {
         printf("set data didn;t succeed\n");
    }
}

/*****************************************************************************/

static void DListIterIsEqualTest(dlist_t *dlist)
{
    dlist_iter_t iter1 = DListBegin(dlist); 
    dlist_iter_t iter2 = DListBegin(dlist); 

    if(TRUE == DListIterIsEqual(iter1, iter2)) 
    {
        printf("The 2 iterators are equals\n");
    }   
    else
    {
        printf("The 2 iterators aren't equals\n");
    }           
}

/*****************************************************************************/

static void DListIsEmptyTest(dlist_t *dlist)
{
    if (DListIsEmpty(dlist))
    {
        printf("the dlist is empty\n");
    }
    else
    {
        printf("the dlist is not empty\n");
    }        
}

/*****************************************************************************/

static void DListInsertTest(dlist_t *dlist)
{ 
    void *data = (int*) 3;
    dlist_iter_t new_element = NULL;
    dlist_iter_t curr_iter = DListEnd(dlist);    
             
    new_element = DListInsert(dlist, curr_iter, data);
    if(new_element == DListEnd(dlist))
    {   
         printf("The isertion of new element didn't succeed\n");
    }
    else
    {
         printf("The isertion of new element succeeded\n");
    }        
}

/*****************************************************************************/
static void DListSizeTest(dlist_t *dlist)
{
	size_t size = 0;
	
	size = DListSize(dlist);
	printf("The size of the dlist is: %lu\n", size);
}

/*****************************************************************************/

static void DListRemoveTest(dlist_t *dlist)
{	
	dlist_iter_t curr_iter = DListBegin(dlist);
	
	printf("The current iterator is %p\n", (void*)curr_iter);
	curr_iter = DListRemove(curr_iter);
	printf("After removing current iterator is %p\n", (void*)curr_iter);	
}

/*****************************************************************************/

static void DListPushFrontTest(dlist_t *dlist)
{
	void *data = (int*) 1;
    dlist_iter_t new_element = NULL;
    dlist_iter_t curr_iter = DListBegin(dlist); 
	
	new_element = DListPushFront(dlist, data);
    if(new_element == DListEnd(dlist))
    {   
         printf("The isertion of new element to the front of the list didn't\
 				succeed\n");
    }
    else
    {
         printf("The isertion of new element to the  of the list succeeded\n");
    }        
}   
	
/*****************************************************************************/

static void DListPushBackTest(dlist_t *dlist)	
{
	void *data = (int*) 4;
    dlist_iter_t new_element = NULL;
    dlist_iter_t curr_iter = DListEnd(dlist);    
             
    new_element = DListPushBack(dlist, data);
    if(new_element == DListEnd(dlist))
    {   
         printf("The isertion of new element to the back of the list\
				didn't succeed\n");
    }
    else
    {
         printf("The isertion of new element to the back of the list\
				succeeded\n");
    }        
}

/*****************************************************************************/

static void DListPopFrontTest(dlist_t *dlist)
{
	void *data = NULL;

	data = DListGetData(DListBegin(dlist)); 
	printf("The data of the needed poped element is: %p\n", data);	
	data = DListPopFront(dlist);
	
	printf("The data of the poped element is: %p\n", data);
}
	
/*****************************************************************************/

static void DListPopBackTest(dlist_t *dlist)
{
	void *data = NULL;
	dlist_iter_t last_element = NULL;	

	last_element = DListPrev(DListEnd(dlist));
	data = DListGetData(last_element); 
	printf("The data of the needed poped element is: %p\n", data);	
	data = DListPopBack(dlist);
	printf("The data of the poped element is: %p\n", data);
}

/*****************************************************************************/

static void DListFindTest(dlist_t *dlist)
{
	dlist_iter_t res_iter = NULL;
	int num = 10;
	int num_par = 5;
	void *data = &num;
	void *param = &num_par;

	res_iter = DListFind(DListBegin(dlist), DListPrev(DListEnd(dlist)), 
						 &DListIs_Match, param);

	if(res_iter == DListPrev(DListEnd(dlist)))
	{
		printf ("there is no match\n");
	}
	else
	{
		printf ("there is a match\n");	
	}
}		

/*****************************************************************************/

static void DListForEachTest(dlist_t *dlist)
{
	int do_action_status = FAILURE;
	int y =5;
	void *param = &y;
	
	do_action_status = DListForEach(DListBegin(dlist), 
									DListPrev(DListEnd(dlist)), &DListDo_Action,
									param);
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

static void DListSpliceTest(dlist_t *src, dlist_t *dest)
{
	dlist_iter_t last_spliced_element = NULL;	
	dlist_iter_t from = DListBegin(src);
	dlist_iter_t to	= DListPrev(DListEnd(src));
	dlist_iter_t where = DListBegin(dest);
	
	printf("The last spliced element need to be %p\n", (void*) DListPrev(to));
	last_spliced_element = DListSplice(from, to, where);
	printf("The last spliced element is %p\n", (void*) last_spliced_element);
}		


/*****************************************************************************/

int DListIs_Match(const void *data, void *param)
{
    return (*(int *)data == *(int *)param);
}

/*****************************************************************************/

int DListDo_Action(void *data, void *param)
{
    *(int *)data += *(int *)param;

    return (0);
}

/*****************************************************************************/


static void TestCaseAPI1(void)
{

	dlist_t *dlist = NULL;    
	printf("*********************TEST CASE API 2 **********************\n");	

    dlist = DListCreateTest();
	DListIsEmptyTest(dlist);
	DListSizeTest(dlist);
	DListInsertTest(dlist);
	DListPushFrontTest(dlist);
	DListSizeTest(dlist);	
	DListPushFrontTest(dlist);
	DListPushFrontTest(dlist);
	DListIsEmptyTest(dlist);
	DListSizeTest(dlist);
	DListPopFrontTest(dlist);
	DListSizeTest(dlist);
	DListPushBackTest(dlist);
	DListSizeTest(dlist);
	DListPopBackTest(dlist);
	DListSizeTest(dlist);
    DListDestroyTest(dlist);

}


static void TestCaseAPI2(void)
{
	dlist_t *dlist = NULL;    
	dlist_t *dlist2 = NULL;
 
	printf("\n\n*********************TEST CASE API 2 **********************\n");

    dlist = DListCreateTest();
	dlist2 = DListCreateTest();	 
	DListIsEmptyTest(dlist);
	DListSizeTest(dlist);
	DListInsertTest(dlist);
	DListPushFrontTest(dlist);
	DListSizeTest(dlist);	
	DListPushFrontTest(dlist);
	DListPushFrontTest(dlist);
	DListIsEmptyTest(dlist);
	DListSizeTest(dlist);
	DListPopFrontTest(dlist);
	DListSizeTest(dlist);
	DListPushBackTest(dlist);
	DListSizeTest(dlist);
	DListPopBackTest(dlist);
	DListSizeTest(dlist);
    
	DListIsEmptyTest(dlist2);
	DListSizeTest(dlist2);
	DListInsertTest(dlist2);
	DListPushFrontTest(dlist2);
	DListSizeTest(dlist2);	
	DListSpliceTest(dlist, dlist2);



	DListDestroyTest(dlist);
	DListDestroyTest(dlist2);

}
















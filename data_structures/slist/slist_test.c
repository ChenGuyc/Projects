/* 
* File Name: slist_test.c
* Description: Testing slist API functions
* Developer: Guy Chen
* Date: 11.06.2020
*/

#include <stdio.h>
#include "slist.h"

#define TRUE 1
#define FALSE 0

enum API_status
{
	SUCCESS = 0,
	FAILURE
};





/****************** Test functions declarations ******************************/
/*
static slist_t *SListCreateTest(void);
static void SListDestroyTest(slist_t *slist);
static void SListIsEmptyTest(const slist_t *slist);
static void SListEndTest(const slist_t *slist);
static void SListBeginTest(const slist_t *slist);
static void SlistNextTest(void);
static void SListGetDataTest(slist_t *slist);
static void SlistSetDataTest(void);
static void SListIterIsEqualTest(slist_t *slist);
static void SListInsertAfterTest(slist_t *slist);
static void SListInsertTest(slist_t *slist);
static void SListCountTest(const slist_t *slist);
static void SListRemoveTest(slist_t *slist);
static void SListFindTest(slist_t *slist); 
static void SListForEachTest(slist_t *slist);
*/
/*****************************************************************************/
/*
static void TestAPI1And2(void)
{
	slist_t *slist = SListCreate();
	printf("slist was created\n");
	SListDestroy(slist);
	printf("slist has been destroyed created\n");
}
*/
/*****************************************************************************/
/*
static void TestAPI3(void)
{
	slist_t *slist = SListCreate();
	printf("slist was created\n");
	if (1 == SListIsEmpty(slist))
	{
		printf("slist is empty\n");
	}	
	else
	{
		printf("slist is not empty\n");
	}
	SListDestroy(slist);
	printf("slist has been destroyed created\n");
}
*/
/*****************************************************************************/
/*
static void TestAPI4(void)
{
	slist_iter_t new_node = NULL;
	slist_t *slist = SListCreate();
	printf("slist was created\n");
	new_node = SListInsert(slist, SListEnd(slist), (int *) 2);
	printf("new node was created\n");
	printf("the adress of new node is %p\n", (void*) new_node);	
	SListDestroy(slist);
	printf("slist has been destroyed created\n");
}
*/
/*****************************************************************************/
/*
static void TestAPI5(void)
{
	slist_iter_t new_node = NULL;
	slist_t *slist = SListCreate();
	printf("slist was created\n");
	new_node = SListInsert(slist, SListEnd(slist), (int *) 2);
	printf("new node was created\n");
	printf("the adress of new node is %p\n", (void*) new_node);	
	new_node= SListInsertAfter(slist, SListBegin(slist), (int *) 4);
	printf("new node was created\n");
	printf("the adress of new node is %p\n", (void*) new_node);	 		
	SListDestroy(slist);
	printf("slist has been destroyed created\n");
}	
*/
/*****************************************************************************/
/*
static void TestAPI6(void)
{
	slist_iter_t new_node = NULL;
	slist_t *slist = SListCreate();
	printf("slist was created\n");
	new_node = SListInsert(slist, SListEnd(slist), (int *) 2);
	printf("new node was created\n");
	printf("the adress of new node is %p\n", (void*) new_node);	
	new_node= SListInsertAfter(slist, SListBegin(slist), (int *) 4);
	printf("new node was created\n");
	printf("the adress of new node is %p\n", (void*) new_node);	 	
	new_node = SListBegin(slist);
	printf("current head next is %p\n",(void *) new_node);
	new_node = SListRemove(slist, new_node);
	printf("current head next after remove is %p\n",(void *) new_node); 		
	SListDestroy(slist);
	printf("slist has been destroyed created\n");
}
	*/
/****************** main function ********************************************/

int main(void)
{
	/*

	slist_t *slist = NULL;
	slist = SListCreateTest();
	
	SListIsEmptyTest(slist);
	SListEndTest(slist);	
	SListBeginTest(slist);	
	SListInsertTest(slist);
	SListBeginTest(slist);
	SListIsEmptyTest(slist);	
	SListInsertAfterTest(slist);	
	SListCountTest(slist);	
	SListGetDataTest(slist);	
	SListIterIsEqualTest(slist);
	SListFindTest(slist);	
	SListForEachTest(slist);	
	SListRemoveTest(slist);	
	SListCountTest(slist);
	SListDestroyTest(slist);
	TestAPI1And2();
	TestAPI3();
	TestAPI4();
	TestAPI5();
	TestAPI6();

*/	

	return 0;

}



/****************** Test functions defenitions *******************************/


/* Test fucntion for SListCreate funcion */ 

static slist_t *SListCreateTest(void)
{	
	slist_t *slist = NULL;
	slist = SListCreate();
	if (slist)
	{
		printf("the slist has been created\n");
	}
	else
	{
		printf("the creation of the slist didn't succeed\n");
	}
	return (slist);
	
}
	
/*****************************************************************************/

/* Test fucntion for SListCreate funcion */ 

static void SListDestroyTest(slist_t *slist)
{
	SListDestroy(slist);
	printf("the slist has been destroyed\n");
}


/*****************************************************************************/

/* Test fucntion for SListIsEmpty funcion */ 

static void SListIsEmptyTest(const slist_t *slist)
{
	int is_empty = 0;
	
	is_empty = SListIsEmpty(slist);
	if (is_empty)
	{
		printf("the list is empty\n");
	}
	else 
	{
		printf("the list is not empty\n");
	}
}

/*****************************************************************************/

/* Test fucntion for SListEnd funcion */ 

static void SListEndTest(const slist_t *slist)
{
	slist_iter_t end_of_list;

	end_of_list = SListEnd(slist);
	printf("the itrator of end of the list is %p\n",(void*) end_of_list);
}


/*****************************************************************************/

/* Test fucntion for SListBegin funcion */ 

static void SListBeginTest(const slist_t *slist)
{
	slist_iter_t begin_of_list;

	begin_of_list = SListBegin(slist);
	printf("the itrator of begin of the list is %p\n",(void*) begin_of_list);
}
	

/*****************************************************************************/

/* Test fucntion for SlistNext funcion */ 
/*
static void SlistNextTest(void)
{
	slist_iter_t iter; 
	slist_iter_t next_iter = NULL;

	next_iter = SlistNext(iter);	
	printf("the next itrator is %p\n",(void*) next_iter);
}
*/

/*****************************************************************************/

/* Test fucntion for SListGetData funcion */ 

static void SListGetDataTest(slist_t *slist)
{
	slist_iter_t iter;
	void *data_in_iter = NULL;
	iter = SListBegin(slist);
	data_in_iter = SListGetData(iter);
	printf("The data in iter %p is: %p\n", (void*) iter, data_in_iter);
}

/*****************************************************************************/

/* Test fucntion for SListSetData funcion */ 
/*
static void SlistSetDataTest(void)
{
	slist_iter_t iter;
	void *data = NULL;
	void *curr_data = NULL;
	
	curr_data = SListGetData(iter);
	printf("The current dta is %p\n", curr_data);	
	SlistSetData(iter,data);
*/	/* after setting new data */
/*	curr_data = SListGetData(iter);
	printf("The current dta is %p\n", curr_data);
}		
*/
/*****************************************************************************/

/* Test fucntion for SListIterIs funcion */ 
/*
static void SListIterIsEqualTest(slist_t *slist)
{
	int is_equal = 0;	
	slist_iter_t iter1; 
	slist_iter_t iter2;
	iter1 = SListBegin(slist);
	iter2 = SListBegin(slist);	
	iter2 = SlistNext(iter1);
	
	
	is_equal = SListIterIsEqual(iter1,iter2);
	if (is_equal)
	{
		printf("The two iterators are equals\n");
	}
	else
	{
		printf("The two iterators are not equals\n");
	}
}		
*/	
/*****************************************************************************/

/* Test fucntion SListInsertAfter funcion */ 

static void SListInsertAfterTest(slist_t *slist)
{
	slist_iter_t new_node;
	int y = 4;
	void *data = &y;
	slist_iter_t where = SListBegin(slist);
	
	new_node = SListInsertAfter(slist, where, data);
	if (NULL != new_node)
	{
		printf("The insertion of new node after the given Itrator succeeded\n");
		printf("The adress of new_node is %p\n" , (void*)new_node);
	}
	else
	{
		printf("The insertion of new node didn't succeed\n");
		printf("hence the adress is as end %p\n" , (void*)new_node);
	}
}

/*****************************************************************************/

/* Test fucntion SListInsert funcion */ 

static void SListInsertTest(slist_t *slist)
{
	slist_iter_t new_node;
	int x = 3;		
	void *data = &x; 	
	slist_iter_t where = SListEnd(slist);	

	
	new_node = SListInsert(slist, where, data);
	if (NULL != new_node)
	{
		printf("The insertion of new node before the given Itrator succeeded\n");
		printf("The adress of new_node is %p\n" , (void*)where);
	}		
	else
	{
		printf("The insertion of new node didn't succeed\n");
		printf("hence the adress is as end %p\n" , (void*)new_node);
	}
	SListBeginTest(slist);
}

/*****************************************************************************/

/* Test fucntion SListCount funcion */

static void  SListCountTest(const slist_t *slist)
{
	size_t counter = 0;
	
	counter = SListCount(slist);
	printf("The number of element in the list is: %lu\n", counter);
}

/*****************************************************************************/

/* Test fucntion SListRemove funcion */

static void SListRemoveTest(slist_t *slist)
{
	slist_iter_t iter = SListBegin(slist);
	
	printf("the current data before remove is: %p\n" ,(void*) iter);	
	iter = SListRemove(slist, iter);
	printf("the current data after remove is: %p\n" ,(void*) iter);	
}	

/*****************************************************************************/

int IsMatch(void *data, void *param)
{
	if (data == param)
	{
		return (TRUE);
	}
	return (FALSE);
}

/*****************************************************************************/

int DoAction(void *data, void *param)
{
	*(int*)data *= *(int*)param;
	return (TRUE);
}

/*****************************************************************************/
static void  SListFindTest(slist_t *slist)
{
	slist_iter_t res = NULL;
	int num = 10;
	void *data = &num;
	void *param = (SListBegin(slist));
	
	res = SListFind(SListBegin(slist), SListEnd(slist), &IsMatch, param);
	
	if (res == SListEnd(slist))
	{
		printf ("there is no match\n");
	}
	else
	{
		printf ("there is a match\n");	
	}
}

/*****************************************************************************/

static void SListForEachTest(slist_t *slist)
{
	int res = FAILURE;
	int y = 5;
	void *param = SListBegin(slist); 
	void *param2 = SListEnd(slist);
	res = SListForEach(param, param, &IsMatch, param);

	if (!res)
	{
		printf("the action succeeded for all the elements\n");
	}
	else
	{
		printf("the action didn't succeed for all the elements\n");
	}
}


/*****************************************************************************/



	

	






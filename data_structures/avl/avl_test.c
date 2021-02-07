/* *******************************************************
* File Name: avl_test.c								     *
* Description: Defenitions of test function for AVL API  *
* Developer: Guy Chen									 *         					 *
* Date: 31.07.2020										 *
*********************************************************/

#include <stdio.h> /*prinff*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /*assert */

#include "avl.h"

#define UNUSED(x) (void)(x)

#define ARR_SIZE 10

/******************************************************************************/

static avl_t *AVLCreateTest(void);
static void AVLDestroyTest(avl_t *avl);
static void AVLSizeTest(const avl_t *avl);
static void AVLIsEmptyTest(const avl_t *avl);
static void AVLInsertTest(avl_t *avl, void *data);
static void AVLFindTest(const avl_t *avl, const void *data);
static void PrintRoot(avl_node_t *node);
void PrintAVLRootTest(avl_t *avl);
static void AVLForEachTest(avl_t *avl);
static void AVLRemoveTest(avl_t *avl, void *data);

/*****************************************************************************/

static int Cmp(const void *data1, const void *data2, void *param);
static int DoAction(void *data, void *param);


/********************** main funtion **************************/

int main(void)
{
    avl_t *avl = NULL;
    int num = 5;
    void *data1 = (void*)num;
    void *data = NULL;
    avl = AVLCreateTest();
    AVLSizeTest(avl);
    AVLIsEmptyTest(avl);
    AVLInsertTest(avl, data1);
    num = 3;
    data = (void*)num;
    AVLInsertTest(avl, data);
    AVLSizeTest(avl);
    AVLFindTest(avl, data);
    num = 2;
    data = (void*)num;
    AVLInsertTest(avl, data);
    AVLForEachTest(avl);
    AVLRemoveTest(avl, &num);
    AVLDestroyTest(avl);
    
    return (0);
}


/********************** Defintion of compare funtion **************************/

static int Cmp(const void *data1, const void *data2, void *param)
{
    int *num1 = (int *)data1;
    int *num2 = (int *)data2;

    UNUSED(param);

    return (num1 > num2) - (num1 < num2);
}

/********************** Defintion of DoAction funtion *************************/

static int DoAction(void *data, void *param)
{
    int *num1 = (int *)data;
    int *num2 = (int *)param;

    *num1 *=  *num2;
    
    return (0);
}

/******************************************************************************/

static avl_t *AVLCreateTest(void)
{
    avl_t *avl = NULL;
    void *param = NULL;
    
    avl = AVLCreate(Cmp, param);
    if(avl)
    {
        printf("The creation of avl tree succeeded\n");
    }
    else
    {
        printf("The creation of avl tree didn't succeed\n");
    }
    return (avl);
}

/******************************************************************************/

static void AVLDestroyTest(avl_t *avl)
{
    AVLDestroy(avl);

    printf("The avl tree has been destroyed\n");
}

/******************************************************************************/

static void AVLSizeTest(const avl_t *avl)
{
    size_t size = 0;
    size = AVLSize(avl);

    printf("The current size of the avl tree is %lu\n", size);
}

/******************************************************************************/

static void AVLIsEmptyTest(const avl_t *avl)
{
    int res = 0; 
    
    res = AVLIsEmpty(avl);
  
    if (res)
    {
        printf("The avl tree is empty\n");
    }
    else
    {
        printf("The avl tree is not empty\n");
    }  
}

/******************************************************************************/

static void AVLInsertTest(avl_t *avl, void *data)
{
    int status = 0;

    status = AVLInsert(avl, data);

    if (0 == status)
    {
        printf("The data: [%lu] was inserted to the avl tree\n", (size_t )data);
    }
    else
    {
        printf("The data: [%lu] wasn't inserted to the avl tree\n",\
                 (size_t)data);
    }
}

/******************************************************************************/

static void AVLFindTest(const avl_t *avl, const void *data)
{
    void *tmp_data = NULL;

    tmp_data = AVLFind(avl, data);
    if (!tmp_data)
    {
        printf("The data wasn't found in the avk tree\n");
    }
    else
    {
        printf("The data was found at %p: \n", tmp_data);
    }
    
}


/******************************************************************************/

static void AVLForEachTest(avl_t *avl)
{
    int num = 2;
  
    int res = 0;

    res = AVLForEach(avl, DoAction, &num);
    if (0 == res)
    {
        printf("The action was operated to all the range\n");
    }
    else
    {
        printf("The action wasn't operated to all the range\n");
    }
}

/******************************************************************************/

static void AVLRemoveTest(avl_t *avl, void *data)
{
    size_t size = 0;
    size = AVLSize(avl);

    printf("The size before remove is %lu\n", size);

    AVLRemove(avl,data);

    size = AVLSize(avl);

    printf("The size afer remove is %lu\n", size);
}

/******************************************************************************/
static void PrintRoot(avl_node_t *node)
{   
    Inorder(node);
}
/******************************************************************************/


/******************************************************************************/


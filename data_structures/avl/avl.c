/*********************************************************
* File Name: avl_test.c								     *
* Description: Defenitions of AVL API functions          *
* Developer: Guy Chen									 *           					 *
* Date: 31.07.2020										 *
*********************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdbool.h> /* true, false */
#include <stdio.h> /*prinff*/

#include "avl.h"

#define DEADBEEF 0xDEADBEEF 

enum status
{
    SUCCESS = 0,
    FAILURE = 1
};
/*
typedef struct avl_node avl_node_t;
*/
struct avl_node
{
    void *data;
    avl_node_t *right;
    avl_node_t *left;
};

struct avl 
{
    avl_node_t *root;
    avl_cmp_func_t cmp;
    void *param;
};

/*************************** utility functions ********************************/

static avl_node_t *CreateNewNode(avl_node_t *new_node, void *data);
static avl_node_t *LeftRotate(avl_node_t *root);
static avl_node_t *RightRotate(avl_node_t *root);
avl_node_t *LeftRightRotate(avl_node_t *root);
avl_node_t *RightLeftRotate(avl_node_t *root);
static int BalanceFactor(avl_node_t *node);
static int Height(avl_node_t *node);
static int Max (size_t num1, size_t num2);

static int InOrderForEach(avl_node_t *node,avl_do_action_func_t do_action, 
                    void *param);
int Balance(avl_node_t *node);
avl_node_t *RebalanceTheTree(avl_node_t *node);
size_t NodeHeight(avl_node_t *node);
avl_node_t *MinClosestNode(avl_node_t *node);
avl_node_t *RemoveFromTree(avl_t *avl, avl_node_t *node, void *data);

/***************************** recursion functions*****************************/

static void AVLFree(avl_node_t *node);
static size_t GetAVLSize(avl_node_t *node);
static avl_node_t *InsertNewNode(avl_t *avl, avl_node_t *node, 
                                 void * data);
static avl_node_t *Search(const avl_t *avl, avl_node_t *node, const void *data);


/******************************************************************************/

avl_t *AVLCreate(avl_cmp_func_t cmp, void *param)
{
    avl_t *avl = NULL;

    avl = (avl_t*)malloc(sizeof(avl_t));
    if (NULL == avl)
    {
        return(NULL);
    }
    
    avl->cmp = cmp;
    avl->param = param;
    avl->root = NULL;

    return (avl);
}

/******************************************************************************/

void AVLDestroy(avl_t *avl)
{
    assert(avl);
    
    if(!AVLIsEmpty(avl))
    {
        AVLFree(avl->root);
    }
    
    free(avl);
    avl = NULL;
}

/******************************************************************************/

size_t AVLSize(const avl_t *avl)
{
    assert(avl);

    return (GetAVLSize(avl->root));
}

/******************************************************************************/

int AVLIsEmpty(const avl_t *avl)
{
    assert(avl);

    return (NULL == avl->root);
}

/******************************************************************************/

int AVLInsert(avl_t *avl, void *data)
{
    avl_node_t *node = NULL;

    assert(avl);

    node = avl->root;

    node = InsertNewNode(avl, node, data);
    
    return(NULL == node);
}

/******************************************************************************/

void AVLRemove(avl_t *avl, void *data)
{
	avl_node_t *root = NULL;

	assert(avl);

    root = avl->root;
	if (!AVLIsEmpty(avl))
	{
		RemoveFromTree(avl, root, data);
	}
}


/******************************************************************************/

void *AVLFind(const avl_t *avl, const void *data)
{
    avl_node_t *node = NULL;                                    

    assert(avl);

    node = Search(avl, avl->root, data);

    return ((void*)node);
}

/******************************************************************************/

int AVLForEach(avl_t *avl, avl_do_action_func_t do_action ,void *param)
{
    int status = 0;

    assert(avl);

    status = InOrderForEach(avl->root, do_action, param);
    return(status);
}

/******************************************************************************/

static int InOrderForEach(avl_node_t *node, avl_do_action_func_t do_action, 
                          void *param)
{
    /* checking if the root is not null */
    if(node != NULL) 
    {
        /* visiting left child */
        InOrderForEach(node->left, do_action, param); 
        /* printing data at root */
        if((do_action(&node->data, param)) == FAILURE)
        {
            return (FAILURE);
        }
        /*visiting right child */ 
        InOrderForEach(node->right, do_action, param);
    }

    return (SUCCESS); 
}

/******************************************************************************/

static void AVLFree(avl_node_t *node)
{
    if(!node)
    {
        return;
    }
    AVLFree(node->left);
    AVLFree(node->right);

    free(node);
    node = NULL;
}

/******************************************************************************/

static size_t GetAVLSize(avl_node_t *root)
{
    if (!root)
    {
        return (0);
    }
    else
    {
        return(1 + (GetAVLSize(root->left) + GetAVLSize(root->right)));
    }
}

/******************************************************************************/

static avl_node_t *InsertNewNode(avl_t *avl, avl_node_t *node, 
                                 void * data)
{
    avl_node_t *new_node = NULL;
 /*if root cahnged due to rotation */   
    int is_root_changed = 0;

    assert(avl);
   
    if (node == NULL)
    {
        new_node = CreateNewNode(new_node, data);
    
        if (!avl->root)
        {
            avl->root = new_node;
        }
        return (new_node);
    }

    if(0 != (avl->cmp(node->data, data,avl->param)))
    {
        if (0 < (avl->cmp(node->data, data,avl->param)))
        {
            node->left = InsertNewNode(avl, node->left, data);
        }
        else
        {
            node->right = InsertNewNode(avl, node->right, data);
        }
        if (avl->root == node)
        {
            is_root_changed = !is_root_changed;
        }
            
        node = RebalanceTheTree(node);
    }

    if(is_root_changed)
    {
        is_root_changed = !is_root_changed;
        avl->root = node;
    }

    return (node);
}

/******************************************************************************/

avl_node_t *RebalanceTheTree(avl_node_t *node)
{
    if (1 < BalanceFactor(node))
    {
        if (NodeHeight(node->left->left) >= NodeHeight(node->left->right))
        {
            node = RightRotate(node);
        }
        else
        {
            node = LeftRightRotate(node);
        }
    }
    else if(-1 > BalanceFactor(node))
    {
        if (NodeHeight(node->right->right) >= NodeHeight(node->right->left))
        {
            node = LeftRotate(node);
        }
        else
        {
            node = RightLeftRotate(node);
        }
    }

    return (node);
}

/******************************************************************************/

int BalanceFactor(avl_node_t *node)
{
	return (NodeHeight(node->left) - NodeHeight(node->right));
}

/******************************************************************************/

size_t NodeHeight(avl_node_t *node)
{
	size_t height = 0;

	/* this condition ignores leaves so it counts only the linkes  */
	if (node == NULL || (node->left == NULL && node->right == NULL))
	{
		return 0;
	}

	height = Max(NodeHeight(node->left), NodeHeight(node->right));

	return ++height;
}

/******************************************************************************/

avl_node_t *RemoveFromTree(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *temp_node = NULL;
	/* variable to check whether the root has been changed during rebalancing */
	int is_root_changed = 0; 

    assert(avl);

	/* deletion part */
	if (avl->cmp(node->data, data, NULL) == 0)
	{
		/* node to remove has no children */
		if (node->left == NULL && node->right == NULL)
		{
			free(node);
            node = NULL;
			return (NULL);
		}
		/* node to remove has one child */
		else if ((node->left == NULL && node->right) || 
				 (node->left && node->right == NULL))
		{		
			if (node->left)
			{
				temp_node = node->left;
				free(node);
                node = NULL;
				return (temp_node);
			}
			else
			{
				temp_node = node->right;
				free(node);
                node = NULL;
				return(temp_node);
			}
		}
		/* node to remove has two children */
		else
		{
			temp_node = MinClosestNode(node);
			node->data = temp_node->data;		
			node->right = RemoveFromTree(avl, node->right, node->data);
			return (node);			
		}
	}
	
	/* scanning part */
	else if (avl->cmp(node->data, data, NULL) > 0 && node->left != NULL)		
	{
		node->left = RemoveFromTree(avl, node->left, data);
	}
	else if (avl->cmp(node->data, data, NULL) < 0 && node->right != NULL)
	{
		node->right = RemoveFromTree(avl, node->right, data);
	}

	if (node == avl->root)
	{
		is_root_changed = !is_root_changed;
	}

	/* rebalancing part */
	node = RebalanceTheTree(node);

	if (is_root_changed)
	{
		is_root_changed = !is_root_changed;
		avl->root = node;
	}

	return (node);	
}

/******************************************************************************/

avl_node_t *MinClosestNode(avl_node_t *node)
{
	if (node->right != NULL)
	{
		node = node->right;
	}
	
	while (node->left != NULL)
	{
		node = node->left;
	}

	return (node);	
}

/******************************************************************************/

void Inorder(avl_node_t *node)
{
    /* checking if the root is not null */
    if(node->next != NULL && (node->status & 0xFF) != 1) 
    {
        /* visiting left child */
        Inorder(node->left); 
        /* printing data at root */
        printf("The value is [%p]\n ",(void*) node->data); 
        /*visiting right child */ 
        Inorder(node->right); 
    }
	else 
	{
		node->next = CreateNode(node);
	}
	
}

/******************************************************************************/

static avl_node_t *Search(const avl_t *avl, avl_node_t *node, const void *data)
{
    assert(avl);

    /* if node->data is x then the element is found */
    if(NULL == node || data == node->data) 
    {
        return (node);
    }    
    /* x is greater, so we will search the right subtree */
    else if(0 < avl->cmp(data,node->data, avl->param)) 
    {
        return Search(avl,node->right, data);
    }   
    /* x is smaller than the data, so we will search the left subtree */ 
    else
    {
        return Search(avl, node->left, data);
    } 
}

/******************************************************************************/

static avl_node_t *CreateNewNode(avl_node_t *new_node, void *data)
{
    new_node = (avl_node_t*)malloc (sizeof(avl_node_t));
 
    if (NULL == new_node)
    {
        return (NULL);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return(new_node);
}

/******************************************************************************/

static avl_node_t *RightRotate(avl_node_t *root)
{
	avl_node_t *current = root->left;
	
	root->left = current->right;
	current->right = root;

	return (current);
}

/******************************************************************************/

static avl_node_t *LeftRotate(avl_node_t *root)
{
	avl_node_t *current = root->right;
	
	root->right = current->left;
	current->left = root;

	return (current);
}

/******************************************************************************/

avl_node_t *RightLeftRotate(avl_node_t *root)
{
	avl_node_t *current = root;
	avl_node_t *temp = NULL;

	root = root->right;
	temp = root->left;
	
    root->left = temp->right;
	temp->right = root;
	current->right = temp;

	current = LeftRotate(current);

	return (current);
}


/******************************************************************************/

avl_node_t *LeftRightRotate(avl_node_t *root)
{
	avl_node_t *current = root;
	avl_node_t *temp = NULL;

	root = root->left;
	temp = root->right;
	
    root->right = temp->left;
	temp->left = root;
	current->left = temp;

	current = RightRotate(current);

	return (current);
}

/******************************************************************************/
static int Max (size_t num1, size_t num2)
{
    return (num1 > num2 ? num1 : num2);
}

/******************************************************************************/










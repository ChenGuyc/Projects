/**********************************************************************
* File Name: dhcp.c            					    				  *
* Name: Guy Chen								    	    		  *
* Create Date: 18.8.2020	    					                  * 	
* Topic: dhcp C file            									  *
**********************************************************************/
/*
Notes: The DS I use for dhcp is Trie, the algorithem I used in the functions is that the root is at height 32 and the leaf is at height mask_bits_size I get from the user.
Since each node can have 2 childrens I need at first to check if I can move on to the left direction, if not I will check if it is leaf by the Heifht, if it not a leaf I will move on to the right direction.
By the time 2 leaf of the same parent will be turned to occupied their parent's status will be turned to occupied as well. 
*/

#include <assert.h>     /* assert */
#include <stdint.h>     /* uint32_t */
#include <arpa/inet.h>  /* inet_ntop */
#include <stdlib.h>     /* malloc, free */
#include <string.h>      /*memcpy*/

#include "dhcp.h"

#define MSB 32
#define MAX_SIZE 32

typedef enum
{
    LEFT = 0,       /*MUST BE 0- DONT CHANGE!*/
    RIGHT = 1       /*MUST BE 1- DONT CHANGE!*/
} children;

typedef struct node
{
    struct node *children[2];       /* children of node */
    /* The 6 riht bits represt the hight of node starting from 32, 
     * The most left bit represent if the node is occupied or not occupied it 2 
     * 2 ways: (1) The node is leaf, (2) The subtree in both direction is full */
    unsigned char status;        
}node_t;

struct dhcp
{
    node_t *root;
    uint32_t net_address;
    unsigned int mask_bits_size;
};

/* recursive functions called by api */
static void Destroyrecursive(dhcp_t *dhcp, node_t *node);
static int GetAddressrecursive(node_t *node, uint32_t *addr, unsigned int mask, int direc);

/* util functions */
static node_t *NewNode(unsigned int bits);
static void SetBitByDirection(uint32_t *addr, int height, int direc);
static int SetThreeOccupiedAddresses(dhcp_t *dhcp);
static unsigned int Height(unsigned char num);
static int IsOccupied(unsigned char num);
static int SetToBeOccupied(unsigned char num);
static void UpdateIsOccupied(node_t* node, int direc);
static int Shift(unsigned char num);
static void SetToBeNotOccupied(unsigned char *num);

/*---------------------------------------------------------------------------*/

dhcp_t *DhcpCreate(const char* net_address, unsigned int mask_bits_size)
{
    dhcp_t *dhcp = (dhcp_t*) malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return (NULL);
    }

    /* convert string of ip address to int and cheak if success*/
    if (0 == inet_pton(AF_INET, net_address, &dhcp->net_address))
    {
        free(dhcp);
        dhcp = NULL;
        return (NULL);
    }

    dhcp->mask_bits_size = mask_bits_size;
    dhcp->root = NewNode(MAX_SIZE);

    if (EXIT_FAILURE == SetThreeOccupiedAddresses(dhcp))
    {
        free(dhcp);
        dhcp = NULL;
        return (NULL);
    }

    return(dhcp);
}

/*---------------------------------------------------------------------------*/

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(dhcp);
    if(NULL != dhcp->root)
    {
        Destroyrecursive(dhcp, dhcp->root);
    }

    free (dhcp);
    dhcp = NULL;
}

/*---------------------------------------------------------------------------*/

int DhcpGetAddress(dhcp_t *dhcp, uint32_t *addr)
{
    int EXIT_STATUS = 0;
    uint32_t new_add = 0;
    assert(dhcp);

    /* if no more addresses are available */
    if (IsOccupied(dhcp->root->status))
    {
        return (EXIT_FAILURE);
    }

    EXIT_STATUS = GetAddressrecursive(dhcp->root, &new_add, dhcp->mask_bits_size, LEFT);
    
    *addr = (dhcp->net_address) | (new_add << Shift(dhcp->mask_bits_size));
    
    return (EXIT_STATUS);
}

/*---------------------------------------------------------------------------*/

void DhcpReleaseAddress(dhcp_t *dhcp, uint32_t ip_address)
{
    uint32_t new_add = ip_address >> (Shift(dhcp->mask_bits_size) + 1);
    node_t *node = dhcp->root;
    int direction = 0;

    while (Height(node->status) > dhcp->mask_bits_size)
    {
        direction = !!(new_add & (1 << (Height(node->status) - 
                    dhcp->mask_bits_size - 1)));
        SetToBeNotOccupied(&node->status);
        node = node->children[direction];
    }

    SetToBeNotOccupied(&node->status);
}

/*---------------------------------------------------------------------------*/

static void Destroyrecursive(dhcp_t *dhcp, node_t *node)
{ 
    if(!node)
    {
        return;
    }

    Destroyrecursive(dhcp, node->children[LEFT]);
    Destroyrecursive(dhcp, node->children[RIGHT]);
    
    free(node);
    node = NULL;
}

/******************************************************************************/

static int GetAddressrecursive(node_t *node, uint32_t *addr, unsigned int mask, int direction)
{
    /* if reached a leaf - mark taken and return*/
    if (Height(node->status) == mask)
    {
        node->status = SetToBeOccupied(node->status);
        return (EXIT_SUCCESS);
    }
    /* if no left node- create and call recursively  */
    if (!node->children[direction])
    {
        int temp = 0;
        node->children[direction] = NewNode(Height(node->status) - 1);
        SetBitByDirection(addr, Height(node->status) - mask, direction);
        temp = GetAddressrecursive(node->children[direction], addr, mask, direction);
        UpdateIsOccupied(node, direction);
        return (temp);
    }   
/* if no room in left node- and no right node- create and call recursively  */
    else if (IsOccupied(node->children[direction]->status) && !node->children[!direction])
    {
        int temp = 0;
        node->children[!direction] = NewNode(Height(node->status) - 1);
        SetBitByDirection(addr, Height(node->status) - mask, !direction);
        temp = GetAddressrecursive(node->children[!direction], addr, mask, direction);
        UpdateIsOccupied(node, direction);   
        return (temp);
    }
    else
    {
        if (IsOccupied(node->children[direction]->status))
        {
            int temp = 0;
            SetBitByDirection(addr, Height(node->status) - mask, !direction);
            temp = GetAddressrecursive(node->children[!direction], addr, mask, direction);
            UpdateIsOccupied(node, direction);   
            return (temp);
        }
        else 
        {
            int temp = GetAddressrecursive(node->children[direction], addr, mask, direction);
            UpdateIsOccupied(node, direction);   
            return (temp);
        }
    }

    return (EXIT_FAILURE);
}

/*---------------------------------------------------------------------------*/

static node_t *NewNode(unsigned int bits)
{
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    if (NULL == new_node)
    {
        return (NULL);
    }

    new_node->children[0] = new_node->children[1] = NULL;
    new_node->status = bits;

    return (new_node);
}

/******************************************************************************/
/* set the 3 occupied adresses end with 00, 11 and 10 */
static int SetThreeOccupiedAddresses(dhcp_t *dhcp)
{
    uint32_t new_add = 0;

    assert(dhcp);

    GetAddressrecursive(dhcp->root, &new_add, dhcp->mask_bits_size, LEFT);
    GetAddressrecursive(dhcp->root, &new_add, dhcp->mask_bits_size, RIGHT);
    GetAddressrecursive(dhcp->root, &new_add, dhcp->mask_bits_size, RIGHT);

    return (0);
}

/******************************************************************************/

static unsigned int Height(unsigned char num)
{
    return (num & 0x3F);
}

/******************************************************************************/
/* The function check if the node is occupied or not */
static int IsOccupied(unsigned char num)
{
    return (num & (1 << 7));
}

/******************************************************************************/
/* set the bit to 0 if we go left or 1 if we go right */
static void SetBitByDirection(uint32_t *addr, int height, int direction)
{
    *addr |= (direction << height);
}

/******************************************************************************/
/* set the bit so the node will be occupied */
static int SetToBeOccupied(unsigned char num)
{
    return (num | (1 << 7));
}

/******************************************************************************/

static void SetToBeNotOccupied(unsigned char *num)
{
    *num &= (~(1 << 7));
}

/******************************************************************************/

static void UpdateIsOccupied(node_t* node, int direction)
{
    if (IsOccupied(node->children[direction]->status) && node->children[!direction])
    {
        if (IsOccupied(node->children[!direction]->status))
        {
            node->status = SetToBeOccupied(node->status);
        }
    }    
}

/******************************************************************************/

static int Shift(unsigned char num)
{
    if (num > 23)
    {
        return (23);
    }
    else if (23 > num && num > 15)
    {
        return (15);
    }
    else if (15 > num && num > 7)
    {
        return (7);
    }
    else
    {
        return (0);
    } 
}

/******************************************************************************/

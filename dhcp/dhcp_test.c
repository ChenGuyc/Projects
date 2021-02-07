/**********************************************************************
* File Name: dhcp_test.c       					    				  *
* Name: Guy Chen								    			      *
* Create Date: 18.8.2020	    									  *
* Topic: dhcp test file            									  *
**********************************************************************/

#include <stdio.h>      /* printf */
#include <assert.h>     /* assert*/
#include <stdlib.h>     /* malloc, free*/

#include "dhcp.h"
/* unit test functions */
static void DhcpCreateTest(void);
static void DhcpDestroyTest(void);
static void DhcpGetAddressTest(void);
static void DhcpReleaseAddressTest(void);

/* util functions*/
static void PrintIPAddress(uint32_t *num);

int main()
{
	printf(" ****** API unit testing: ******\n");

	DhcpCreateTest();
	DhcpDestroyTest();
    DhcpGetAddressTest();
	DhcpReleaseAddressTest();

    printf("********** End of API Testing\n");

	return (0);
}

/******************************************************************************/

static void DhcpCreateTest(void)
{
    char* net_address = "92.3.2.8";
    unsigned int net_bits = 29;

    dhcp_t *dhcp = DhcpCreate(net_address, net_bits);
    printf("\n ************** Dhcp Create Test ***********************\n ");
    if (dhcp)
    {
        printf("The creation of dhcp succeeded\n");
    }
    else
    {
         printf("The creation of dhcp didn't succeed\n");
    }
    
    DhcpDestroy(dhcp);

    printf("\n");
}

/******************************************************************************/

static void DhcpDestroyTest(void)
{
    char* net_address = "32.0.45.0";
    unsigned int net_bits = 26;

    dhcp_t *dhcp = DhcpCreate(net_address, net_bits);
    
    printf("\n ************** Dhcp Destroy Test ***********************\n ");

    DhcpDestroy(dhcp);
    printf("The dhcp has been destroyed\n");    
    printf("\n");
}

/******************************************************************************/

static void DhcpGetAddressTest(void)
{
    char* net_address = "92.10.2.0";
    unsigned int net_bits = 28;
    uint32_t *address = (uint32_t *) malloc(sizeof(int));
    size_t i = 0;
    dhcp_t *dhcp = DhcpCreate(net_address, net_bits);
    assert(dhcp);

    printf("\n ************** Dhcp Get Address Test ********************\n ");
    
    for (i = 0; i <= 14; ++i)
    {
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
    }
    free(address);
    DhcpDestroy(dhcp);
    printf("\n");
 }   

/******************************************************************************/

static void DhcpReleaseAddressTest(void)
{
    char* net_address = "92.10.33.16";
    unsigned int net_bits = 29;
    uint32_t *address = (uint32_t *) malloc(sizeof(int));
    uint32_t *address2 = (uint32_t *) malloc(sizeof(int));
    
    dhcp_t *dhcp = DhcpCreate(net_address, net_bits);
    assert(dhcp);   

    printf("\n ************** Dhcp Release Address Test ****************\n ");

    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address2));
    PrintIPAddress(address2);
    DhcpReleaseAddress(dhcp, *address);
    DhcpReleaseAddress(dhcp, *address2);
    printf("released 2 addresses- should get them again:\n");
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
    printf("did get address work? (0) %d\n", DhcpGetAddress(dhcp, address));
    PrintIPAddress(address);
      
    free(address);
    free(address2);
    DhcpDestroy(dhcp);

    printf("\n");
}

/******************************************************************************/

static void PrintIPAddress(uint32_t *num)
{
    printf("%d.", *((char*)(num)));
    printf("%d.", *((char*)(num) + 1));
    printf("%d.", *((char*)(num) + 2));
    printf("%d\n", *((char*)(num) +3));
}
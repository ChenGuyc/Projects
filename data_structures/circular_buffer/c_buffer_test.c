/* 
* File Name: C_beffer_test.c
* Description: Test functions for circular buffer API functions
* Developer: Guy Chen
* Date: 17.06.2020
*/


#include <stdio.h>
#include <errno.h> /* errno */
#include "c_buffer.h" 

#define TRUE 1
#define FALSE 0

int extern errno;

/********************* Fucntion Declerations **********************************/

static c_buffer_t *CBufferCreateTest(void);
static void CBufferDestroyTest(c_buffer_t *c_buffer);
static void CBufferIsEmptyTest(const c_buffer_t *c_buffer);
static void CBufferFreeSpaceTest(const c_buffer_t *c_buffer);
static void CBufferCapacityTest(const c_buffer_t *c_buffer);
static void CBufferWriteTest(c_buffer_t *c_buffer);
static void CBufferReadTest(c_buffer_t *c_buffer);

static void TestCase1(void);
static void TestCase2(void);
static void TestCase3(void);

/******************************* main Function ********************************/

int main (void)
{
	c_buffer_t *new_buffer = NULL;
	
	new_buffer = CBufferCreateTest();
	CBufferWriteTest(new_buffer); 
	CBufferReadTest(new_buffer);	
	CBufferIsEmptyTest(new_buffer);	
	CBufferFreeSpaceTest(new_buffer);
	CBufferCapacityTest(new_buffer);

	CBufferDestroyTest(new_buffer);
	printf("\n\nTesting with test case \n\n");	
	TestCase1();
	TestCase2();
	TestCase3();
	

	return (0);
}


/************************ Fucntion Defenitions ********************************/

static c_buffer_t *CBufferCreateTest(void)
{
	size_t capacity = 10;
	c_buffer_t *new_buffer = NULL;
	
	new_buffer = CBufferCreate(capacity);
	if (NULL == new_buffer)
	{
		printf("The creation of circular buffer didn't succeed\n");
	}
	else
	{
		printf("The creation of cicular buffer succeeded\n");
	}
		
	return (new_buffer);
}


/******************************************************************************/

static void CBufferDestroyTest(c_buffer_t *c_buffer)
{
	CBufferDestroy(c_buffer);
	
	printf("The circular buffer has been destroyed\n");
}
	
/******************************************************************************/
static void CBufferWriteTest(c_buffer_t *c_buffer)
{
	ssize_t bytes_writen = 0;
	char src[] = "hey!";
	size_t count = 5;
	
	bytes_writen = CBufferWrite(c_buffer, src, count);
	
	if (-1 != bytes_writen)
	{
		printf("The number of bytes writeninto the buffer is: %ld\n", bytes_writen);
	}
	else
	{
		printf("The error is: %s\n", strerror(errno));
	} 
}

/******************************************************************************/

static void CBufferReadTest(c_buffer_t *c_buffer)
{
	ssize_t bytes_read = 0;
	char dest [20] ={0};
	size_t count = 7;
	
	bytes_read = CBufferRead(c_buffer, dest, count);
	
	if (-1 != bytes_read)
	{
		printf("The number of bytes read from buffer is: %ld\n", bytes_read);
	}
	else
	{
		printf("The error is: %s\n", strerror(errno));
	} 
}



/******************************************************************************/

static void CBufferIsEmptyTest(const c_buffer_t *c_buffer)
{
	if (CBufferIsEmpty (c_buffer))
	{
		printf("The buffer is  empty\n");
	}
	else
	{
		printf("The Buffer is not empty\n");
	}
}
	
/******************************************************************************/

static void CBufferFreeSpaceTest(const c_buffer_t *c_buffer)
{
	size_t free_space = 0;
	
	free_space = CBufferFreeSpace(c_buffer);
	printf("The free space in the buffer in bytes is: %lu\n", free_space);
}

/******************************************************************************/

static void CBufferCapacityTest(const c_buffer_t *c_buffer)
{
	size_t capacity = 0;
	
	capacity = CBufferCapacity(c_buffer);
	printf("The buffer has capacity of: %lu bytes\n", capacity);
}

/******************************************************************************/

/* Test case 1 is: create buffer, try to read (from empty) , write once and than
write again with count that bigger than free space check, write again and check
for errno, finally destroy */ 
static void TestCase1(void)
{
	char dest[50] = {0};
	size_t capacity = 10;
	char src [] = "hello world!!!";
	size_t bytes_count1 = 5;
	size_t bytes_count2 = 7;
	ssize_t bytes_read = 0;
	ssize_t bytes_write = 0;

	c_buffer_t *p_buffer = CBufferCreate(capacity);
	
	bytes_read = CBufferRead(p_buffer, dest, bytes_count2);
	
	if(-1 == bytes_read)
	{
		printf("After reading from empty buffer : %s\n", strerror(errno));
	}

	bytes_write = CBufferWrite(p_buffer, src, bytes_count1);
	
	bytes_write += CBufferWrite(p_buffer, src, bytes_count2);

	printf("After trying to write 12 bytes (while capacity is 10),\
	\n number of bytes successfuly writen is: %ld\n", bytes_write);

	bytes_write = CBufferWrite(p_buffer, src, bytes_count1);
	if(-1 == bytes_write)
	{
		printf("After writing to full buffer : %s\n", strerror(errno));
	}

	CBufferDestroy(p_buffer);

	printf("\n---------------end of test case 1 test---------------\n\n");
}

/* Test case 2 is: create 10 bytes buffer write 7, read 3 and write another 5,
make sure return is 5, finally destroy */ 
static void TestCase2(void)
{
	char dest[50] = {0};
	size_t capacity = 10;
	char src [] = "hello world!!!";
	size_t bytes_count1 = 7;
	size_t bytes_count2 = 3;
	size_t bytes_count3 = 5;
	ssize_t bytes_write = 0;

	c_buffer_t *p_buffer = CBufferCreate(capacity);

	bytes_write = CBufferWrite(p_buffer, src, bytes_count1);
	CBufferRead(p_buffer, dest, bytes_count2);
	bytes_write += CBufferWrite(p_buffer, src, bytes_count3);

	printf("After trying to write 12 bytes in 2 steps with read of 3 between\
 	\n (while capacity is 10), number of bytes successfuly writen is: %ld\n",
	bytes_write);

	dest[13] = '\0';
	printf("Dest now contain: %s\n", dest);

	CBufferDestroy(p_buffer);

	printf("\n---------------end of test case 2 test---------------\n\n");
}

/* Test case 3 is: create 11 bytes buffer write 10, read 8 , write another 5 
and read another 5, print dest and make sure circle works properly,
finally destroy */ 
static void TestCase3(void)
{
	char dest1[50] = {0};
	char dest2[50] = {0};
	size_t capacity = 11;
	char src [] = "hello world!!!";
	size_t bytes_count1 = 11;
	size_t bytes_count2 = 8;
	size_t bytes_count3 = 6;

	c_buffer_t *p_buffer = CBufferCreate(capacity);

	CBufferWrite(p_buffer, src, bytes_count1);
	CBufferRead(p_buffer, dest1, bytes_count2);
	printf("Dest now contain: %s\n", dest1);
	
	CBufferWrite(p_buffer, src, bytes_count3);
	CBufferRead(p_buffer, dest2, bytes_count3);

	printf("Dest now contain: %s\n", dest2);

	CBufferDestroy(p_buffer);

	printf("\n---------------end of test case 3 test---------------\n\n");
}


	










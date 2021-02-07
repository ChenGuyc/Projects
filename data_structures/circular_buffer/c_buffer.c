/* 
* File Name: C_beffer.c
* Description: Defenitions circular buffer API functions
* Developer: Guy Chen
* Date: 17.06.2020
*/


#include <unistd.h> /* ssize_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, free */
#include <errno.h> /* errno */
#include "c_buffer.h" 


#define MIN2(a,b) ((a) < (b) ? (a) : (b))


int extern errno;

enum API_STATUS
{
	FAILURE = -1,
	SUCCESS = 0
};

struct c_buffer 
{
    size_t read;
    size_t size;
    size_t capacity;
    char buffer[1];
};


/******************************************************************************/

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *cbuffer = NULL;

	cbuffer =(c_buffer_t *)malloc((offsetof(struct c_buffer, buffer)) + 
					 			   capacity * sizeof(char *));
	if (NULL == cbuffer)
	{
		return (NULL);	
	}
	
	/* set attributes */
	cbuffer->read = 0;
	cbuffer->size = 0;
	cbuffer->capacity = capacity;
	return (cbuffer);
}

/******************************************************************************/

void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	free(c_buffer);
	c_buffer = NULL;
}

/******************************************************************************/

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (!(c_buffer->size));
}

/******************************************************************************/

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (c_buffer->capacity - c_buffer->size);
}

/******************************************************************************/

size_t CBufferCapacity(const c_buffer_t *c_buffer)
{
	assert(c_buffer);	
	
	return (c_buffer->capacity);
}

/******************************************************************************/

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	char *write_index = NULL;
	char *src_ptr = (char *)src;
	size_t chars_to_write = 0;

	assert(c_buffer);
	assert(src);

	if(!CBufferFreeSpace(c_buffer))
	{
		errno = ENOBUFS;
		return (FAILURE);
	}

	count = MIN2(count, CBufferFreeSpace(c_buffer));

	/*Putting the "write" index in the right place */ 	
	write_index = c_buffer->buffer + ((c_buffer->read + 
				   c_buffer->size) % c_buffer->capacity);

	/*check if there is enough free space till the end of the array */
	if(c_buffer->read + count + c_buffer->size > c_buffer->capacity && 
	   c_buffer->read + c_buffer->size < c_buffer->capacity)
	{
		chars_to_write = c_buffer->capacity - (c_buffer->read + c_buffer->size);	
	
		memcpy(write_index, src_ptr, chars_to_write);

		src_ptr += chars_to_write;
		write_index =  c_buffer->buffer;

		memcpy(write_index, src_ptr, count - chars_to_write);
	}
	else
	{
		memcpy(write_index, src, count);
	}

	/*Updating size index */
	c_buffer->size += count;

	return (count);
}


ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	char *read_index = NULL;
	char *dest_ptr = (char *)dest;
	size_t cahrs_to_read = 0;

	assert(c_buffer);
	assert(dest);
	
	if(!CBufferIsEmpty(c_buffer))
	{
		errno = ENODATA;
		return (FAILURE);
	}
	
	count = MIN2(count, c_buffer->size);
	
	/*Putting the read index in the right place */ 
	read_index = c_buffer->buffer + c_buffer->read;

	/*check if we there are enough chars till the the end of the array */
	if(c_buffer->read + count > c_buffer->capacity)
	{
		cahrs_to_read = c_buffer->capacity - c_buffer->read ;

		memcpy(dest_ptr, read_index, cahrs_to_read);

		dest_ptr += cahrs_to_read;
		read_index = c_buffer->buffer;

		memcpy(dest_ptr, read_index, count - cahrs_to_read);	
	}
	else
	{
		memcpy(dest, read_index, count);
	}

	/*Updating read and size indexes */ 
	c_buffer->read = (c_buffer->read + count) % c_buffer->capacity;
	c_buffer->size -= count;

	return (count);
}


	





















	






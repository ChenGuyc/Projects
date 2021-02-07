/* 
* File Name:bit_array_test.c
* Description: Defenition of functions for bit_array.h
* Developer: Guy Chen
* Reviewer: ori Komemi
* Date: 02.06.2020
*/

#include "bit_array.h"

#define MASK 1
#define SIZE_OF_ARRAY sizeof(size_t)
#define BITS_IN_BYTE 8
#define BITS_IN_ARRAY (SIZE_OF_ARRAY * BITS_IN_BYTE)
#define ZERO_ASCII 48

#define R2(n) n, n + 2*64, n + 1*64, n + 3*64
#define R4(n) R2(n), R2(n + 2 * 16), R2(n + 1 * 16), R2(n +3 * 16)
#define R6(n)  R4(n), R4(n + 2 * 4), R2(n + 1 * 4), R4(n + 3 * 4)
#define REVERESE_BITS R6(0), R6(2), R6(1), R6(3)
const size_t mirror_lut[256] = {REVERESE_BITS};


#define B2(n) n, n + 1, n +1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)
const size_t count_on_lut [256] = {COUNT_BITS};

/*****************************************************************************/

bit_array_t BitArrSetAll(bit_array_t arr)
{
	return (arr | (~0));
}

/*****************************************************************************/

bit_array_t BitArrResetAll(bit_array_t arr)
{
	return (arr & 0);
}

/*****************************************************************************/

bit_array_t BitArrSetOn(bit_array_t arr, size_t index)
{
	size_t mask = MASK;	
	
;	arr =  arr | (mask << (index - 1));
	return (arr);
}

/*****************************************************************************/

bit_array_t BitArrSetOff(bit_array_t arr, size_t index)
{
	size_t mask = MASK;
	
	mask <<= (index - 1);
	mask = ~ mask; 	 
	return (arr & mask);	
}

/*****************************************************************************/

bit_array_t BitArrSetBit(bit_array_t arr, size_t index, int boolean_value)
{
	if (boolean_value)
	{
		return (BitArrSetOn(arr, index));
	}
	else 
	{
		return (BitArrSetOff(arr, index));
	}
}

/*****************************************************************************/

bit_array_t BitArrFlip(bit_array_t arr, size_t index)
{
	int mask = MASK;
	
	mask <<= (index - 1);
	return (arr ^ mask); 
}

/*****************************************************************************/

int BitArrIsOn(bit_array_t arr, size_t index)
{
	size_t mask = MASK;
	
	mask <<= (index - 1);
	return (!!(arr & mask));
}

/*****************************************************************************/

int BitArrIsOff(bit_array_t arr, size_t index)
{
	size_t mask = MASK;
	
	mask <<= (index - 1);
	return (!!((~arr) & mask));
}	

/*****************************************************************************/

bit_array_t BitArrRotR(bit_array_t arr, size_t num_to_shift)
{
	size_t mask = MASK;
	size_t temp = 0;
	size_t i= 0;
	
	for (i = 0; i < (num_to_shift % BITS_IN_ARRAY); ++i)
	{
		temp = (arr & mask) | temp;
		mask <<= 1;
	}
	
	arr = (arr >> (num_to_shift % BITS_IN_ARRAY)) | (temp << (BITS_IN_ARRAY - 
		  (num_to_shift % BITS_IN_ARRAY)));
	
	return (arr);
}

/*****************************************************************************/

bit_array_t BitArrRotL(bit_array_t arr, size_t num_to_shift)
{
	arr = (arr << (num_to_shift % BITS_IN_ARRAY)) | (arr >> (BITS_IN_ARRAY - 
		  (num_to_shift % BITS_IN_ARRAY)));
	
	return (arr);
}
	
/*****************************************************************************/

size_t BitArrCountOn(bit_array_t arr)
{
	arr -= ( arr >> 1) & 0x5555555555555555;
	arr = (arr & 0x3333333333333333) + ((arr >> 2) & 0x3333333333333333);
	arr = (arr + (arr >> 4)) & 0x0F0F0F0F0F0F0F0F;

	return ((arr * 0x0101010101010101) >> 56 );
}

/*****************************************************************************/

size_t BitArrCountOff(bit_array_t arr)
{
	return (BITS_IN_ARRAY - BitArrCountOn(arr));
}

/*****************************************************************************/

bit_array_t BitArrMirror(bit_array_t arr)
{
		arr = (arr & 0x00000000FFFFFFFF) << 32  | 
			  (arr & 0xFFFFFFFF00000000) >> 32;	
		arr = (arr & 0xCCCCCCCCCCCCCCCC) >> 16 |
			  ((arr & 0x3333333333333333) << 16);
		arr = (arr & 0xAAAAAAAAAAAAAAAA) >> 8 |
			  ((arr & 0x5555555555555555) << 8); 
		arr = (arr & 0x0F0F0F0F0F0F0F0F) << 4  | 
			  (arr & 0xF0F0F0F0F0F0F0F0) >> 4;
		arr = (arr & 0xCCCCCCCCCCCCCCCC) >> 2 |
			  ((arr & 0x3333333333333333) << 2);
		arr = ((arr & 0xAAAAAAAAAAAAAAAA) >> 1) |
			  ((arr & 0x5555555555555555) << 1); 					

		return(arr);  
}

/*****************************************************************************/


char *BitArrToString(bit_array_t arr, char *dest)
{
	int i = 0;

	dest[BITS_IN_ARRAY - 1] = '\0';

	/* insert chars to the string */
	for(i = (BITS_IN_ARRAY- 1); i >= 0; --i)
	{
		dest[i] = (arr % 2 + ZERO_ASCII);
		arr /= 2;
	}

	return(dest);
}


/*****************************************************************************/


size_t BitArrCountOnLUT(bit_array_t arr)
{
	int count_on = 0;
	size_t i = 0;

	for (i=0; i < BITS_IN_ARRAY; i += BITS_IN_BYTE)
	{
		count_on += count_on_lut[(arr >> i) & 0xFF];
	}

	return (count_on);
}

/*****************************************************************************/

bit_array_t BitArrMirrorLUT(bit_array_t arr)
{
	bit_array_t mirror_arr = 0;
	size_t i = 0;
	int j = BITS_IN_ARRAY;
	
	for (i = 0, j = BITS_IN_ARRAY - BITS_IN_BYTE; i < BITS_IN_ARRAY; 
		i += BITS_IN_ARRAY, j -= BITS_IN_ARRAY)
	{
		mirror_arr += mirror_lut[(arr >> i) & 0xFF] << j;
	}

	return (mirror_arr);
}



































/* 
* File Name:bit_array_test.c
* Description: testing the functions of bit_array.c file
* Developer: Guy Chen
* Date: 02.06.2020
*/

#include <stdio.h> /*printf */
#include "bit_array.h"

/********************** Declerations of test Ffunctions **********************/

static void BitArrSetAllTest(void);
static void BitArrResetAllTest(void);
static void BitArrSetOnTest(void);
static void BitArrSetOffTest(void);
static void BitArrSetBitTest(void);
static void BitArrFlipTest(void);
static void BitArrIsOnTest(void);
static void BitArrIsOffTest(void);
static void BitArrRotRTest(void);
static void BitArrRotLTest(void);
static void BitArrCountOnTest(void);
static void BitArrCountOffTest(void);
static void BitArrMirrorTest(void);
static void BitArrToStringTest(void);
static void BitArrCountOnLUTTest(void);
static void BitArrMirrorLUTTest(void);

/****************************************************************************/

int main(void)
{

	BitArrSetAllTest();
	BitArrResetAllTest();
	BitArrSetOnTest();
	BitArrSetOffTest();
	BitArrSetBitTest();
	BitArrFlipTest();
	BitArrIsOnTest();
	BitArrIsOffTest();	
	BitArrRotRTest();
	BitArrRotLTest();
	BitArrCountOnTest();
	BitArrCountOffTest();
	BitArrMirrorTest();
	BitArrToStringTest();	
	BitArrCountOnLUTTest();	
	BitArrMirrorLUTTest();

	return (0);
}

/********************** Defenitions of test functions *************************/

/* Test funtion for BitArrSetAll function */
 
static void BitArrSetAllTest(void)
{
	size_t array_of_bits = 12;

	printf("%lx\n", BitArrSetAll(array_of_bits));
}


/* Test funtion for BitArrResetAll function */

static void BitArrResetAllTest(void)
{
	size_t array_of_bits = 12;	

	printf("%lx\n", BitArrResetAll(array_of_bits));
}


/* Test funtion for BitArrSetOn function */

static void BitArrSetOnTest(void)
{
	size_t array_of_bits = 12;	
	size_t index = 2;
		
	array_of_bits = BitArrSetOn(array_of_bits, index);
	printf("%lx\n", array_of_bits);
}


/* Test funtion for BitArrSetOff function */

static void BitArrSetOffTest(void)
{
	size_t array_of_bits = 9;	
	size_t index = 3;

	array_of_bits = BitArrSetOff(array_of_bits, index);
	printf("%lx\n", array_of_bits);
}


/* Test funtion for BitArrSetBit function */

static void BitArrSetBitTest(void)
{
	size_t array_of_bits = 12;	
	size_t index = 3;
	int value = 0;
	
	array_of_bits = BitArrSetBit (array_of_bits, index, value);
	printf("%lx\n", array_of_bits);
}


/* Test funtion for BitArrFlip function */

static void BitArrFlipTest(void)
{
	size_t array_of_bits = 12;	
	size_t index = 1;
	
	array_of_bits = BitArrFlip(array_of_bits, index);
	printf("%lx\n", array_of_bits);
}	


/* Test funtion for BitArrIsOn function */

static void BitArrIsOnTest(void)
{
	size_t array_of_bits = 12;	
	size_t index = 3;
	int is_on = 0;

	is_on = BitArrIsOn(array_of_bits, index);
	if (is_on)
	{
		printf("The value of is_on is: %d\n", is_on);
		printf ("The bit in index: %lu is on\n", index);
	}
	else
	{
		printf("The value of is_on is: %d\n", is_on);
		printf ("The bit index: %lu isn't on\n", index);
	}
}


/* Test funtion for BitArrIsOff function */

static void BitArrIsOffTest(void)
{
	size_t array_of_bits = 12;	
	size_t index = 4;
	int is_off = 0;

	is_off = BitArrIsOff(array_of_bits, index);
	if (is_off)
	{
		printf("The value of is_off is: %d\n", is_off);
		printf ("The bit in index: %lu is off\n", index);
	}
	else
	{
		printf("The value of is_off is: %d\n", is_off);
		printf ("The bit in index: %lu isn't off\n", index);
	}
}


/* Test funtion for BitArrRotR function */

static void BitArrRotRTest(void)
{
	size_t array_of_bits = 12;	
	size_t num_to_shift = 66;
	
	printf("before rotate: %lu\n", array_of_bits);
	array_of_bits = BitArrRotR(array_of_bits, num_to_shift);
	printf("After rotate: %lu\n", array_of_bits);
}


/* Test funtion for BitArrRotL function */

static void BitArrRotLTest(void)
{
	size_t array_of_bits = 13;	
	size_t num_to_shift = 66;
	
	printf("before rotate: %lu\n", array_of_bits);
	array_of_bits = BitArrRotL(array_of_bits, num_to_shift);
	printf("After rotate: %lu\n", array_of_bits);
}


/* Test funtion for BitArrCountOn function */

static void BitArrCountOnTest(void)
{
	size_t array_of_bits = 13;	
	size_t num_of_bits_on = 0;
	
	num_of_bits_on = BitArrCountOn(array_of_bits);
	printf("sum of bits on in the number %lu are %lu:\n", array_of_bits, 
			num_of_bits_on);
}


/* Test funtion for BitArrCountOff function */

static void BitArrCountOffTest(void)
{
	size_t array_of_bits = 13;	
	size_t num_of_bits_off = 0;
	
	num_of_bits_off = BitArrCountOff(array_of_bits);
	printf("sum of bits off in the number %lu are %lu:\n", array_of_bits, 
			num_of_bits_off);
}


/* Test funtion for BitArrMirror function */

static void BitArrMirrorTest(void)
{
	size_t array_of_bits = 1;
	
	array_of_bits = BitArrMirror(array_of_bits);
	printf("The mirror is: %lu\n", array_of_bits);
}
	

/* Test funtion for BitArrToString function */

static void BitArrToStringTest(void)
{
	size_t array_of_bits = 13;	
	char arr_of_string [65] ="";
	
	BitArrToString(array_of_bits, arr_of_string);
	
	printf("The number is %lu annd binary presentation is %s\n", 
			array_of_bits, arr_of_string); 

}

static void BitArrCountOnLUTTest(void)
{
	size_t array_of_bits = 65535;
	size_t counter = 0;

	counter = BitArrCountOnLUT(array_of_bits);
	printf("the number of set bit in %lu, is: %lu\n", array_of_bits, counter);
}


static void BitArrMirrorLUTTest(void)
{
	size_t array_of_bits = 1;
	
	array_of_bits = BitArrMirrorLUT(array_of_bits);
	printf("The mirror is %lu\n", array_of_bits);
}
	














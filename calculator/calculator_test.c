/**********************************************************************
* File Name: calculator_test.c      			    				  *
* Name: Guy Chen    								    			  *
* Create Date: 28.7.2020											  *
* Topic: Calculator test C file         									  *
**********************************************************************/

#include <stdio.h> 
#include <string.h> 


#include <stdio.h>      /* printf */

#include "calculator.h"

static void TestCalculator(void);

int main()
{
    TestCalculator();

    return(0);
}

static void TestCalculator(void)
{
    float result = 0;
    char str1[] = "0/0";
    char str2[] = "(14-3)*54/7";
    char str3[] = "17*5+(4-3)/4";
    char str4[] = "3+4-2-5";
    char str5[] = "17-22/2-12";
    char str6[] = "17-(22/2)-12";
    
    result = Calculator(str1);
    printf("str1 = %s = %f\n", str1, result);

    result = Calculator(str2);
    printf("str2 = %s = %f\n", str2, result);

    result = Calculator(str3);
    printf("str3 = %s = %f\n", str3, result);

    result = Calculator(str4);
    printf("str4 = %s = %f\n", str4, result);

    result = Calculator(str5);
    printf("str5 = %s = %f\n", str5, result);

    result = Calculator(str6);
    printf("str6 = %s = %f\n", str6, result);

}

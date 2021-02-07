/*********************************************************************
* File Name: calculator.c      					    				  *
* Name: Guy Chen    								    			  *
* Create Date: 28.7.2020											  *
* Reviewed by: Ori Komemi            							 	  *
* Topic: Calculator C file         									  *
**********************************************************************/

#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc, free */

#include "calculator.h" 
#include "stack.h"

#define NaN (float)0 / (float)0
#define UNUSED(x) (void)(x)


typedef char *(*action_t)(char* equation, stack_t *stack_operator,
                          stack_t *stack_operand);
typedef float (*calculate_t)(float num1, float num2);
/******************************************************************************/

static char *StoreOpenParenthesis(char *equation, stack_t *stack_operator,
                                 stack_t *stack_operand);
static char *GetOpenParenthesis(char *equation, stack_t *stack_operator,
                                 stack_t *stack_operand);
static char *Action(char *equation, stack_t *stack_operator,
                    stack_t *stack_operand);
static char *StoreNumber(char *equation, stack_t *stack_operator,
                        stack_t *stack_operand);
static char *StoreOperator(char *equation, stack_t *stack_operator,
                          stack_t *stack_operand);
static char *GetAndCalculate(char *equation, stack_t *stack_operator,
                             stack_t *stack_operand);
static char *IncrementEquatoin(char *equation, stack_t *stack_operator,
                               stack_t *stack_operand);
static char *DoNothing(char *equation, stack_t *stack_operator,
                                 stack_t *stack_operand);

/* Calculation functions */
static float Multiply(float num1, float num2);
static float Divide(float num1, float num2);
static float Add(float num1, float num2);
static float Subtract(float num1, float num2);

/* The functions in the LUT per ASCII table form index 40 */
static action_t operations[17] = 
{StoreOpenParenthesis, GetOpenParenthesis, Action, Action, DoNothing, Action, 
DoNothing, Action, StoreNumber, StoreNumber, StoreNumber, StoreNumber, StoreNumber,StoreNumber, StoreNumber, StoreNumber, StoreNumber};

static action_t parenthesis [8] = 
{IncrementEquatoin, GetOpenParenthesis, GetOpenParenthesis, GetOpenParenthesis,
DoNothing, GetOpenParenthesis, DoNothing, GetOpenParenthesis};

static int precedence_LUT[9] = {4, 4, 2, 1, -1, 1, 0, 2};

static action_t diff_precedehce_LUT [9] =
{GetAndCalculate, StoreOperator, GetAndCalculate, GetAndCalculate, StoreOperator,
StoreOperator};

static calculate_t Calculate_LUT [6] =
{Multiply, Add, NULL, Subtract, NULL, Divide};

static float CalculateRestEquation(stack_t *stack_operator,
                                   stack_t *stack_operand);

/******************************************************************************/

float Calculator(const char *equation)
{
    stack_t *stack_operand = NULL;
    stack_t *stack_operator = NULL;
    float result = 0;

    stack_operand = StackCreate(strlen(equation));
    if(NULL == stack_operand)
    {
        return (NaN);
    }
    stack_operator = StackCreate(strlen(equation));
    if(NULL == stack_operator)
    {
        return (NaN);
    }
    while(*equation && equation != NULL)
    {
        equation = operations[(char)*equation - 40]((char*)equation, stack_operator, stack_operand);
    }
    if (NULL == equation)
    {
        StackDestroy(stack_operand);
        StackDestroy(stack_operator);
        return (NaN);
    }

    result = CalculateRestEquation(stack_operator, stack_operand);
    StackDestroy(stack_operand);
    StackDestroy(stack_operator);

    return (result);
}

/******************************************************************************/

static float CalculateRestEquation(stack_t *stack_operator,
                                   stack_t *stack_operand)
{
    char *top = NULL;
    float *num1 = NULL;
    float *num2 = NULL;
    float return_value = 0;

    while (!StackIsEmpty(stack_operator))
    {
        top = StackPeek(stack_operator);
        StackPop(stack_operator);

        num1 = StackPeek(stack_operand);
        StackPop(stack_operand);

        num2 = StackPeek(stack_operand);
        StackPop(stack_operand);

        *num1 = Calculate_LUT[(char)*top - 42](*num1, *num2);

        free(num2);
        num2 = NULL;

        StackPush(stack_operand, num1);
    }

    num1 = StackPeek(stack_operand);
    return_value = *num1;
    StackPop(stack_operand);

    free(num1);
    num1 = NULL;

    return (return_value);
}

/******************************************************************************/

static char *StoreNumber(char *equation, stack_t *stack_operator,
                        stack_t *stack_operand)
{
    float *num = NULL;
    char *ptr = NULL;

    UNUSED(stack_operator);

    assert(stack_operand);
    assert(equation);

    num = (float*)malloc(sizeof(float));
    if(NULL == num)
    {
        return(NULL);
    }

    *num = strtod(equation, &ptr);
    equation = ptr;

    StackPush(stack_operand, num);

    return (equation);
}

/******************************************************************************/

static char *StoreOperator(char *equation, stack_t *stack_operator,
                          stack_t *stack_operand)
{
    UNUSED(stack_operand);
    StackPush(stack_operator, equation);
   
    return (++equation);
}

/******************************************************************************/

static char *GetAndCalculate(char *equation, stack_t *stack_operator,
                             stack_t *stack_operand)
{
    char *top = NULL;
    float *num1 = NULL;
    float *num2 = NULL;

    top = StackPeek(stack_operator);
    StackPop(stack_operator);

    num1 = StackPeek(stack_operand);
    StackPop(stack_operand);

    num2 = StackPeek(stack_operand);
    StackPop(stack_operand);

    *num1 = Calculate_LUT[(char)*top - 42](*num1, *num2);

    free(num2);
    num2 = NULL;

    StackPush(stack_operand, num1);

    return(equation);
}

/******************************************************************************/

static char *GetOpenParenthesis(char *equation, stack_t *stack_operator,
                                 stack_t *stack_operand)
{
    char *top = NULL;
    float *num1 = NULL;
    float *num2 = NULL;

    top = StackPeek(stack_operator);
    StackPop(stack_operator);

    num1 = StackPeek(stack_operand);
    StackPop(stack_operand);

    num2 = StackPeek(stack_operand);
    StackPop(stack_operand);

    *num1 = Calculate_LUT[(char)*top - 42](*num1, *num2);

    free(num2);
    num2 = NULL;

    StackPush(stack_operand, num1);

    top = StackPeek(stack_operator);
    equation = parenthesis[(char)*top - 40](equation, stack_operator, stack_operand);

    return (equation);
}

/******************************************************************************/

static char *Action(char *equation, stack_t *stack_operator,
                    stack_t *stack_operand)
{
    int diff = 0;
    char *top = NULL;

    if(StackIsEmpty(stack_operator))
    {
        return(StoreOperator(equation,stack_operator,stack_operand));
    }
    
    top = StackPeek(stack_operator);
    diff = precedence_LUT[(char)*top - 40] - 
           precedence_LUT[(char)*equation - 40] +2;
        
    equation = diff_precedehce_LUT[diff](equation,stack_operator,
                                         stack_operand);
    return(equation);
}

/******************************************************************************/
static char *StoreOpenParenthesis(char *equation, stack_t *stack_operator,
                                 stack_t *stack_operand)
{
    UNUSED(stack_operand);
    StackPush(stack_operator, equation);

    return(++equation);
}

/******************************************************************************/
static char *IncrementEquatoin(char *equation, stack_t *stack_operator,
                               stack_t *stack_operand)
{
    UNUSED(stack_operand);
    StackPop(stack_operator);
    
    return(++equation);
}

/******************************************************************************/
static char *DoNothing(char *equation, stack_t *stack_operator,
                                 stack_t *stack_operand)
{
	UNUSED(equation); /* disable warniing */
    UNUSED(stack_operator); /* disable warniing */
    UNUSED(stack_operand); /* disable warniing */

    return(NULL);
}

/******************************************************************************/

/* Calculating functions */
/******************************************************************************/

static float Multiply(float num1, float num2)
{
    return (num1 * num2);
}

/******************************************************************************/

static float Divide(float num1, float num2)
{
    return (num2 / num1);  
}

/******************************************************************************/

static float Add(float num1, float num2)
{
    return (num1 + num2); 
}

/******************************************************************************/

static float Subtract(float num1, float num2)
{
    return (num2 - num1);
}

/******************************************************************************/








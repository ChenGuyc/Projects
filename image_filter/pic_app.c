/**********************************************************************
* File Name: pic_app.c      			    				  *
* Name: Guy Chen    								    			  *
* Create Date: 28.8.2020											  *         
**********************************************************************/


#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "photoutils.h"
#include "filter.h"

#define filterWidth 3
#define filterHeight 3

int main()
{
     Emboss();
    Sharpen();

    return (0);
}

/**********************************************************************
* File Name: filter.c  			    				  *
* Name: Guy Chen    								    			  *
* Create Date: 28.8.2020											  *         
**********************************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "photoutils.h"

void Emboss(void)
{
    FILE *bmp_r = fopen("./FIndingDory.bmp", "r");
    FILE *bmp_w = fopen("./new_img.bmp", "a+");
    size_t i = 0;
    size_t j = 0;
    double filter[3][3] =
    {
        {-1, -1,  0},
        {-1,  0,  1},
        {0,  1,  1}
    };
    double factor = 1.0;
    double bias = 128.0;

    BMP_IMAGE *img1 = NULL;
    BMP_IMAGE *img2 = NULL;

    img1 = LoadImage(bmp_r);
    img2 = ConstructImage(img1);

     for(i = 0;i < img1->Header.height; ++i)
    {
        for(j = 0;j < img1->Header.width; ++j)
        {
            SetPixel(img2,  img2->Header.height - i -1, j, GetPixel(img1, i, j));
        }
    }

    SetFilterParams((double*)filter, 3 ,3, factor, bias);

    for(i = 1;i < img2->Header.height - 1; ++i)
    {
        for(j = 1;j < img2->Header.width - 1; ++j)
        {
            SetPixel(img2,  img2->Header.height - i -1 , j, ApplyFilter(img1, i, j));
        }
    }

    StoreImage(bmp_w, img2);

    DestructImage(img1);
    DestructImage(img2);

    fclose(bmp_r);
    fclose(bmp_w);
}


void Sharpen(void)
{
    FILE *bmp_r = fopen("./FIndingDory.bmp", "r");
    FILE *bmp_w = fopen("./new_img1.bmp", "a+");
    size_t i = 0;
    size_t j = 0;
    double filter[3][3] =
    {
        {-1, -1,  -1},
        {-1,  9,  -1},
        {-1,  -1,  -1}
    };
    double factor = 1.0;
    double bias = 0.0;

    BMP_IMAGE *img1 = NULL;
    BMP_IMAGE *img2 = NULL;

    img1 = LoadImage(bmp_r);
    img2 = ConstructImage(img1);

     for(i = 0;i < img1->Header.height; ++i)
    {
        for(j = 0;j < img1->Header.width; ++j)
        {
            SetPixel(img2,  img2->Header.height - i -1, j, GetPixel(img1, i, j));
        }
    }

    SetFilterParams((double*)filter, 3 ,3, factor, bias);

    for(i = 1;i < img2->Header.height - 1; ++i)
    {
        for(j = 1;j < img2->Header.width - 1; ++j)
        {
            SetPixel(img2,  img2->Header.height - i -1 , j, ApplyFilter(img1, i, j));
        }
    }

    StoreImage(bmp_w, img2);

    DestructImage(img1);
    DestructImage(img2);

    fclose(bmp_r);
    fclose(bmp_w);
}

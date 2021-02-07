/**********************************************************************
* File Name: photoutils_test.c     			    				  *
* Name: Guy Chen    								    			  *
* Create Date: 28.8.2020											  *         
**********************************************************************/


#include "photoutils.h"

static void TestPhotoCopy();

int main()
{
    TestPhotoCopy();
}

static void TestPhotoCopy()
{
    FILE *bmp_r = fopen("./FIndingDory.bmp", "r");
    FILE *bmp_w = fopen("./new_img.bmp", "a+");
    size_t i = 0;
    size_t j = 0;
    double filter[3][3] =
    {
    -1, -1,  0,
    -1,  0,  1,
    0,  1,  1
    };
    double factor = 1.0;
    double bias = 128.0;

    BMP_IMAGE *img1 = NULL;
    BMP_IMAGE *img2 = NULL;

    BMP_IMAGE *tmp1 = NULL;
    BMP_IMAGE *tmp2 = NULL;

    img1 = LoadImage(bmp_r);
    img2 = ConstructImage(img1);

    tmp1 = img1;
    tmp2 = img2;

    for(i = 0; i < img1->Header.height; ++i)
    {
        for(j = 0; j < img1->Header.width; ++j)
        {
            SetPixel(img2, img1->Header.height - i - 1, j, 
            GetPixel(img1, i, j));
        }
    }

    SetFilterParams((double*)filter, 3 ,3, factor, bias);

    for(i = 1;i <= img2->Header.height; ++i)
    {
        printf("height: %d\n", i);
        for(j = 1;j <= img2->Header.width; ++j)
        {
            printf("width: %d\n", j);
            SetPixel(img2, img2->Header.height - i - 1, j, ApplyFilter(img1, i, j));
        }
    }


    StoreImage(bmp_w, img2);
 
    DestructImage(img1);
    DestructImage(img2);

    fclose(bmp_r);
    fclose(bmp_w);

}

#include <stdio.h>
#include <stdlib.h>
#include "ti_alex.h"
#include <time.h>

/**
 *  @fn greyscale_pixel
 *  @param img an IplImage which we want to convert in greyscale.
 *  @param x an int which is the abs position of the image.
 *  @param y an int which is the ord position of the image.
 *
 *  This function return a colored pixel from IplImage into a greyscale int pixel.
 */
uchar greyscale_pixel(IplImage* pixel, int i, int j){
    uchar pixel_blue = (uchar)(pixel->imageData[((i*3)+(j*pixel->widthStep))]) ;
    uchar pixel_green = (uchar)(pixel->imageData[((i*3)+(j*pixel->widthStep))+1]) ;
    uchar pixel_red = (uchar)(pixel->imageData[((i*3)+(j*pixel->widthStep))+2]) ;


    return ((pixel_blue+pixel_green+pixel_red)/3) ;
}

/**
 *  @fn greyscale_img
 *  @param img an IplImage which we want to convert in greyscale.
 *  @param x an int which is the abs size of the image.
 *  @param y an int which is the ord size of the image.
 *
 *  This function convert a colored IplImage into a char** greyscale image.
 */
uchar** greyscale_img(IplImage* img, int x, int y){
    int i, j ;
    uchar** img_greyscale = (uchar**)calloc(x, sizeof(uchar*));

    for(i = 0 ; i < x ; i++){
        img_greyscale[i] = (uchar*)calloc(y, sizeof(uchar));
        for(j = 0 ; j < y ; j++){
            img_greyscale[i][j] = greyscale_pixel(img, i, j);
        }
    }

    return img_greyscale ;
}


int** grad(IplImage* image, int x, int y){
    //int img_sobel_vert[x-2][y-2] ;
    //int img_sobel_hori[x-2][y-2] ;
    int** norme_grad ;
    uchar** img_greyscale ;

    clock_t begin = clock();

    norme_grad = (int**)malloc((x-2)*sizeof(int*));

    img_greyscale = greyscale_img(image, x, y);

    int i, j ;
    int k, l ;

    uchar pixel_1 ;
    uchar pixel_2 ;
    uchar pixel_3 ;
    uchar pixel_4 ;
    uchar pixel_6 ;
    uchar pixel_7 ;
    uchar pixel_8 ;
    uchar pixel_9 ;

    int pixel_sobel_vert = 0, pixel_sobel_hori = 0 ;

    for(i = 1 ; i < x-1 ; i++){

        norme_grad[i-1] = (int*)malloc((y-2)*sizeof(int));

        for(j = 1 ; j < y-1 ; j++){
            pixel_1 = img_greyscale[i-1][j-1] ;
            pixel_2 = img_greyscale[i-1][j] ;
            pixel_3 = img_greyscale[i-1][j+1] ;
            pixel_4 = img_greyscale[i][j-1] ;
            pixel_6 = img_greyscale[i][j+1] ;
            pixel_7 = img_greyscale[i+1][j-1] ;
            pixel_8 = img_greyscale[i+1][j] ;
            pixel_9 = img_greyscale[i+1][j+1] ;

            // sobel vertical
            pixel_sobel_vert = -pixel_1
                               -2*pixel_2
                               -pixel_3
                               + pixel_7
                               + 2*pixel_8
                               + pixel_9;

            //img_sobel_vert[i-1][j-1] = pixel_sobel_vert ;

            // sobel horizontal
            pixel_sobel_hori = -pixel_1
                               + pixel_3
                               -2*pixel_4
                               + 2*pixel_6
                               -pixel_7
                               + pixel_9;

            //img_sobel_hori[i-1][j-1] = pixel_sobel_hori ;

            norme_grad[i-1][j-1] = sqrt((pixel_sobel_hori*pixel_sobel_hori)+(pixel_sobel_vert*pixel_sobel_vert));
        }
    }
    clock_t end = clock();

    printf("%s : %f second(s) of execution.", __FUNCTION__, ((double)(end-begin)/CLOCKS_PER_SEC));
    return norme_grad ;

}

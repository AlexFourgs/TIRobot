#include <stdio.h>
#include <stdlib.h>
#include "ti_alex.h"

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
    uchar** img_greyscale = (uchar**)calloc(x, sizeof(char*));

    for(i = 0 ; i < x ; i++){
        img_greyscale[i] = (uchar*)calloc(y, sizeof(char));
        for(j = 0 ; j < y ; j++){
            img_greyscale[i][j] = greyscale_pixel(img, i, j);
        }
    }

    return img_greyscale ;
}

uchar** grad(IplImage* image, int x, int y){
    int sobel_vert[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int sobel_hori[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int img_sobel_vert[x-2][y-2] ;
    int img_sobel_hori[x-2][y-2] ;
    uchar** img_greyscale ;

    //
    memset(img_sobel_hori, 0, sizeof(img_sobel_hori));
    memset(img_sobel_vert, 0, sizeof(img_sobel_vert));


    img_greyscale = greyscale_img(image, x, y);

    int i, j ;
    int k, l ;

    for(i = 1 ; i < x-1 ; i++){
        for(j = 1 ; j < y-1 ; j++){
            for(k = -1 ; k < 2 ; k++){
                for(l = -1 ; l < 2 ; l++){
                    img_sobel_vert[i-1][j-1] += sobel_vert[k+1][l+1]*img_greyscale[i+k][j+l];
                    img_sobel_hori[i-1][j-1] += sobel_hori[k+1][l+1]*img_greyscale[i+k][j+l];
                }
            }
        }
    }


}

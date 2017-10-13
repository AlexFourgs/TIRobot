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
void greyscale_img(IplImage* img, int nb_ligne, int nb_colonne, uchar*** gr) {
    int i, j ;

    for(i = 0 ; i < nb_ligne ; i++){
        for(j = 0 ; j < nb_colonne ; j++){
            (*gr)[i][j] = greyscale_pixel(img, j, i);
        }
    }
}


void grad(IplImage* image, int nb_ligne, int nb_colonne, int*** norme_grad, int*** img_sobel_vert, int*** img_sobel_hori, uchar*** gr) {
    // int** norme_grad ;
    // uchar** img_greyscale ;

    // clock_t begin = clock();

    /*
    // à effacer
    byte** sobel_vert_byte = bmatrix(0, nb_ligne-2, 0, nb_colonne-2);
    byte** sobel_hori_byte = bmatrix(0, nb_ligne-2, 0, nb_colonne-2);
    byte** norme_grad_byte = bmatrix(0, nb_ligne-2, 0, nb_colonne-2);
    */
    // img_greyscale = greyscale_img(image, nb_ligne, nb_colonne, gr);
    greyscale_img(image, nb_ligne, nb_colonne, gr);
    int i, j ;

    int pixel_1 = 0;
    int pixel_2 = 0;
    int pixel_3 = 0;
    int pixel_4 = 0;
    int pixel_6 = 0;
    int pixel_7 = 0;
    int pixel_8 = 0;
    int pixel_9 = 0;

    int pixel_sobel_vert = 0, pixel_sobel_hori = 0 ;

    for(i = 1 ; i < nb_ligne-1 ; i++) {

        for(j = 1 ; j < nb_colonne-1 ; j++) {
            // pixel_1 = img_greyscale[i-1][j-1] ;
            // pixel_2 = img_greyscale[i-1][j] ;
            // pixel_3 = img_greyscale[i-1][j+1] ;
            // pixel_4 = img_greyscale[i][j-1] ;
            // pixel_6 = img_greyscale[i][j+1] ;
            // pixel_7 = img_greyscale[i+1][j-1] ;
            // pixel_8 = img_greyscale[i+1][j] ;
            // pixel_9 = img_greyscale[i+1][j+1] ;

            pixel_1 = (*gr)[i-1][j-1] ;
            pixel_2 = (*gr)[i-1][j] ;
            pixel_3 = (*gr)[i-1][j+1] ;
            pixel_4 = (*gr)[i][j-1] ;
            pixel_6 = (*gr)[i][j+1] ;
            pixel_7 = (*gr)[i+1][j-1] ;
            pixel_8 = (*gr)[i+1][j] ;
            pixel_9 = (*gr)[i+1][j+1] ;

            // sobel vertical
            pixel_sobel_vert = -pixel_1
                               -2*pixel_2
                               -pixel_3
                               + pixel_7
                               + 2*pixel_8
                               + pixel_9;

            (*img_sobel_vert)[i-1][j-1] = pixel_sobel_vert ;

            // sobel horizontal
            pixel_sobel_hori = -pixel_1
                               + pixel_3
                               -2*pixel_4
                               + 2*pixel_6
                               -pixel_7
                               + pixel_9;

            (*img_sobel_hori)[i-1][j-1] = pixel_sobel_hori ;

            (*norme_grad)[i-1][j-1] = sqrt((pixel_sobel_hori*pixel_sobel_hori)+(pixel_sobel_vert*pixel_sobel_vert));
        }
    }
    // clock_t end = clock();

    // printf("%s : %f second(s) of execution.\n", __FUNCTION__, ((double)(end-begin)/CLOCKS_PER_SEC));
}

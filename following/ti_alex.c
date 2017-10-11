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
uchar** greyscale_img(IplImage* img, int nb_ligne, int nb_colonne){
    int i, j ;
    uchar** img_greyscale = (uchar**)malloc(nb_ligne*sizeof(uchar*));

    for(i = 0 ; i < nb_ligne ; i++){
        img_greyscale[i] = (uchar*)malloc(nb_colonne*sizeof(uchar));
        for(j = 0 ; j < nb_colonne ; j++){
            img_greyscale[i][j] = greyscale_pixel(img, i, j);
        }
    }

    return img_greyscale ;
}


int** grad(IplImage* image, int nb_ligne, int nb_colonne, int*** img_sobel_vert, int*** img_sobel_hori){
    int** norme_grad ;
    uchar** img_greyscale ;

    // clock_t begin = clock();

    norme_grad = (int**)malloc((nb_ligne-2)*sizeof(int*));
    *img_sobel_hori = (int**)malloc((nb_ligne-2)*sizeof(int*));
    *img_sobel_vert = (int**)malloc((nb_ligne-2)*sizeof(int*));

    /*
    // à effacer
    byte** sobel_vert_byte = bmatrix(0, nb_ligne-2, 0, nb_colonne-2);
    byte** sobel_hori_byte = bmatrix(0, nb_ligne-2, 0, nb_colonne-2);
    byte** norme_grad_byte = bmatrix(0, nb_ligne-2, 0, nb_colonne-2);
    */
    img_greyscale = greyscale_img(image, nb_ligne, nb_colonne);

    int i, j ;

    uchar pixel_1 ;
    uchar pixel_2 ;
    uchar pixel_3 ;
    uchar pixel_4 ;
    uchar pixel_6 ;
    uchar pixel_7 ;
    uchar pixel_8 ;
    uchar pixel_9 ;

    int pixel_sobel_vert = 0, pixel_sobel_hori = 0 ;

    for(i = 1 ; i < nb_ligne-1 ; i++){

        norme_grad[i-1] = (int*)malloc((nb_colonne-2)*sizeof(int));
        (*img_sobel_hori)[i-1] = (int*)malloc((nb_colonne-2)*sizeof(int));
        (*img_sobel_vert)[i-1] = (int*)malloc((nb_colonne-2)*sizeof(int));

        for(j = 1 ; j < nb_colonne-1 ; j++){
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

            (*img_sobel_vert)[i-1][j-1] = pixel_sobel_vert ;

            // sobel horizontal
            pixel_sobel_hori = -pixel_1
                               + pixel_3
                               -2*pixel_4
                               + 2*pixel_6
                               -pixel_7
                               + pixel_9;

            (*img_sobel_hori)[i-1][j-1] = pixel_sobel_hori ;

            norme_grad[i-1][j-1] = sqrt((pixel_sobel_hori*pixel_sobel_hori)+(pixel_sobel_vert*pixel_sobel_vert));
        }
    }
    // clock_t end = clock();

    // printf("%s : %f second(s) of execution.\n", __FUNCTION__, ((double)(end-begin)/CLOCKS_PER_SEC));

    return norme_grad ;

}

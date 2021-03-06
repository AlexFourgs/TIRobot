#include "harris.h"

/* gcc -o harris.out harris.c ti_alex.c `pkg-config --libs opencv`*/

void harris(int** gradX, int** gradY, int x, int y, float lambda, int threshold, ValuePoint** corners, int* corners_nb, int*** h) {
    int i, j, k;

    int gradXX_1, gradXX_2, gradXX_3, gradXX_4, gradXX_5, gradXX_6, gradXX_7, gradXX_8, gradXX_9 ;
    int gradYY_1, gradYY_2, gradYY_3, gradYY_4, gradYY_5, gradYY_6, gradYY_7, gradYY_8, gradYY_9 ;

    float gauss_gradXX = 0, gauss_gradYY = 0, gauss_gradXY = 0, norm = 0, harris_pixel = 0;

    *corners_nb = 0;

    for(i = 1 ; i < y-3 ; i++) {
        for(j = 1 ; j < x-3 ; j++) {
            gradXX_1 = gradX[i-1][j-1] ;
            gradXX_2 = gradX[i-1][j] ;
            gradXX_3 = gradX[i-1][j+1] ;
            gradXX_4 = gradX[i][j-1] ;
            gradXX_5 = gradX[i][j] ;
            gradXX_6 = gradX[i][j+1] ;
            gradXX_7 = gradX[i+1][j-1] ;
            gradXX_8 = gradX[i+1][j] ;
            gradXX_9 = gradX[i+1][j+1] ;

            gradYY_1 = gradY[i-1][j-1] ;
            gradYY_2 = gradY[i-1][j] ;
            gradYY_3 = gradY[i-1][j+1] ;
            gradYY_4 = gradY[i][j-1] ;
            gradYY_5 = gradY[i][j] ;
            gradYY_6 = gradY[i][j+1] ;
            gradYY_7 = gradY[i+1][j-1] ;
            gradYY_8 = gradY[i+1][j] ;
            gradYY_9 = gradY[i+1][j+1] ;

            gauss_gradXX = ((float) 1/16)*gradXX_1*gradXX_1
                         + ((float) 1/8) *gradXX_2*gradXX_2
                         + ((float) 1/16)*gradXX_3*gradXX_3
                         + ((float) 1/8) *gradXX_4*gradXX_4
                         + ((float) 1/4) *gradXX_5*gradXX_5
                         + ((float) 1/8) *gradXX_6*gradXX_6
                         + ((float) 1/16)*gradXX_7*gradXX_7
                         + ((float) 1/8) *gradXX_8*gradXX_8
                         + ((float) 1/16)*gradXX_9*gradXX_9;

            gauss_gradYY = ((float) 1/16)*gradYY_1*gradYY_1
                         + ((float) 1/8) *gradYY_2*gradYY_2
                         + ((float) 1/16)*gradYY_3*gradYY_3
                         + ((float) 1/8) *gradYY_4*gradYY_4
                         + ((float) 1/4) *gradYY_5*gradYY_5
                         + ((float) 1/8) *gradYY_6*gradYY_6
                         + ((float) 1/16)*gradYY_7*gradYY_7
                         + ((float) 1/8) *gradYY_8*gradYY_8
                         + ((float) 1/16)*gradYY_9*gradYY_9;

            gauss_gradXY = ((float) 1/16)*gradXX_1*gradYY_1
                         + ((float) 1/8) *gradXX_2*gradYY_2
                         + ((float) 1/16)*gradXX_3*gradYY_3
                         + ((float) 1/8) *gradXX_4*gradYY_4
                         + ((float) 1/4) *gradXX_5*gradYY_5
                         + ((float) 1/8) *gradXX_6*gradYY_6
                         + ((float) 1/16)*gradXX_7*gradYY_7
                         + ((float) 1/8) *gradXX_8*gradYY_8
                         + ((float) 1/16)*gradXX_9*gradYY_9;


            norm = (gauss_gradXX+gauss_gradYY);

            harris_pixel = gauss_gradXX*gauss_gradYY - gauss_gradXY - lambda*(norm*norm);
            (*h)[i-1][j-1] = harris_pixel;

            // if(harris_pixel > threshold) {
            //     CvPoint p = {j, i};
            //     (*corners)[*corners_nb] = p;
            //     *corners_nb += 1;
            // }
            if(harris_pixel > threshold) {
                k = *corners_nb -1;
                while(harris_pixel > (*corners)[k].value && k >= 0) {
                    (*corners)[k+1] = (*corners)[k];
                    k--;
                }
                CvPoint p = {j, i};
                (*corners)[k+1].p = p;
                (*corners)[k+1].value = harris_pixel;
                *corners_nb += 1;
            }
        }
    }
}

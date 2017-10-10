#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "ti_alex.h"

/* gcc -o harris.out harris.c ti_alex.c `pkg-config --libs opencv`*/

int** harris(int** gradX, int** gradY, int x, int y, int lambda) {
    int** harris = (int**) malloc((x-4)*sizeof(int*));

    int i, j ;

    uchar gradXX_1, gradXX_2, gradXX_3, gradXX_4, gradXX_5, gradXX_6, gradXX_7, gradXX_8, gradXX_9 ;
    uchar gradYY_1, gradYY_2, gradYY_3, gradYY_4, gradYY_5, gradYY_6, gradYY_7, gradYY_8, gradYY_9 ;

    int gauss_gradXX, gauss_gradYY, gauss_gradXY, norm;

    for(i = 2 ; i < x-2 ; i++) {
        harris[i-2] = (int*) malloc((y-4)*sizeof(int));
        for(j = 2 ; j < y-2 ; j++) {
            gradXX_1 = gradX[i-1][j-1] ;
            gradXX_2 = gradX[i-1][j] ;
            gradXX_3 = gradX[i-1][j+1] ;
            gradXX_4 = gradX[i][j-1] ;
            gradXX_5 = gradX[i][j] ;
            gradXX_6 = gradX[i][j+1] ;
            gradXX_7 = gradX[i+1][j-1] ;
            gradXX_8 = gradX[i+1][j] ;
            gradXX_9 = gradX[i+1][j+1] ;

            gauss_gradXX = (1/16)*gradXX_1*gradXX_1
                         + (1/8) *gradXX_2*gradXX_2
                         + (1/16)*gradXX_3*gradXX_3
                         + (1/8) *gradXX_4*gradXX_4
                         + (1/4) *gradXX_5*gradXX_5
                         + (1/8) *gradXX_6*gradXX_6
                         + (1/16)*gradXX_7*gradXX_7
                         + (1/8) *gradXX_8*gradXX_8
                         + (1/16)*gradXX_9*gradXX_9;

            gradYY_1 = gradY[i-1][j-1] ;
            gradYY_2 = gradY[i-1][j] ;
            gradYY_3 = gradY[i-1][j+1] ;
            gradYY_4 = gradY[i][j-1] ;
            gradYY_5 = gradY[i][j] ;
            gradYY_6 = gradY[i][j+1] ;
            gradYY_7 = gradY[i+1][j-1] ;
            gradYY_8 = gradY[i+1][j] ;
            gradYY_9 = gradY[i+1][j+1] ;

            gauss_gradYY = (1/16)*gradYY_1*gradYY_1
                         + (1/8) *gradYY_2*gradYY_2
                         + (1/16)*gradYY_3*gradYY_3
                         + (1/8) *gradYY_4*gradYY_4
                         + (1/4) *gradYY_5*gradYY_5
                         + (1/8) *gradYY_6*gradYY_6
                         + (1/16)*gradYY_7*gradYY_7
                         + (1/8) *gradYY_8*gradYY_8
                         + (1/16)*gradYY_9*gradYY_9;

            gauss_gradXY = (1/16)*gradXX_1*gradYY_1
                         + (1/8) *gradXX_2*gradYY_2
                         + (1/16)*gradXX_3*gradYY_3
                         + (1/8) *gradXX_4*gradYY_4
                         + (1/4) *gradXX_5*gradYY_5
                         + (1/8) *gradXX_6*gradYY_6
                         + (1/16)*gradXX_7*gradYY_7
                         + (1/8) *gradXX_8*gradYY_8
                         + (1/16)*gradXX_9*gradYY_9;

            norm = (gauss_gradXX+gauss_gradYY);
            harris[i-2][j-2] = gauss_gradXX*gauss_gradYY - gauss_gradXY - lambda*(norm*norm);
        }
    }

    return harris;
}

// int main(int argc, char const *argv[]) {
//
//     return 0;
// }

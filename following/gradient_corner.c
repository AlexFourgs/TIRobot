#include "gradient_corner.h"

void gradient_corner_detection(int** gradX, int** gradY, int size_x, int size_y, int threshold, ValuePoint** corners, int* corners_nb) {
	int i, j, k;

	int gradXX_1, gradXX_2, gradXX_3, gradXX_4, gradXX_5, gradXX_6, gradXX_7, gradXX_8, gradXX_9 ;
	int gradYY_1, gradYY_2, gradYY_3, gradYY_4, gradYY_5, gradYY_6, gradYY_7, gradYY_8, gradYY_9 ;

	float conv_gradXX = 0, conv_gradYY = 0, conv_gradXY = 0;
	float g = 0;

	*corners_nb = 0;

	for(i = 1 ; i < size_y-3 ; i++) {
    	for(j = 1 ; j < size_x-3 ; j++) {
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

			conv_gradXX =  gradXX_1*gradXX_1
                         + gradXX_2*gradXX_2
                         + gradXX_3*gradXX_3
                         + gradXX_4*gradXX_4
                         + gradXX_6*gradXX_6
                         + gradXX_7*gradXX_7
                         + gradXX_8*gradXX_8
                         + gradXX_9*gradXX_9;

			conv_gradYY =  gradYY_1*gradYY_1
                         + gradYY_2*gradYY_2
                         + gradYY_3*gradYY_3
                         + gradYY_4*gradYY_4
                         + gradYY_6*gradYY_6
                         + gradYY_7*gradYY_7
                         + gradYY_8*gradYY_8
                         + gradYY_9*gradYY_9;

			conv_gradXY =  gradXX_1*gradYY_1
                         + gradXX_2*gradYY_2
                         + gradXX_3*gradYY_3
                         + gradXX_4*gradYY_4
                         + gradXX_6*gradYY_6
                         + gradXX_7*gradYY_7
                         + gradXX_8*gradYY_8
                         + gradXX_9*gradYY_9;

			g = ((gradXX_5 * gradXX_5 * conv_gradYY) + (gradYY_5 * gradYY_5 * conv_gradXX) - (2 * gradXX_5 * gradYY_5 * conv_gradXY))/(conv_gradXX + conv_gradYY);

			// if( g > threshold ) {
			// 	CvPoint p = {j, i};
        	// 	(*corners)[*corners_nb] = p;
        	// 	*corners_nb += 1;
			// }

			if(g > threshold) {
                k = *corners_nb -1;
                while(g > (*corners)[k].value && k >= 0) {
                    (*corners)[k+1] = (*corners)[k];
                    k--;
                }
                CvPoint p = {j, i};
                (*corners)[k+1].p = p;
                (*corners)[k+1].value = g;
                *corners_nb += 1;
            }
		}
	}
}

#include "gradient_corner.h"


int** gradient_corner_detection(int** gradX, int** gradY,int size_x, int size_y, int threshold, CvPoint** corners, int* corners_nb){

	uchar gradXX_1, gradXX_2, gradXX_3, gradXX_4, gradXX_5, gradXX_6, gradXX_7, gradXX_8, gradXX_9 ;
    	uchar gradYY_1, gradYY_2, gradYY_3, gradYY_4, gradYY_5, gradYY_6, gradYY_7, gradYY_8, gradYY_9 ;
	int i,j;

	float conv_gradXX = 0, conv_gradYY = 0, conv_gradXY = 0, norm = 0, harris_pixel = 0;
	float k;

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

			conv_gradXX = 1 *gradXX_1*gradXX_1
                         + 1 *gradXX_2*gradXX_2
                         + 1 *gradXX_3*gradXX_3
                         + 1 *gradXX_4*gradXX_4
                         + 1 *gradXX_5*gradXX_5
                         + 0 *gradXX_6*gradXX_6
                         + 1 *gradXX_7*gradXX_7
                         + 1 *gradXX_8*gradXX_8
                         + 1 *gradXX_9*gradXX_9;

			conv_gradYY = 1 *gradYY_1*gradYY_1
                         + 1 *gradYY_2*gradYY_2
                         + 1 *gradYY_3*gradYY_3
                         + 1 *gradYY_4*gradYY_4
                         + 0 *gradYY_5*gradYY_5
                         + 1 *gradYY_6*gradYY_6
                         + 1 *gradYY_7*gradYY_7
                         + 1 *gradYY_8*gradYY_8
                         + 1 *gradYY_9*gradYY_9;

			conv_gradXY = 1 *gradXX_1*gradYY_1
                         + 1 *gradXX_2*gradYY_2
                         + 1 *gradXX_3*gradYY_3
                         + 1 *gradXX_4*gradYY_4
                         + 0 *gradXX_5*gradYY_5
                         + 1 *gradXX_6*gradYY_6
                         + 1 *gradXX_7*gradYY_7
                         + 1 *gradXX_8*gradYY_8
                         + 1 *gradXX_9*gradYY_9;

			k = conv_gradYY * gradX[i][j] + gradY[i][j] * conv_gradXX - 2 *(gradX[i][j] * gradY[i][j]) * conv_gradXY;

			if( k > threshold ){
				CvPoint p = {j, i};
                		(*corners)[*corners_nb] = p;
                		*corners_nb += 1;
			}
		}
	}


	return 0;
}

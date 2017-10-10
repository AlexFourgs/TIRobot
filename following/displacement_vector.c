#include "displacement_vector.h"

int cross_correlation(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_win_x, int size_win_y){

	int i;
	int j;
	int sum=0;
	int x;
	int y;

	//cross correlation
	for(j=-size_win_y/2;j< size_win_y/2;j++){
		for(i=-size_win_x/2;i< size_win_x /2;i++){
			sum = sum + image_1[ptx1 + i][pty1 + j] * image_2[ptx2 + i][pty2 + j];
		}
	}



	return sum;

}

/**
  * distance euclidienne
*/

int euclidian_distance(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_win_x, int size_win_y){

        int i;
        int j;
        int sum=0;
        int x;
        int y;

        //cross correlation
        for(j=-size_win_y/2;j< size_win_y/2;j++){
                for(i=-size_win_x/2;i< size_win_x /2;i++){
                        sum = sum + sqrt(pow(image_1[ptx1 + i][pty1 + j],2) - pow(image_2[ptx2 + i][pty2 + j],2));
                }
        }



        return sum;

}

/**
  * match one point of image 1 with all corners of image 2
*/

int matching_point(uchar** image_1 , uchar** image_2,int size_x, int size_y, int ptx, int pty, uchar** harris2, int window_size){

	//browse all the harris points from the image 1 and compare with all harris point of image2

	int i;
	int j;

	for(j=pty - window_size /2; i< pty + window_size /2; j++){
		for(i= ptx - window_size /2; i< ptx + window_size /2; i++){
			if((j > 0) && (j< size_y)&&(i> 0)&&(i < size_x)){
				// method 1 : choose the minimum euclidian distance between points
				
				// method 2 : choose the minimum euclidian distance between patch

			}
		}
	}

	//keep the minimum value
	return 0;
}

/*int main() {
	uchar img1[3][3];
	img1[0][0]=0;
	img1[0][1]=255;
	img1[0][2]=0;
	img1[1][0]=255;
	img1[1][1]=255;
	img1[1][2]=0;
	img1[2][0]=255;
	img1[2][1]=0;
	img1[2][2]=255;
}*/

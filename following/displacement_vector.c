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


int matching_point(uchar** image_1 , uchar** image_2, int ptx, int pty, uchar** harris2, int window_size){

	//browse all the harris points from the image 1 and compare with all harris point of image2

	int i;
	int j;

	
	//compare them with cross correlation
	//keep the minimum value
	return 0;
}

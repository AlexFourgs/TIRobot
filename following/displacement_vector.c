#include "displacement_vector.h"

int** cross_correlation(int** image_1, int** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_win_x, int size_win_y){

	int i;
	int j;
	int sum=0;
	int x;
	int y;

	//cross correlation
	for(j=-size_win_y;j< size_win_y;j++){
		for(i=-size_win_x;i< size_win_x;i++){
			sum = sum + image_1[ptx1 + i][pty1 + j] * image_2[ptx2 + i][pty2 + j];
		}
	}



	return NULL;

}

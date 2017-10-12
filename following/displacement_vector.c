#include "displacement_vector.h"


double cross_correlation(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch){

	int i;
	int j;
	double sum=0;
	int x;
	int y;

	//cross correlation
	for(j=-size_patch/2;j< size_patch/2;j++){
		for(i=-size_patch/2;i< size_patch /2;i++){
			sum = sum + image_1[ptx1 + i][pty1 + j] * image_2[ptx2 + i][pty2 + j];
		}
	}



	return sum;

}

/**
  * distance euclidienne
*/

double euclidian_distance(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch){

        int i;
        int j;
        double sum=0;
        int x;
        int y;

	//let the value of patch size at constant value like 3 or check if the value is unpair

        //cross correlation
        for(j=-size_patch/2;j< size_patch/2;j++){
                for(i=-size_patch/2;i< size_patch /2;i++){

                        sum = sum + pow(image_2[ptx1 + i][pty1 + j] - image_1[ptx2 + i][pty2 + j],2);
                }
        }



        return sqrt(sum);

}

/**
  * match one point of image 1 with all corners of image 2
*/

CvPoint matching_point(uchar** image_1 , uchar** image_2,int size_x, int size_y, int ptx, int pty, CvPoint* harris2, int window_size, int size_patch){

	//browse all the harris points from the image 1 and compare with all harris point of image2

	int i;
	double distance=0;
	double distance_prev= 100000000;

	int ptx_nearest;
	int pty_nearest;

	double patch_distance = 0;
	double patch_distance_prev = 100000000;

	int ptx_nearest_patch = 0;
	int pty_nearest_patch = 0;

	CvPoint matching_point;

	for(i=0 ; i < sizeof(harris2); i++){

		if((harris2[i].x > 0) && (harris2[i].x < size_x) && (harris2[i].y > 0) && (harris2[i].y < size_y) && (abs(harris2[i].x - ptx) < window_size/2) && (abs(harris2[i].y - pty) < window_size)){
			// method 1 : choose the minimum euclidian distance between points
			distance = sqrt(pow(harris2[i].x - ptx, 2) + pow(harris2[i].y- pty, 2));

			if(distance < distance_prev){
				distance_prev = distance;
				ptx_nearest = harris2[i].x;
				pty_nearest = harris2[i].y;
			}

			// method 2 : choose the minimum euclidian distance between patch
			patch_distance = euclidian_distance(image_1, image_2, size_x, size_y, ptx, harris2[i].x, pty, harris2[i].y,size_patch);
			if(patch_distance < patch_distance_prev){
				patch_distance_prev = patch_distance;
				ptx_nearest_patch = harris2[i].x;
				pty_nearest_patch = harris2[i].y;
			}
		}
	}

	//keep the minimum value
	matching_point.x = ptx_nearest_patch;
	matching_point.y = pty_nearest_patch;

	return matching_point;
}


Vector find_all_matches(uchar** image_1, uchar** image_2, int size_x, int size_y, CvPoint* harris1, CvPoint* harris2, int size_window, int size_patch, Match* matches){

	CvPoint pt1;
	CvPoint pt2;

	matches = calloc(5000, sizeof(Match));

	int i;
	int dx;
	int dy;
	int imax = 0;
	int ymax = 0;
	int count_max = 0;
	int count = 0;
	int displacement_table[size_window][size_window];
	Vector vector;

	for(i=0; i< sizeof(harris1);i++){
		pt1.x = harris1[i].x;
		pt1.y = harris1[i].y;

		pt2 = matching_point(image_1, image_2, size_x, size_y, pt1.x,pt1.y, harris2, size_window, size_patch);

		// compute distance x and y and add to the score table
		dx = pt2.x - pt1.x;
		dy = pt2.y - pt2.y;

		matches[i].pt1 = pt1;
		matches[i].pt2 = pt2;

		// fill accumulation table
		displacement_table[dx + 50][dy + 50] ++;
		count = displacement_table[dx + 50][dy + 50];
		if(count > count_max){
			imax = dx + 50;
			ymax = dy + 50;
			count_max = count;
		}


	}

	vector.dx = imax - 50;
	vector.dy = ymax - 50;

	return vector;

}

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

        //cross correlation
        for(j=-size_patch/2;j<= size_patch/2;j++){
                for(i=-size_patch/2;i<= size_patch /2;i++){
			//printf("i %d\n", pty1);
                        sum = sum + pow(image_1[ptx1 + j][pty1 + i] - image_2[ptx2 + j][pty2 + i],2);
                }
        }

        return sqrt(sum);

}

/**
  * match one point of image 1 with all corners of image 2
*/

CvPoint matching_point(uchar** image_1 , uchar** image_2,int size_x, int size_y, int ptx, int pty, ValuePoint* harris2, int window_size, int size_patch, int nbPoints){

	//browse all the harris points from the image 1 and compare with all harris point of image2

	int i;
	double distance=0;
	double distance_prev= 100000000;

	int ptx_nearest = ptx;
	int pty_nearest = pty;

	double patch_distance = 0;
	double patch_distance_prev = 100000000;

	int ptx_nearest_patch = 51;
	int pty_nearest_patch = 51;

	CvPoint matching_point;

	for(i=0 ; i < nbPoints; i++){
		CvPoint h2i = harris2[i].p;

		if((h2i.x > 3) && (h2i.x < size_x-3) && (h2i.y > 3) && (h2i.y < size_y-3) && (abs(h2i.y - pty) < window_size/2) && (abs(h2i.x - ptx) < window_size/2)){
			// method 1 : choose the minimum euclidian distance between points
			distance = sqrt(pow(h2i.y - pty, 2) + pow(h2i.x- ptx, 2));

			if(distance < distance_prev){
				distance_prev = distance;
				ptx_nearest = h2i.x;
				pty_nearest = h2i.y;
			}

			// method 2 : choose the minimum euclidian distance between patch
			patch_distance = euclidian_distance(image_1, image_2, size_x, size_y, pty, h2i.y, ptx, h2i.x,size_patch);
			if(patch_distance < patch_distance_prev){
				patch_distance_prev = patch_distance;
				ptx_nearest_patch = h2i.x;
				pty_nearest_patch = h2i.y;
			}
		}
	}

	//keep the minimum value
	matching_point.x = ptx_nearest_patch;
	matching_point.y = pty_nearest_patch;

	return matching_point;
}


Vector find_all_matches(uchar** image_1, uchar** image_2, int size_x, int size_y, ValuePoint* harris1, ValuePoint* harris2, int size_window, int size_patch, Match* matches, int nbPoints1, int nbPoints2){

	CvPoint pt1;
	CvPoint pt2;

	//matches = calloc(5000, sizeof(Match));

	int i;
	int dx=0;
	int dy=0;
	int imax = 25;
	int ymax = 25;
	int count_max = 0;
	int count = 0;

	int** displacement_table ;
	displacement_table= (int**)calloc(size_window,sizeof(int*));
	int u,v;

	for(v=0;v<size_window;v++){
		displacement_table[v] = (int*)calloc(size_window,sizeof(int**));
	}

	for(i=0; i< nbPoints1;i++){
		pt1.x = harris1[i].p.x;
		pt1.y = harris1[i].p.y;
		pt2 = matching_point(image_1, image_2, size_x, size_y, pt1.x,pt1.y, harris2, size_window, size_patch, nbPoints2);

		// compute distance x and y and add to the score table
		if((pt2.x!=51)&&(pt2.y)){
			dx = pt2.x - pt1.x;
			dy = pt2.y - pt1.y;

		// fill accumulation table
			displacement_table[dx + 25][dy + 25] = displacement_table[dx+25][dy+25] + 1;
			count = displacement_table[dx + 25][dy + 25];
			if(count > count_max){
				imax = dx + 25;
				ymax = dy + 25;
				count_max = count;
			}
		}

	}

	for(v=0;v<size_window;v++){
		free(displacement_table[v]);
	}

	free(displacement_table);
	Vector vector = {imax-25, ymax -25};
	vector.dx = imax - 25;
	vector.dy = ymax - 25;

	return vector;

}

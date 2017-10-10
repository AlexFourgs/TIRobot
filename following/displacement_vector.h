#ifndef DISPLACEMENT_VECTOR
#define DISPLACEMENT_VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <highgui.h>
#include <cv.h>
#include <pthread.h>



typedef struct Point{

	int x;
	int y;
}Point;

typedef struct Match{

	Point pt1;
	Point pt2;
}Match;

double cross_correlation(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch);
Point matching_point(uchar** image_1 , uchar** image_2, int size_x, int size_y, int ptx, int pty, Point* harris2, int window_size, int size_patch);
double euclidian_distance(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch);
Match find_all_matches(uchar** image_1, uchar** image_2, int size_x, int size_y, Point* harris1, Point* harris2, int size_window, int size_patch);


#endif

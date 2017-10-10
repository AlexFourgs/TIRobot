#ifndef DISPLACEMENT_VECTOR
#define DISPLACEMENT_VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <highgui.h>
#include <cv.h>
#include <pthread.h>

double cross_correlation(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch);
int matching_point(uchar** image_1 , uchar** image_2, int size_x, int size_y, int ptx, int pty, uchar** harris2, int window_size, int size_patch);
double euclidian_distance(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch);



#endif

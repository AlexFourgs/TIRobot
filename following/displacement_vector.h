#ifndef DISPLACEMENT_VECTOR
#define DISPLACEMENT_VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <highgui.h>
#include <cv.h>
#include <pthread.h>

int** sum_square_distance(int** image_1, int** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_win_x, int size_win_y);



#endif
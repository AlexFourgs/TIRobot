#ifndef __HARRIS__
#define __HARRIS__

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "ti_alex.h"
#include "displacement_vector.h"

int** harris(int** gradX, int** gradY, int x, int y, float lambda, int threshold, CvPoint** corners, int* corners_nb);

#endif

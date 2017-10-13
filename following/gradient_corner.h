/**
 * \file displacement_vector.c
 * \brief This file compute some distances of many points and match the features of two images
 * \author Alexis AKTOR
 * \date 10 October 2017
*/

#ifndef GRADIENT_CORNER
#define GRADIENT_CORNER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <pthread.h>
#include "ValuePoint.h"

void gradient_corner_detection(int** gradX, int** gradY, int size_x, int size_y, int threshold, ValuePoint** corners, int* corners_nb);

#endif

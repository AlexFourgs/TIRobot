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
#include <highgui.h>
#include <cv.h>
#include <pthread.h>

int gradient_corner_detection(int** gradX, int** gradY,int size_x, int size_y, CvPoint** corners, int* corners_nb);

#endif

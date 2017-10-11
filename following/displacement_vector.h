/**
 * \file displacement_vector.c
 * \brief This file compute some distances of many points and match the features of two images
 * \author Alexis AKTOR
 * \date 10 October 2017
*/

#ifndef DISPLACEMENT_VECTOR
#define DISPLACEMENT_VECTOR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <highgui.h>
#include <cv.h>
#include <pthread.h>

/**
 * \struct Point
 * \brief struct to contains the x_axis and the y_axis of a point
 * \var x x_axis
 * \var y y_axis 
*/

typedef struct Point{

	int x;
	int y;
}Point;

/**
 * \struct Match
 * \brief struct to contains both points of a match
 * \var pt1 point 1
 * \var pt2 point 2
*/

typedef struct Match{

	Point pt1;
	Point pt2;
}Match;



/**
 * \fn double cross_correlation(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch)
 * \brief this function take the one point in an image 1 and another point in an image 2. And then compute the cross_correlation between the window around the tow points
 * \param image_1 first image to compare
 * \param image_2 second image to compare
 * \param size_x size of the screen in x_axis
 * \param size_y size of the screen in y_axis
 * \param ptx1 point1 to compare in x_axis
 * \param ptx2 point2 to compare in x_axis
 * \param pty1 point1 to compare in y_axis
 * \param pty1 point2 to compare in y_axis
 * \param size_patch size of the patch/window around the corner
 * \return the score of the correlation
*/

double cross_correlation(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch);

/**
 * \fn Point matching_point(uchar** image_1 , uchar** image_2, int size_x, int size_y, int ptx, int pty, Point* harris2, int window_size, int size_patch)
 * \brief This function score one corner of an image1 with all corners with an image2 
 * \param image_1 first image to compare
 * \param image_2 second image to compare
 * \param size_x size of the screen in x_axis
 * \param size_y size of the screen in y_axis
 * \param ptx1 point1 to compare in x_axis
 * \param ptx2 point2 to compare in y_axis
 * \param harris2 array with all corners of the second image
 * \param window_size size of the research area
 * \param size_patch size of the patch/window around the corner
 * \return the point in the second image which is matching more of each others with the point to compare
*/

CvPoint matching_point(uchar** image_1 , uchar** image_2, int size_x, int size_y, int ptx, int pty, CvPoint* harris2, int window_size, int size_patch);

/**
 * \fn double euclidian_distance(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch)
 * \brief this function take two images and two corners in each image. And compute the euclidian distance of the matrix around both points
 * \param image_1 first image to compare
 * \param image_2 second image to compare
 * \param size_x size of the screen in x_axis
 * \param size_y size of the screen in y_axis
 * \param ptx1 point1 to compare in x_axis
 * \param ptx2 point2 to compare in x_axis
 * \param pty1 point1 to compare in y_axis
 * \param pty1 point2 to compare in y_axis
 * \param size_patch size of the patch/window around the corner
 * \return the score of the euclidian distance
*/


double euclidian_distance(uchar** image_1, uchar** image_2, int size_x, int size_y, int ptx1, int ptx2, int pty1, int pty2, int size_patch);

/**
 * \fn Match find_all_matches(uchar** image_1, uchar** image_2, int size_x, int size_y, Point* harris1, Point* harris2, int size_window, int size_patch)
 * \brief take all the corners of an image 1 and an image 2 and say wich point of the image 1 corresponds the most
 * \param image_1 first image to compare
 * \param image_2 second image to compare
 * \param size_x size of the screen in x_axis
 * \param size_y size of the screen in y_axis
 * \param harris1 set of all corners of the image1
 * \param harris2 set of all corners of the image2
 * \param window_size size of the research area
 * \param size_patch size of the patch/window around the corner
 * \return all matches but after we will return something else
*/


Point find_all_matches(uchar** image_1, uchar** image_2, int size_x, int size_y, CvPoint* harris1, CvPoint* harris2, int size_window, int size_patch);


#endif

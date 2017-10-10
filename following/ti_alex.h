#ifndef TI_ALEX
#define TI_ALEX

#include <opencv/highgui.h>
#include <opencv/cv.h>


uchar greyscale_pixel(IplImage* pixel, int i, int j);
uchar** greyscale_img(IplImage* img, int x, int y);

int** grad(IplImage* image, int x, int y);

#endif

#ifndef TI_ALEX
#define TI_ALEX

#include <highgui.h>
#include <cv.h>


uchar greyscale_pixel(IplImage* pixel, int i, int j);
uchar** greyscale_img(IplImage* img, int x, int y);

uchar** grad(IplImage* image, int x, int y);

#endif

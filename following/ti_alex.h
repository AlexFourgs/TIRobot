#ifndef TI_ALEX
#define TI_ALEX

#include <opencv/highgui.h>
#include <opencv/cv.h>
/*
#include "./Lib/def.h"
#include "./Lib/nrio.h"
#include "./Lib/nrarith.h"
#include "./Lib/nralloc.h"
*/

uchar greyscale_pixel(IplImage* pixel, int i, int j);
void greyscale_img(IplImage* img, int x, int y, uchar*** gr);

void grad(IplImage* image, int nb_ligne, int nb_colonne, int*** norme_grad, int*** img_sobel_vert, int*** img_sobel_hori, uchar*** gr);


#endif

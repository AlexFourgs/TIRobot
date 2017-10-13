#ifndef __VALUEPOINT__
#define __VALUEPOINT__

#include "opencv/cv.h"

typedef struct ValuePoint ValuePoint;
struct ValuePoint {
    CvPoint p;
    int value;
};

#endif

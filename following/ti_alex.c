#include <stdio.h>
#include <stdlib.h>
#include "ti_alex.h"

int greyscale_pixel(int r, int g, int b){
    return ((r+g+b)/3) ;
}

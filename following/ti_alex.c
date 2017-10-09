#include <stdio.h>
#include <stdlib.h>

int greyscale_pixel(int r, int g, int b){
    return ((r+g+b)/3) ;
}

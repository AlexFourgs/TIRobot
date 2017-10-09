/*! \file  mprocess.c
 *  \brief Image process
 *
 * functions for image processing
 */ 


#include "mvideo.h"


extern int mywidth;
extern int myheight;
extern unsigned char * grayscale_buff;


/*!  swap red  and blue  chanels */

void swap_rgb24(unsigned char *buf, struct Camera* camera)
{
  char  c;
  char *p = buf;
  int   i = mywidth*myheight;
  int bytes_per_rgb = 3;
  
  if(!camera->greyscale)
    {

      while (--i) 
	{
	  c = p[0]; p[0] = p[2]; p[2] = c;
	 // p[0] = p[1]  = p[2];
	  p += bytes_per_rgb;
	}
    } 
}






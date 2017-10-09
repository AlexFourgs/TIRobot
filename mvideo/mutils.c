/*! \file  mutils.c
 *  \brief tools for mvideo aplication
 *
 * Put in this file the tools needed for capture applications:
 * saving images, output traces, etc...
 */ 

#include "mvideo.h"



/**! 
Save the camera buffer into a ppm file   
*/

void ppm_save_util(struct Camera *camera,char *nam,int w, int h)
{
  FILE *outfile;
  int i;

  outfile = fopen(camera->device_name, "w");
  
  if (outfile == NULL)
    {
      printf("Could not open file");
      return;
    }
 
  
  fprintf (outfile, "P3\n%d %d\n%d\n", w, h, 255); /**! header */
  if (camera->greyscale) /**!case of a bw image*/
    {
      for (i = 0; i < w*h; i++)
	{ 
	  fprintf (outfile, "%03d %03d %03d\n", camera->pic[i], camera->pic[i], camera->pic[i]);
	}
    }
  else  /**!case of a color image*/
    for (i = 0; i < h*w*3; i=i+3)
      { 
	fprintf (outfile, "%03d %03d %03d\n", camera->pic[i], camera->pic[i+1], camera->pic[i+2]);
      }
  
  fclose(outfile);

}


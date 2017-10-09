/*! \file  mvideo.c
 *  \brief video handle functions
 * 
 *  This file contains the functions needed for video capture :
 *  opening, get info, set parameters, grab display and close the video port. 
 */ 


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <linux/types.h> 
#include <linux/videodev.h>
#include <signal.h>
#include "mvideo.h"
#include "ccvt.h"
#include <gtk/gtk.h>

//#define DEBUG

sem_t s_draw;
sem_t s_grab1;
int plsquit = 0;
int x_frames = 0;
int y_frames = 0;
int mywidth;
int myheight;
int nb_frames = 0;
int arg_x;
int arg_y;
int scale=1;

void open_cam(struct Camera *camera) 
{
#ifdef DEBUG
    printf("Entering %s\n", __FUNCTION__);
#endif
  printf("device : %s \n",camera->device_name);
  if((camera->dev<=0)){
    camera->dev = open(camera->device_name, O_RDWR);
    if (camera->dev < 0) {
      perror(camera->devname);
      exit(1);
    }
  }
  pthread_mutex_unlock( &camera->iscam_mutex );
}


void close_cam(struct Camera *camera, int quiting)
{
#ifdef DEBUG
    printf("Entering %s\n", __FUNCTION__);
#endif
  pthread_mutex_lock( &camera->iscam_mutex );
  if(camera->dev > 0){
    close(camera->dev);
    camera->dev = 0;
  }
}


void init_cam(struct Camera *camera)
{
#ifdef DEBUG
    printf("Entering %s\n", __FUNCTION__);
#endif

  camera->greyscale = 0;
  camera->pic = NULL;
  camera->picbuff = NULL;
  camera->pixmap = NULL;
  camera->draw = 0;
  camera->update_camera = 0;
  camera->capture = 1;
  camera->dev = 0;
  camera->swapcolors = 1;

  pthread_mutex_init( &camera->pref_mutex, NULL ); /* utilité a verifier lié aux widget gtk */
  pthread_mutex_init( &camera->iscam_mutex, NULL ); /* is there an open cam? */
}


void set_cam_info(struct Camera *camera)
{
  int palette;
  int depth;
#ifdef DEBUG
    printf("Entering %s\n", __FUNCTION__);
#endif
    palette=camera->vid_pic.palette;
    depth=camera->vid_pic.depth;
    
    camera->vid_pic.palette = VIDEO_PALETTE_RGB24;
    camera->vid_pic.depth   = 24;

  if (ioctl (camera->dev, VIDIOCSPICT, &camera->vid_pic) < 0) {
    perror ("ioctl (VIDIOCSPICT)");
    printf("Reverting to old palette\n");
    camera->vid_pic.palette = palette;
    camera->vid_pic.depth   = depth;
    ioctl(camera->dev,VIDIOCSPICT,&camera->vid_pic);
  }
  camera->vid_win.height=myheight;
  camera->vid_win.width=mywidth;
  if (ioctl (camera->dev, VIDIOCSWIN, &camera->vid_win) < 0) {
    perror ("ioctl (VIDIOCSWIN)");
  }
  ioctl (camera->dev, VIDIOCGWIN, &camera->vid_win);
mywidth=camera->vid_win.width;
myheight=camera->vid_win.height;

}


void get_cam_info(struct Camera *camera)
{ 
  int i;
  struct video_clip vid_clips[32];
  int index=-1;
  
#ifdef DEBUG
  printf("Entering %s\n", __FUNCTION__);
#endif

   camera->vid_chan.channel=0;
    while (!ioctl(camera->dev,VIDIOCGCHAN,&(camera->vid_chan)))
      {
	if (camera->vid_chan.type == VIDEO_TYPE_CAMERA)
	  {
#ifdef DEBUG
	    printf("%d\t%s\n",camera->vid_chan.channel,camera->vid_chan.name);
#endif
	    if (strstr(camera->vid_chan.name,"Composite"))
	      {
#ifdef DEBUG
		printf("Composite\n");
		printf("Current Norm : %d\n",camera->vid_chan.norm);
#endif
	        index=camera->vid_chan.channel;
		camera->type=CAM_COMPOSITE;
		break;
	      }
	    if (strstr(camera->vid_chan.name,"Camera") || strstr(camera->vid_chan.name,"Webcam"))
	      {
#ifdef DEBUG
		printf("Camera\n");
#endif
	        index=camera->vid_chan.channel;
		camera->type=0;
		break;
	      }
	  }
	camera->vid_chan.channel++;
      }
  if (index == -1)
  {
     printf("Invalid device !\n");
     close(camera->dev);
     exit(1);
  }
  printf("Using input : %d\n",index);
  if (ioctl(camera->dev, VIDIOCGCAP, &camera->vid_caps)<0)
    {
      perror("ioctl VIDIOCGCAP");
    }
  if (camera->type == CAM_COMPOSITE)
  { 
	  camera->vid_caps.maxwidth=768;
	  camera->vid_caps.maxheight=576;
  }
  mywidth= (camera->vid_caps.maxwidth < arg_x  || !arg_x) ? camera->vid_caps.maxwidth : arg_x;
  mywidth/=scale;
  myheight=(camera->vid_caps.maxheight < arg_y || !arg_y) ? camera->vid_caps.maxheight : arg_y;
  myheight/=scale;

  printf("Maximum Size : %dx%d\n",mywidth,myheight);

  if (ioctl(camera->dev, VIDIOCGWIN, &camera->vid_win)<0)
    {
      perror("ioctl VIDIOCGWIN");
    }
  printf("Capture window : %d,%d,%d,%d\n",camera->vid_win.x,camera->vid_win.y,camera->vid_win.width,camera->vid_win.height);
  if (ioctl(camera->dev, VIDIOCGPICT, &camera->vid_pic)<0)
    {
      perror("ioctl VIDIOCGPICT");
    }
  printf("Current Palette : %d\n",camera->vid_pic.palette);
  printf("Current Depth   : %d\n",camera->vid_pic.depth);
  for (i = 0; i < 32; i++) {
    vid_clips[i].x      = 0;
    vid_clips[i].y      = 0;
    vid_clips[i].width  = 0;
    vid_clips[i].height = 0;
  }
  camera->vid_win.clips = vid_clips;
  camera->vid_win.clipcount = 0;

  //allocation monocrome (1 bande)
  if (camera->vid_caps.type & VID_TYPE_MONOCHROME) {
    camera->greyscale = 1;
    camera->pic = realloc( camera->pic, mywidth*myheight);
    camera->picbuff = realloc( camera->picbuff, mywidth*myheight );
#ifdef DEBUG
    printf("monochrome\n");
#endif
  }
  //allocation couleur (3 bandes)
  else {
    camera->greyscale = 0; //modif pour test de btttv, en attendant la couleur   0 normalement
    camera->pic = realloc(camera->pic, mywidth*myheight*3);
    camera->picbuff = realloc(camera->pic, mywidth*myheight*3); //a voir avec le pic
#ifdef DEBUG
    printf("couleur\n");
#endif
  }
  
}

//ajout pour prendre en compte bttv
//apres get_cam_info, obligé.
void select_cam(struct Camera* camera)
{
	int i;
#ifdef DEBUG
  printf("Entering %s\n", __FUNCTION__);
#endif
  
  if (camera->type == CAM_COMPOSITE)
  {
    camera->vid_chan.norm = VIDEO_MODE_PAL;
  }
  

  if (ioctl (camera->dev, VIDIOCSCHAN, &camera->vid_chan) == -1) {
    perror ("ioctl (VIDIOCSCHAN)");
  }
  
  /* try to setup mmap-based capture */
  /* query for buffer infos */
  memset(&camera->vid_buff,0,sizeof(struct video_mbuf));
  if (ioctl(camera->dev, VIDIOCGMBUF, &camera->vid_buff) == -1) {
    perror("ioctl (VIDIOCGMBUF)");	
  }
  camera->vid_buff.frames=(camera->vid_buff.frames>2) ? 2 : camera->vid_buff.frames; /* au dessus de 2 frames le bttv a du mal*/
  camera->data=malloc(camera->vid_buff.frames*sizeof(char *)); 
  camera->vid_mmap=(struct video_mmap *)malloc(camera->vid_buff.frames*sizeof(struct video_mmap));
 for(i=0;i<camera->vid_buff.frames;i++)
 {
   camera->vid_mmap[i].format = camera->vid_pic.palette;
   camera->vid_mmap[i].frame = i;
   camera->vid_mmap[i].width =  mywidth;
   camera->vid_mmap[i].height = myheight;
 }
 camera->data[0] = mmap(0, camera->vid_buff.size,
			 PROT_READ | PROT_WRITE, MAP_SHARED,
			 camera->dev, 0);
  if ((int) camera->data[0] == -1) 
    {
      fprintf(stderr, "echec\n");
    }
  for (i=1;i<camera->vid_buff.frames;i++)
    camera->data[i] = camera->data[i-1] + camera->vid_buff.offsets[i];
}




void display(struct Camera *camera) 
{
  int width,height;
  unsigned char *rgb_buf=NULL;

#ifdef DEBUG
  printf("Entering %s\n", __FUNCTION__);
#endif

  while( !plsquit ) {
    if( !sem_wait( &s_draw ) ) 
      {
	unsigned char *tmp;
#ifdef DEBUG
	printf("display start\n");
#endif
	tmp = camera->pic;
	if (camera->vid_pic.palette!=VIDEO_PALETTE_YUV420P)
	  rgb_buf=camera->pic;
	
	camera->pic = camera->picbuff;
	camera->picbuff = tmp;
	
	
	
	//on affiche ici l'image
	width = camera->vid_mmap[0].width;
	height= camera->vid_mmap[0].height;

	if (camera->vid_pic.palette==VIDEO_PALETTE_YUV420P)
	  {
	     if (rgb_buf)
	       {
	         rgb_buf=(unsigned char*)realloc(rgb_buf,width*height*3);
	       }
	     else
	       {
		 rgb_buf=(unsigned char*)malloc(width*height*3);
	       }
	     ccvt_420p_rgb24(width,height,tmp,rgb_buf);
	  }
		if (camera->swapcolors)
		  swap_rgb24(rgb_buf,camera);


	/*put image process here*/

	


	if (camera->drawing_area->window)
	  {
	    gdk_threads_enter();
	    gdk_draw_rgb_image (camera->drawing_area->window, camera->drawing_area->style->fg_gc[GTK_STATE_NORMAL], 0, 0,width,height, GDK_RGB_DITHER_NORMAL, rgb_buf,width*3 );     
	    gdk_threads_leave();
	  }
	else
	  {
	    gtk_main_quit();
	  }
	sem_post( &s_grab1 );              
#ifdef DEBUG
	printf("Display stop\n");
#endif
      }
  }
  if (camera->vid_pic.palette==VIDEO_PALETTE_YUV420P)
    if(rgb_buf)
      {
        free(rgb_buf);
      }

  return; 
}


void grab_image(struct Camera *camera)
{
  int i,j;
  int current_buffer = 1;
  int old_buffer=0;
  int width, height;
 
//  get_cam_info(camera);
      if (ioctl(camera->dev, VIDIOCMCAPTURE, &camera->vid_mmap[old_buffer]) == -1) 
	{
	  perror("ioctl VIDIOCMCAPTURE");
	  ioctl(camera->dev, VIDIOCSYNC,&camera->vid_mmap[old_buffer]);
	} 

  while ( !plsquit ) {
    // order matters! the sem_waits MUST be before the mutex lock
    if( !sem_wait( &s_grab1 ) && !pthread_mutex_lock( &camera->iscam_mutex )) {
#ifdef DEBUG
      printf("grab_image start\n");
#endif
/*      pthread_mutex_lock( &camera->pref_mutex );
      if (camera->update_camera){ 
	set_cam_info(camera);
	get_cam_info(camera);
	camera->update_camera = 0;
      }
      pthread_mutex_unlock( &camera->pref_mutex );*/
  
      /* grab image surement a mettre dans get_cam_info*/
      if (ioctl(camera->dev, VIDIOCMCAPTURE, &camera->vid_mmap[current_buffer]) == -1) 
	{
	  perror("ioctl VIDIOCMCAPTURE");
//	  ioctl(camera->dev, VIDIOCSYNC,&camera->vid_mmap[old_buffer]);
	} 
      else {
	  width = camera->vid_mmap[old_buffer].width;
	  height= camera->vid_mmap[old_buffer].height;
	if (ioctl(camera->dev,VIDIOCSYNC,&camera->vid_mmap[old_buffer]) == -1) 
	  {
	    perror("ioctl VIDIOCSYNC");
	  }
	nb_frames++;
      }
      
      if (camera->greyscale == 1)
	{
	  for (i = 0; i < height; i++)
	    for (j = 0; j < width; j++) 
	      camera->picbuff[(j + i * width)] = camera->data[current_buffer][j + i * width];
	  
	  //ceci est ok avec une camera couleur, forcee en camera->greyscale == 1 et em VIDEO_PALETTE_GREY
	  // le ppm est correct
	  // ppm_save_util(camera,"toto.ppm",width,height);
	}
      else
	{
	  if (camera->vid_pic.palette==VIDEO_PALETTE_YUV420P)
 	    memcpy(camera->picbuff,camera->data[old_buffer],width*height*3/2);
	  else
 	    memcpy(camera->picbuff,camera->data[old_buffer],width*height*3);
	 
	}
       old_buffer=current_buffer;
       current_buffer = (current_buffer+1>=camera->vid_buff.frames) ? 0 : current_buffer+1;

    pthread_mutex_unlock( &camera->iscam_mutex );
    sem_post( &s_draw );    
#ifdef DEBUG
    printf("grab_image stop\n");
#endif
    }
  }
}
  
void fps(void *data)
{
	int myframes;

	while (1)
	{
		sleep(2);
		myframes=nb_frames;
		nb_frames=0;
		printf("%d\n",myframes/2);
	}
}

int increment_second_counter(struct Camera *camera) {
  static int x_seconds = 0;
  
  x_seconds++;
  // the following just prevents integer wrap
  if( ( x_seconds % 512 ) == 0 ) {
    x_seconds /= 2;
    x_frames /= 2;
  }
  camera->fps_avg = x_frames / x_seconds;
  camera->fps_current = y_frames;
  y_frames = 0;
  
  return 0;
}

int main(int argc, char *argv[])
{
  static struct Camera camera;
  pthread_t grab_thread;
  pthread_t draw_thread;
  pthread_t fps_thread;
  int with_fps=0;
  int c;
  extern char *optarg;
  int n_arg=0;
 

  GtkWidget *window;

  while  ((c=getopt(argc,argv,"c:x:y:s:f"))!=EOF)
    {
      switch (c)
	{
	  case 'c':	strcpy(camera.device_name,optarg);
			n_arg++;
			break;
	  case 'x':	arg_x=atoi(optarg);
			break;
	  case 'y':	arg_y=atoi(optarg);
			break;
	  case 's':	scale=atoi(optarg);
			break;
	  case 'f':	with_fps=1;
	  default: break;
	}
    }
  if (!n_arg)
    {
      strcpy(camera.device_name,"/dev/video");
    }
  


  g_thread_init(NULL);
  gdk_threads_init();  
  gtk_init (&argc, &argv);
  gdk_rgb_init();


  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  

  camera.drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (camera.drawing_area, 300, 300);
  gtk_container_add (GTK_CONTAINER (window), camera.drawing_area);
  gtk_widget_show_all (window);

  init_cam(&camera);
  camera.window=window;
  //semaphores
  
  sem_init( &s_draw, 0, 0 );
  sem_init( &s_grab1, 0, 1 );
  open_cam(&camera);
  get_cam_info(&camera);
  set_cam_info(&camera);
  select_cam (&camera);


  pthread_create(&grab_thread, NULL, (void *)&grab_image, (void*)&camera);
  pthread_create(&draw_thread, NULL, (void *)&display, (void*)&camera);
  if(with_fps)
    pthread_create(&fps_thread,NULL, (void *)&fps,NULL);
  
  /* PROCEDURE DE QUIT TRES IMORTANTE
  plsquit = 1; // ask our threads to quit
  // update semaphores and mutexes so threads can run and finish
  
  sem_post( &s_draw );
  sem_post( &s_grab1 );
  // join the threads cleanly
  pthread_join( grab_thread, NULL );
  pthread_join( draw_thread, NULL );
  
  close_cam(&camera, 1);
  exit(0);*/
  
  gtk_main ();
  

  return 0;

}




#ifndef MVIDEO_H
#define MVIDEO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/videodev.h>
#include <gtk/gtk.h>
#include <fcntl.h>
#include <pthread.h>

struct Timer_Struct
{
  int time;
  int unit;
  int beep;
  int iscommand;
  char command[255];
 
};

enum Unit_Types {
  SECONDS = 0,
  MINUTES = 1
};

struct Camera
{
  char device_name[20];
#define CAM_COMPOSITE 1
  int type;
  int dev;
  int greyscale;
  int draw;
  int update_camera;
  int capture;
  int on_timer;
  int timeout;
  int swapcolors;
  int autobright;
  guint timeoutid;

  struct video_channel vid_chan; //pour bttv
  struct video_mbuf vid_buff; //pour bttv
  struct video_mmap *vid_mmap; //pour bttv
  unsigned char **data;//pour bttv
  GdkPixmap *pixmap;
  GtkWidget *drawing_area;
  GtkWidget *window;
  struct video_capability vid_caps; // bttv et usb
  struct video_window vid_win; //bttv et usb
  struct video_picture vid_pic; //bttv et usb

  struct video_clip vid_clips[32]; //usb

  unsigned char *pic;
  unsigned char *picbuff;
  char devname[256];
  char savefile[256];
  char savefileclean[256];

  pthread_mutex_t iscam_mutex, pref_mutex;

  int fps_avg;
  int fps_current;
  struct Timer_Struct timer_struct;
};

unsigned char *grayscale_buff;

/*cam config*/
void open_cam(struct Camera*);
void close_cam(struct Camera*, int force);
void get_cam_info(struct Camera*);
void select_cam(struct Camera *camera);

/*display*/
void display(struct Camera*);

/* utils*/
void ppm_save_util(struct Camera *camera,char *nam,int w,int h);

/*process*/
void swap_rgb24(unsigned char *buff,struct Camera *camera);

#endif /*MVIDEO*/

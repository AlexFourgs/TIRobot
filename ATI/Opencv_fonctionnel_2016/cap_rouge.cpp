#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

int main(int, char **)
{

    int i, j, count;
    Vec3f pixel;

    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened()) // check if we succeeded
        return -1;

    Mat frame;
    namedWindow("MyCam", 1);

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);  //taille de la fenetre
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240); //au dela de 320*240

    MatIterator_<Vec3b> it, end;

    while (1)
    {
        if (cap.read(frame))
        { // get a new frame from camera

            count = 0;
            for (it = frame.begin<Vec3b>(), end = frame.end<Vec3b>(); it != end; ++it)
            {
                //      (*it)[0] = /*accès au B */
                // (*it) [1] =  /* le G */
                // (*it)[2] =  /* le R*/

                if (((float)((*it)[2]) / ((float)((*it)[0] + (*it)[1] + (*it)[2]))) > 0.5)
                {

                    (*it)[0] = 255;
                    (*it)[1] = 0;
                    (*it)[2] = 0;
                }
                //count++;
            }

            //printf("count : %d\n",count);

            imshow("MyCam", frame);
        }
        if (waitKey(30) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

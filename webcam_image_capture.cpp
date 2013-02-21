#include <cstdio>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

int main(int, char**)
{

  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  Mat frame;
 
  int key = -1;
  for(;;)
    {
     
      // get a new frame from camera
     
      for (int i = 0; i < 200; i++) // for loop to take images every 200ms
	{
	  char buf[100];
	  sprintf(buf, "circle1/circleimage%d.jpg", i);

	  key = cvWaitKey(200);
	
	  if (key < 0)
	    {
		
	      cap >> frame;

	      imwrite(buf, frame);

	      imshow("webcam", frame);
	    }
	  else
	    break;
	
	}
    }

  return 0;
}

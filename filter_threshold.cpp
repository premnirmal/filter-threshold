/* PREM NIRMAL
   Fordham RCV Lab
   Fordham University
   Bronx NY 10458
*/
  
/* OpenCV program that filters the webcam image based on
   threshold values, and stores the aggregate image.
   Use with an overhead camera to trace the robots path.
 */

#include <cstdio>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <cmath>

using namespace cv;
using namespace std;

int main(int, char**)
{
  Mat frame;
  double threshvalue=230, maxthresh=255; // min and max threshold values
  IplImage *img, *result, *thresh, *gray;
  CvSize size;
  char buf[100];
  char buf2[100];

  VideoCapture cap(0); // open the default camera, store in cap
  if(!cap.isOpened())  // check if we succeeded
    {
      cerr << "Error: Cannot open image\n";
      return -1;
    }
  int key = -1;
 	   	        
  //capture webcam into frame
  cap >> frame;
  // show webcam frame
  imshow("webcam", frame);

  cout << "Started.. press ESC to quit.\n";

  // store a temporary img location string into buf2
  sprintf(buf2, "test/temp.jpg");
  //capture webcam and store it as temp.jpg
  imwrite(buf2, frame);
  //load temp.jpg into img
  img = cvLoadImage(buf2, 1);
  //create blank image called 'result' based on size of img
  result = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	
  cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
  cvShowImage("result", result);
    
  // for loop to take images until a key is pressed
  while(1)
    {	
      sprintf(buf, "test/testimage.jpg");
      key = cvWaitKey(50); //image taken every 50 miliseconds 
	
      if (key < 0)
	{
	  cap >> frame;
	  imshow("webcam", frame);
	  imwrite(buf, frame);
	  img = cvLoadImage(buf, 1);
	  //create blank images gray and thresh
	  gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	  thresh = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	  cvCvtColor(img, gray, CV_RGB2GRAY); //convert image to grayscale
	  // apply threshold filter
	  cvThreshold(gray, thresh, threshvalue, maxthresh, CV_THRESH_BINARY);
	  cvErode(thresh, thresh, 0, 6); // erode 6 times to reduce noise
	  cvAdd(result, thresh, result, NULL); // result = result + thresh
	  //show result
	  cvShowImage("result", result); // display result
	  cvSaveImage("test/result.jpg", result);// save result
	  remove(buf); // delete the original image	
	}
      else
	{
	  cout<<"Exiting...\n";
	  break;	
	}
    }
  cout<<"Image stored as test/result.jpg\n";

  remove("test/temp.jpg");	
  cout<<"Removed temp.\n";
  
  return 0;
}

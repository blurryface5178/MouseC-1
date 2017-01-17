#include "CameraInterface.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;


CameraInterface::CameraInterface(){

}


CameraInterface::CameraInterface(int id, int frame_width, int frame_height)
{	

	openCamera(id, frame_width, frame_height);


}




CameraInterface::~CameraInterface()
{
	
}



bool CameraInterface::openCamera(int id, int frame_width, int frameHeight)
{
	createTrackBar();
	cap.open(id);
	cap.set(CAP_PROP_FRAME_WIDTH, frame_width);
	cap.set(CAP_PROP_FRAME_HEIGHT, frame_height);
	cap.set(CV_CAP_PROP_FPS, frame_rate);
	while (true)	
	{
		
		cap.read(img);
		flip(img, img, 180);
		BGRtoHSV(img);
		cvtColor(img, img, CV_BGR2BGRA);
		double fps = cap.get(CV_CAP_PROP_FPS);
		putText(img, to_string(fps), cvPoint(30, 30),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		namedWindow("MouseC");
		imshow("MouseC", img);


	if (waitKey(20) == 27) {
			break;
		}
	}

	return false;
}
 


void CameraInterface::BGRtoHSV(Mat img) {
	Mat hsv, threshold;
	cvtColor(img, hsv, CV_BGR2YCrCb);
	inRange(hsv, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
	namedWindow("HSV video");
	namedWindow("Filter video");
	imshow("HSV video", hsv);
	imshow("Filter video", threshold);
}

void CameraInterface::cropCaughtHand(int x, int y, int width, int height)
{
	Rect croppedSize = Rect(x, y, width, height);
	croppedImage = img(croppedImage);
	
}

void CameraInterface::createTrackBar()
{
	namedWindow(trackbarWindowName);

	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, 255);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, 255);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, 255);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, 255);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, 255);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, 255);

}






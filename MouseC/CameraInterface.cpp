#include "CameraInterface.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
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
	createTrackBars();
	cap.open(id);
	cap.set(CAP_PROP_FRAME_WIDTH, frame_width);
	cap.set(CAP_PROP_FRAME_HEIGHT, frame_height);
	cap.set(CV_CAP_PROP_FPS, frame_rate);
	while (true)	
	{
		
		cap.read(img);
		flip(img, img, 180);
		BGRtoHSV(img);
		double fps = cap.get(CV_CAP_PROP_FPS);
		putText(img, to_string(fps), cvPoint(30, 30),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		namedWindow("MouseC");
		//namedWindow("BGR");
		imshow("MouseC", img);


	if (waitKey(20) == 27) {
			break;
		}
	}

	return false;
}
 


void CameraInterface::BGRtoHSV(Mat image) {
	morphologicalDilate(image);

	cvtColor(image, hsv, CV_BGR2HSV);

	inRange(hsv, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
	//morphologicalErode(threshold);
	namedWindow("HSV video");
	namedWindow("Filter video");
	imshow("HSV video", hsv);
	imshow("Filter video", threshold);
}

Mat CameraInterface::ROI(int x, int y, int width, int height)
{
	Rect croppedSize = Rect(x, y, width, height);
	croppedImage = img(croppedImage);
	return croppedImage;
}

void CameraInterface::createTrackBars()
{
	namedWindow(trackbarWindowName);

	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, 255);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, 255);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, 255);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, 255);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, 255);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, 255);
	createTrackbar("ERODE", trackbarWindowName, &ERODEMIN, ERODEMAX);
	createTrackbar("DILATE", trackbarWindowName, &DILATEMIN, DILATEMAX);

}

void CameraInterface::extractPixelColor()
{
	if (H_ROI.size > 0) {
		H_MIN = min_element(H_ROI.begin, H_ROI.end);
		H_MAX = max_element(H_ROI.begin, H_ROI.end);
	}



}

void CameraInterface::storePixelValue(Mat hsv_pixel, int x, int y, int width, int height)
{
	for (int i = 0; i < x + width; i++) {
		for (int j = 0; i < y + height; j++) {

			H_ROI.push_back((int)hsv_pixel.at<Vec3b>(x ,y)[0]); 
			S_ROI.push_back((int)hsv_pixel.at<Vec3b>(x, y)[1]);
			V_ROI.push_back((int)hsv_pixel.at<Vec3b>(x, y)[2]);
			
		}

	}
}

void CameraInterface::morphologicalErode(Mat &thres)
{
	erode(thres, thres, getStructuringElement(MORPH_RECT, Size(ERODEMIN +1, ERODEMIN+1)));
}

void CameraInterface::morphologicalDilate(Mat & thres)
{
	dilate(thres, thres, getStructuringElement(MORPH_RECT, Size(DILATEMIN + 1, DILATEMIN + 1)));
	//GaussianBlur(thres, thres, Size(2*DILATEMIN + 1,2* DILATEMIN + 1),0,0);
}



#include "CameraInterface.h"
#include"HandDetection.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>


using namespace cv;
using namespace std;


CameraInterface::CameraInterface() {

}


CameraInterface::CameraInterface(int id, int frame_width, int frame_height)
{

	//openCamera(id, frame_width, frame_height);
	//createTrackBars();
	cap.open(id);
	cap.set(CAP_PROP_FRAME_WIDTH, frame_width);
	cap.set(CAP_PROP_FRAME_HEIGHT, frame_height);
	cap.set(CV_CAP_PROP_FPS, frame_rate);




}




CameraInterface::~CameraInterface()
{

}



void CameraInterface::openCamera()
{

	cap.read(img);
	flip(img, img, 180);
	//BGRtoHSV(img);
	//hd.Detect(img);
	double fps = cap.get(CV_CAP_PROP_FPS);
	putText(img, to_string(fps), cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	showVideo(img, "MouseC");



}



void CameraInterface::BGRtoHSV(Mat image) {
	

	cvtColor(image, hsv, CV_BGR2HSV);

	inRange(hsv, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
	morphologicalErode(threshold, ERODEMIN);
	morphologicalDilate(image, DILATEMIN);
	showVideo(threshold, "FilterVideo");
}

Mat CameraInterface::ROI(Mat roiSrc, int x, int y, int width, int height)
{
	Rect croppedSize = Rect(x, y, width, height);
	croppedImage = roiSrc(croppedSize);
	return croppedImage;
}

void CameraInterface::createTrackBars()
{
	namedWindow(trackbarWindowName, WINDOW_FREERATIO);

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
	if (H_ROI.size() > 0) {
		H_MIN = *min_element(H_ROI.begin(), H_ROI.end());
		H_MAX = *max_element(H_ROI.begin(), H_ROI.end());
	}

	if (S_ROI.size() > 0) {
		S_MIN = *min_element(S_ROI.begin(), S_ROI.end());
		S_MAX = *max_element(S_ROI.begin(), S_ROI.end());
	}

	if (V_ROI.size() > 0) {
		V_MIN = *min_element(V_ROI.begin(), V_ROI.end());
		V_MAX = *max_element(V_ROI.begin(), V_ROI.end());
	}



}

Mat CameraInterface::getImg()
{
	return img;
}

Mat CameraInterface::getThreshold()
{
	return threshold;
}

void CameraInterface::storePixelValue(Mat hsv_pixel, int x, int y, int width, int height)
{
	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {

			H_ROI.push_back((int)hsv_pixel.at<Vec3b>(y, x)[0]);
			S_ROI.push_back((int)hsv_pixel.at<Vec3b>(y, x)[1]);
			V_ROI.push_back((int)hsv_pixel.at<Vec3b>(y, x)[2]);

		}

	}
}

void CameraInterface::morphologicalErode(Mat &thres, int &E_MIN)
{
	erode(thres, thres, getStructuringElement(MORPH_ELLIPSE, Size(E_MIN + 1, E_MIN + 1)));
}

void CameraInterface::morphologicalDilate(Mat & thres, int &D_MIN)
{
	dilate(thres, thres, getStructuringElement(MORPH_ELLIPSE, Size(D_MIN + 1, D_MIN + 1)));
}

void CameraInterface::createBlur(Mat &src_img, int min_value) {
	GaussianBlur(src_img, src_img, Size(2*min_value + 1,2* min_value + 1),0,0);
}
/*

void CameraInterface::Mouse(int event, int x, int y, int flag, void* in)
{
	//Input
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "LButtonClicked at (" << x << "," << y << ")" << endl;
	}
	if (event == EVENT_RBUTTONDOWN)
	{
		cout << "RButtonClicked at (" << x << "," << y << ")" << endl;
	}
	if (event == EVENT_MBUTTONDOWN)
	{
		cout << "MButtonClicked at (" << x << "," << y << ")" << endl;
	}
}

void CameraInterface::setMouse() {
	setMouseCallback("Click", CameraInterface::Mouse, NULL);
}
*/


void CameraInterface::showVideo(Mat src, String windowName) {

	namedWindow(windowName, WINDOW_FREERATIO);
	imshow(windowName, src);
}
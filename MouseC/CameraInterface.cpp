#include "CameraInterface.h"
#include"HandDetection.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>
#include"CameraImage.h"


using namespace cv;
using namespace std;


CameraInterface::CameraInterface() {

}







CameraInterface::~CameraInterface()
{
	delete cap;

}






void CameraInterface::BGRtoHSV(Mat image) {
	

	cvtColor(image, hsv, CV_BGR2HSV);
		
	inRange(hsv, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
	morphologicalErode(threshold, ERODEMIN);
	morphologicalDilate(threshold, DILATEMIN);
	showVideo(hsv, "HSV image");
	showVideo(threshold, "FilterVideo");
}

Mat CameraInterface::ROI(Mat *roiSrc, int x, int y, int width, int height)
{
	Rect croppedSize = Rect(x, y, width, height);
	croppedImage = (*roiSrc)(croppedSize);
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

void CameraInterface::createBlur(Mat &src_src, int min_value) {
	GaussianBlur(src_src, src_src, Size(2*min_value + 1,2* min_value + 1),0,0);
}



void CameraInterface::showVideo(Mat src, String windowName) {

	namedWindow(windowName, WINDOW_FREERATIO);
	imshow(windowName, src);
}

void CameraInterface::palmPixExt(CameraImage *m) 
{
	roi.push_back(My_ROI(Point(m->src.cols / 3, m->src.rows / 6), Point(m->src.cols / 3 + square_len, m->src.rows / 6 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 4, m->src.rows / 2), Point(m->src.cols / 4 + square_len, m->src.rows / 2 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 3, m->src.rows / 1.5), Point(m->src.cols / 3 + square_len, m->src.rows / 1.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2, m->src.rows / 2), Point(m->src.cols / 2 + square_len, m->src.rows / 2 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2.5, m->src.rows / 2.5), Point(m->src.cols / 2.5 + square_len, m->src.rows / 2.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2, m->src.rows / 1.5), Point(m->src.cols / 2 + square_len, m->src.rows / 1.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols / 2.5, m->src.rows / 1.8), Point(m->src.cols / 2.5 + square_len, m->src.rows / 1.8 + square_len), m->src));


	for (;;) {
		for (int j = 0; j<NSAMPLES; j++) {
			roi[j].draw_rectangle(m->src);
		}
		string imgText = string("Cover rectangles with palm and press enter");
		printText(m->src, imgText);
		showVideo(m->src, "getvalue");
		if (waitKey(30) == char('f')) break;
	}



}

void CameraInterface::printText(Mat src, string text) {
	int fontFace = FONT_HERSHEY_PLAIN;
	putText(src, text, Point(src.cols / 2, src.rows / 10), fontFace, 1.2f, Scalar(200, 0, 0), 2);
}


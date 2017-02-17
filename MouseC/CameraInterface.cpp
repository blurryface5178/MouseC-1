#include "CameraInterface.h"
#include"HandDetection.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
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






void CameraInterface::BGRtoHSV(CameraImage *m) {
	for (int i = 0; i < NSAMPLES; i++)
	{
		inRange(m->srcLR, Scalar(HMIN[i], SMIN[i], VMIN[i]), Scalar(HMAX[i], SMAX[i], VMAX[i]), threshold);
		channels.push_back(threshold);
		//cout << HMIN[i]<<"," << SMIN[i]<<"," << VMIN[i]<<","<< HMAX[i]<<","<< SMAX[i]<<","<< VMAX[i];
	}
	
  mergeData(channels, m);
}



void CameraInterface::mergeData(vector<Mat> thres, CameraImage *m) {
	m->bw = thres[0];


	for (int i = 1; i < NSAMPLES; i++)
	{
		m->bw += thres[i];
	}

	
	for (int i = 0; i < 3; i++) {
		m->bwList.push_back(m->bw);
	}


	merge(m->bwList, result);
	
	m->bwList.clear();

}

Mat CameraInterface::getMergedData() {
	return result;
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
		HMIN.push_back(*min_element(H_ROI.begin(), H_ROI.end()));
		HMAX.push_back(*max_element(H_ROI.begin(), H_ROI.end()));
	}

	if (S_ROI.size() > 0) {
		SMIN.push_back(*min_element(S_ROI.begin(), S_ROI.end()));
		SMAX.push_back(*max_element(S_ROI.begin(), S_ROI.end()));
	}

	if (V_ROI.size() > 0) {
		VMIN.push_back(*min_element(V_ROI.begin(), V_ROI.end()));
		VMAX.push_back(*max_element(V_ROI.begin(), V_ROI.end()));
	}



}




void CameraInterface::storePixelValue(CameraImage *m, My_ROI roi, int avg[3])
{
	/*
	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {

			H_ROI.push_back((int)hsv_pixel.at<Vec3b>(y, x)[0]);
			S_ROI.push_back((int)hsv_pixel.at<Vec3b>(y, x)[1]);
			V_ROI.push_back((int)hsv_pixel.at<Vec3b>(y, x)[2]);

		}

	}
	*/


	Mat r;
	roi.roi_ptr.copyTo(r);
	vector<int>hm;
	vector<int>sm;
	vector<int>vm;
	// generate vectors
	for (int i = 2; i<r.rows - 2; i++) {
		for (int j = 2; j<r.cols - 2; j++) {
			H_ROI.push_back(r.data[r.channels()*(r.cols*i + j) + 0]);
			S_ROI.push_back(r.data[r.channels()*(r.cols*i + j) + 1]);
			V_ROI.push_back(r.data[r.channels()*(r.cols*i + j) + 2]);
		}
	}

	extractPixelColor();

	avg[0] = getMedian(H_ROI);
	avg[1] = getMedian(S_ROI);
	avg[2] = getMedian(V_ROI);
	
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


	for (int i = 0; i<30; i++) {
		m->cap->read(m->src);
		flip(m->src, m->src, 1);
		for (int j = 0; j<NSAMPLES; j++) {
			roi[j].draw_rectangle(m->src);
		}
		string imgText = string("Cover rectangles with palm and press F");
		printText(m->src, imgText);
		showVideo(m->src, "getvalue");
		if (waitKey(30) == char('f')) break;
	}

	destroyWindow("getvalue");



}

void CameraInterface::printText(Mat src, string text) {
	int fontFace = FONT_HERSHEY_PLAIN;
	putText(src, text, Point(src.cols / 2, src.rows / 10), fontFace, 1.2f, Scalar(200, 0, 0), 2);
}

void CameraInterface::average(CameraImage *m) {
	for (int i = 0; i<15; i++) {
		m->cap->read(m->src);
		flip(m->src, m->src, 1);
		cvtColor(m->src, m->src, CV_BGR2HSV);
		for (int j = 0; j<NSAMPLES; j++) {
			//Rect* rectangleROI = &roi[j].draw_rectangle(m->src);
			//getAvgColor(m, roi[j], avgColor[j], rectangleROI);
			roi[j].draw_rectangle(m->src);
			storePixelValue(m, roi[j], avgColor[j]);
		}

	

		cvtColor(m->src, m->src, CV_HSV2BGR);
		string imgText = string("Finding average color of hand");
		printText(m->src, imgText);
		showVideo(m->src, "img1");
		if (cv::waitKey(30) == char("z")) break;
	}

	destroyWindow("img1");
}
/*/
void CameraInterface::getAvgColor(CameraImage *m, My_ROI roi, int avg[3], Rect* rectangleROI) {
	storePixelValue(m->src, rectangleROI->x, rectangleROI->y, rectangleROI->width, rectangleROI->height);
	extractPixelColor();
	avg[0] = getMedian(H_ROI);
	avg[1] = getMedian(S_ROI);
	avg[2] = getMedian(V_ROI);
}

*/

int CameraInterface::getMedian(vector<int> val) {
	int median;
	size_t size = val.size();
	sort(val.begin(), val.end());
	if (size % 2 == 0) {
		median = val[size / 2 - 1];
	}
	else {
		median = val[size / 2];
	}
	return median;
}





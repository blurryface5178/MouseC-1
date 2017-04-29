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




void CameraInterface::normalizeColors(CameraImage * myImage){
	// copy all boundries read from trackbar
	// to all of the different boundries
	for(int i=1;i<NSAMPLES;i++){
		for(int j=0;j<3;j++){
			c_lower[i][j]=c_lower[0][j];	
			c_upper[i][j]=c_upper[0][j];	
		}	
	}
	// normalize all boundries so that 
	// threshold is whithin 0-255
	for(int i=0;i<NSAMPLES;i++){
		if((avgColor[i][0]-c_lower[i][0]) <0){
			c_lower[i][0] = avgColor[i][0] ;
		}if((avgColor[i][1]-c_lower[i][1]) <0){
			c_lower[i][1] = avgColor[i][1] ;
		}if((avgColor[i][2]-c_lower[i][2]) <0){
			c_lower[i][2] = avgColor[i][2] ;
		}if((avgColor[i][0]+c_upper[i][0]) >255){ 
			c_upper[i][0] = 255-avgColor[i][0] ;
		}if((avgColor[i][1]+c_upper[i][1]) >255){
			c_upper[i][1] = 255-avgColor[i][1] ;
		}if((avgColor[i][2]+c_upper[i][2]) >255){
			c_upper[i][2] = 255-avgColor[i][2] ;
		}
	}
}

void CameraInterface::BGRtoHSL(CameraImage *m) {
	
	Scalar hlslowerBound, hsvlowerBound;
	Scalar hlsupperBound, hsvupperBound;
	Mat foo;
	for (int i = 0; i<NSAMPLES; i++) {
		normalizeColors(m);
		hlslowerBound = Scalar(avgColor[i][0] - c_lower[i][0], avgColor[i][1] - c_lower[i][1], avgColor[i][2] - c_lower[i][2]);
		hlsupperBound = Scalar(avgColor[i][0] + c_upper[i][0], avgColor[i][1] + c_upper[i][1], avgColor[i][2] + c_upper[i][2]);
		//hsvlowerBound = Scalar(HMIN[i],SMIN[i], VMIN[i]);
		//hsvupperBound = Scalar(HMAX[i],SMAX[i], VMAX[i]);
		inRange(m->srcLR, hlslowerBound, hlsupperBound, threshold);
		//inRange(m->srcLR, hsvlowerBound, hsvupperBound, thresholds[1]);
		//threshold = thresholds[0] + thresholds[1];
		channels.push_back(threshold);
	}
	
	
  mergeData(channels, m);
}

void CameraInterface::initWindows() {
	namedWindow("trackbars", CV_WINDOW_KEEPRATIO);

}



void CameraInterface::mergeData(vector<Mat> thres, CameraImage *m) {
	m->bw = thres[0];


	for (int i = 1; i < NSAMPLES; i++)
	{
		m->bw += thres[i];
	}

	medianBlur(m->bw, m->bw, 7);
	
	for (int i = 0; i < 3; i++) {
		m->bwList.push_back(m->bw);
	}


	//merge(m->bwList, result);
	result = m->bw;
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



void CameraInterface::extractPixelColor()
{
	if (h_roi.size() > 0) {
		HMIN.push_back(*min_element(h_roi.begin(), h_roi.end()));
		HMAX.push_back(*max_element(h_roi.begin(), h_roi.end()));
	}

	if (s_roi.size() > 0) {
		SMIN.push_back(*min_element(s_roi.begin(), s_roi.end()));
		SMAX.push_back(*max_element(s_roi.begin(), s_roi.end()));
	}

	if (v_roi.size() > 0) {
		VMIN.push_back(*min_element(v_roi.begin(), v_roi.end()));
		VMAX.push_back(*max_element(v_roi.begin(), v_roi.end()));
	}



}





void CameraInterface::storePixelValue(CameraImage *m, My_ROI roi, int avg[3])
{


	Mat r;
	roi.roi_ptr.copyTo(r);


	


	// generate vectors
	for (int i = 2; i<r.rows - 2; i++) {
		for (int j = 2; j<r.cols - 2; j++) {
			H_ROI.push_back(r.data[r.channels()*(r.cols*i + j) + 0]);
			S_ROI.push_back(r.data[r.channels()*(r.cols*i + j) + 1]);
			L_ROI.push_back(r.data[r.channels()*(r.cols*i + j) + 2]);
		}
	}

	//extractPixelColor();

	avg[0] = getMedian(H_ROI);
	avg[1] = getMedian(S_ROI);
	avg[2] = getMedian(L_ROI);
	
}



void CameraInterface::morphologicalErode(Mat &thres, int &E_MIN)
{
	erode(thres, thres, getStructuringElement(MORPH_ELLIPSE, Size(E_MIN + 1, E_MIN + 1)));
}

void CameraInterface::morphologicalDilate(Mat & thres, int D_MIN)
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


	for (int i = 0; i<40; i++) {
		m->cap->read(m->src);
		flip(m->src, m->src, 1);
		for (int j = 0; j<NSAMPLES; j++) {
			roi[j].draw_rectangle(m->src);
		}
		string imgText = string("Cover rectangles with palm and press F");
		printText(m->src, imgText);
		showVideo(m->src, "getvalue");
		if (waitKey(30) == 'f') break;
	}




}

void CameraInterface::initTrackbars() {
	for (int i = 0; i<NSAMPLES; i++) {
		c_lower[i][0] = 12;
		c_upper[i][0] = 7;
		c_lower[i][1] = 30;
		c_upper[i][1] = 40;
		c_lower[i][2] = 80;
		c_upper[i][2] =  80;
	}
	createTrackbar("lower1", "trackbars", &c_lower[0][0], 255);
	createTrackbar("lower2", "trackbars", &c_lower[0][1], 255);
	createTrackbar("lower3", "trackbars", &c_lower[0][2], 255);
	createTrackbar("upper1", "trackbars", &c_upper[0][0], 255);
	createTrackbar("upper2", "trackbars", &c_upper[0][1], 255);
	createTrackbar("upper3", "trackbars", &c_upper[0][2], 255);
}


void CameraInterface::printText(Mat src, string text) {
	int fontFace = FONT_HERSHEY_PLAIN;
	putText(src, text, Point(src.cols / 2, src.rows / 10), fontFace, 1.2f, Scalar(200, 0, 0), 2);
}

void CameraInterface::average(CameraImage *m) {
	for (;;) {
		m->cap->read(m->src);
		flip(m->src, m->src, 1);
		cvtColor(m->src, m->src, CV_BGR2HLS);
		for (int j = 0; j<NSAMPLES; j++) {
			//Rect* rectangleROI = &roi[j].draw_rectangle(m->src);
			//getAvgColor(m, roi[j], avgColor[j], rectangleROI);
			roi[j].draw_rectangle(m->src);
			storePixelValue(m, roi[j], avgColor[j]);
		}

	
		cvtColor(m->src, m->src, CV_HLS2BGR);
		string imgText = string("Finding average color of hand");
		printText(m->src, imgText);
		showVideo(m->src, "getvalue");
		if (waitKey(30) == 'z') break; 
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





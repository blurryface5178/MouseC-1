#pragma once
#include "CameraInterface.h"
#include"HandDetection.h"
#include"My_ROI.h"
#include"CameraImage.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>

#include<iostream>

#define NSAMPLES 7

using namespace cv;
using namespace std;

extern Mat img;

class CameraInterface
{
private:
	int id;
	Mat src;
	int frame_width = 360;
	int frame_height = 480;
	int frame_rate = 5;
	int H_MIN = 0;
	int S_MIN = 0;
	int L_MIN = 0;
	int H_MAX = 256;
	int S_MAX = 256;
	int L_MAX = 256;
	int ERODEMAX = 21;
	int ERODEMIN = 0;
	int DILATEMIN = 0;
	int DILATEMAX = 21;
	int INTERESTNUM = 7;
	vector<int> HMIN; 
	vector<int> SMIN;
	vector<int> VMIN;
	vector<int> HMAX;
	vector<int> SMAX;
	vector<int> VMAX;

	vector<int> H_ROI;
	vector<int> S_ROI;
	vector<int> L_ROI;

	vector<int> h_roi, s_roi, v_roi;
	
	const String trackbarWindowName = "Trackbar";
	const int square_len = 20;
	int avgColor[NSAMPLES][3];
	VideoCapture *cap = new VideoCapture;

	Mat hsv, threshold;
	Mat thresholds[2];
	vector<Mat> channels;
	Mat croppedImage;
	vector<My_ROI> roi;
	Mat result;
	int c_lower[NSAMPLES][3];
	int c_upper[NSAMPLES][3];




public:
	CameraInterface();
	~CameraInterface();

	Mat ROI(Mat*, int, int, int, int);
	void createTrackBars();
	void extractPixelColor();
	void morphologicalErode(Mat &thres, int &);
	void morphologicalDilate(Mat &thres, int);
	void storePixelValue(CameraImage *m, My_ROI roi, int avg[3]);
	void showVideo(Mat, String);
	void createBlur(Mat&, int);
	void printText(Mat, string);
	void palmPixExt(CameraImage *);
	Mat getMergedData();
	void average(CameraImage*);
	void BGRtoHSL(CameraImage*);
	void initTrackbars();
	void initWindows();


private:
	int getMedian(vector<int>);
	void mergeData(vector<Mat>, CameraImage *);
	void normalizeColors(CameraImage * myImage);

};



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
	int V_MIN = 0;
	int H_MAX = 256;
	int S_MAX = 256;
	int V_MAX = 256;
	int ERODEMAX = 21;
	int ERODEMIN = 0;
	int DILATEMIN = 0;
	int DILATEMAX = 21;
	int INTERESTNUM = 7;

	vector<int> H_ROI;
	vector<int> S_ROI;
	vector<int> V_ROI;
	
	const String trackbarWindowName = "Trackbar";
	const int square_len = 20;
	const int NSAMPLES = 7;
	VideoCapture *cap = new VideoCapture;

	Mat hsv, threshold;
	Mat croppedImage;
	vector<My_ROI> roi;





public:
	CameraInterface();
	~CameraInterface();

	Mat ROI(Mat*, int, int, int, int);
	Mat getThreshold();
	void createTrackBars();
	void extractPixelColor();
	void morphologicalErode(Mat &thres, int &);
	void morphologicalDilate(Mat &thres, int &);
	void storePixelValue(Mat, int x, int y, int width, int height);
	void showVideo(Mat, String);
	void createBlur(Mat&, int);
	void printText(Mat, string);
	void palmPixExt(CameraImage *);


private:
	void BGRtoHSV(Mat image);
	


};



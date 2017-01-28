#pragma once
#include "CameraInterface.h"
#include"HandDetection.h"

#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>

#include<iostream>

using namespace cv;
using namespace std;



class CameraInterface
{
private:
	int id;
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
	vector<int> H_ROI;
	vector<int> S_ROI;
	vector<int> V_ROI;
	const String trackbarWindowName = "Trackbar";
	VideoCapture cap;
	HandDetection hd;

	Mat img, hsv, threshold, croppedImage;





public:
	CameraInterface();
	CameraInterface(int id, int frame_width, int frame_height);
	void createTrackBars();
	void extractPixelColor();
	Mat ROI(Mat , int , int , int , int);
	void morphologicalErode(Mat &thres, int &);
	void morphologicalDilate(Mat &thres, int &);
	Mat getImg();
	Mat getThreshold();
	void storePixelValue(Mat, int x, int y, int width, int height);
	void openCamera();
	void showVideo(Mat, String);
	void createBlur(Mat&, int);
	~CameraInterface();

private:
	void BGRtoHSV(Mat image);
	

	///static void Mouse(int event, int x, int y, int flag, void * in);
	///void setMouse();

};



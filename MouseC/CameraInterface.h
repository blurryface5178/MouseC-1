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
	int frame_rate = 24;
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

	Mat img,hsv,threshold, croppedImage;
	




public:
	CameraInterface();
	CameraInterface(int id, int frame_width, int frame_height);
	void createTrackBars();
	void extractPixelColor();
	void storePixelValue(Mat, int x, int y, int width, int height);
	~CameraInterface();

private:
	bool openCamera(int id, int frame_width, int frame_height);
	void BGRtoHSV(Mat image);
	Mat ROI(int x, int y, int width, int height);
	void morphologicalErode(Mat &thres);
	void morphologicalDilate(Mat &thres);


};



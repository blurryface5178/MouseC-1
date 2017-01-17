#pragma once
#include "CameraInterface.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;



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
	const String trackbarWindowName = "Trackbar";
	VideoCapture cap;

	Mat img,hsv,threshold, croppedImage;
	




public:
	CameraInterface();
	CameraInterface(int id, int frame_width, int frame_height);
	~CameraInterface();

private:
	bool openCamera(int id, int frame_width, int frame_height);
	void BGRtoHSV(Mat img);
	void cropCaughtHand(int x, int y, int width, int height);
	void createTrackBar();


};



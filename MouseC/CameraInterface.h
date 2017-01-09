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
	int frame_rate = 5;
	VideoCapture stream;
	Mat img;
	

public:
	CameraInterface();
	CameraInterface(int id, int frame_width, int frame_height);
	~CameraInterface();

private:
	bool openCamera(int id, int frame_width, int frame_height);


};



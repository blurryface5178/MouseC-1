#pragma once
#include "HandDetection.h"
#include "CameraInterface.h"

#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>

using namespace cv;

class HandDetection
{
public:
	String file_name = "palm.xml";
	HandDetection();
	HandDetection(Mat img);
	~HandDetection();
	Mat gray;
	void Detect(Mat src);
};


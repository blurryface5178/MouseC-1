#pragma once
#include"CameraInterface.h"
#include"ColorCodecConversion.h"
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>


using namespace cv;
using namespace std;


class ColorCodecConversion
{
private:
	VideoCapture *capture;
	Mat hsv;
	Mat threshold;


public:
	ColorCodecConversion();

	void bgrToHSB(Mat bgr);
	~ColorCodecConversion();


};



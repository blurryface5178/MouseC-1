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
	CameraInterface *cI;
	VideoCapture *capture;
	Mat bgr, hsv;
	Mat threshold;


public:
	ColorCodecConversion();
	ColorCodecConversion(CameraInterface *cI);
	void bgrToHSB();
	~ColorCodecConversion();


};



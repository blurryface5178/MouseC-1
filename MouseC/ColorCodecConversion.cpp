#include"ColorCodecConversion.h"
#include"CameraInterface.h"
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;
	
ColorCodecConversion::ColorCodecConversion()
{



}



void ColorCodecConversion::bgrToHSB(Mat bgr)
{


	cvtColor(bgr, hsv, CV_BGR2HSV);
	inRange(hsv, Scalar(0, 0,0), Scalar(0, 0,0), threshold);
	namedWindow("HSV video");
	namedWindow("Filter video");
	imshow("HSV video", hsv);
	imshow("Filter video", threshold);

}


ColorCodecConversion::~ColorCodecConversion()
{
}


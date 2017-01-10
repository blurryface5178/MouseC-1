#include "ColorCodecConversion.h"
#include"CameraInterface.h"
#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;

ColorCodecConversion::ColorCodecConversion()
{



}

ColorCodecConversion::ColorCodecConversion(CameraInterface *cI)
{

	this->cI = cI;
	capture = (this->cI)->getVideoCapture();
	

}

void ColorCodecConversion::bgrToHSB()
{
	while (true)
	{
		capture->read(bgr);
		
		cvtColor(bgr, hsv, CV_BGR2HSV);
		inRange(hsv, Scalar(0, 255), Scalar(0, 255), threshold);
		namedWindow("HSV video");
		namedWindow("Filter video");
		imshow("HSV video", hsv);
		imshow("Filter video", threshold);
		if (waitKey(30) == 27)
		{
			break;
		}
	}
}


ColorCodecConversion::~ColorCodecConversion()
{
}


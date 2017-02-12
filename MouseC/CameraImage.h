#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;
class CameraImage
{


public:
	Mat src;
	CameraImage();
	CameraImage(int,int,int,int);
	~CameraImage();

};


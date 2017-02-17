#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>

using namespace cv;
using namespace std;
class CameraImage
{
public:
	CameraImage();
	CameraImage(int,int,int,int);
	Mat src;
	Mat srcLR;
	Mat bw;
	vector<Mat> bwList;
	VideoCapture *cap = new VideoCapture();

	~CameraImage();

};


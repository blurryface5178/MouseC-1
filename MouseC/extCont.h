#pragma once
#include"CameraInterface.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>

using namespace std;
using namespace cv;
class extCont
{
private:
	Mat extSrc;
	Mat gray_scale;
	Mat gray_threshold;
	Mat extROI;
	int B_MIN = 0; 
	int B_MAX =20;
	int T_MIN = 0;
	int T_MAX = 255;
	int E_MIN = 0;
	int E_MAX = 20;
	int D_MIN = 0;
	int D_MAX = 20;
	char a[40];
	int count = 0;
	CameraInterface cI;
	vector<vector<Point> >contours;
	vector<Vec4i>hierarchy;

public:
	extCont();
	void beginExt(Mat);
	void showVideo();
	String getText();
	~extCont();

private:
	void createTrack();
	void findingContours();
};


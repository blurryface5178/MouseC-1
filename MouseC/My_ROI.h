#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>


using namespace std;
using namespace cv;
class My_ROI
{
public:
	My_ROI();
	My_ROI(Point, Point, Mat);
	Point upper_corner, lower_corner;
	Mat roi_ptr;
	Scalar color;
	int border_thickness;
	void draw_rectangle(Mat);
	~My_ROI();
};


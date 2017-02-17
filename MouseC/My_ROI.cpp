#include "My_ROI.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>


using namespace std;
using namespace cv;

My_ROI::My_ROI() {
	upper_corner = Point(0, 0);
	lower_corner = Point(0, 0);

}

My_ROI::My_ROI(Point u_corner, Point l_corner, Mat src) {
	upper_corner = u_corner;
	lower_corner = l_corner;
	color = Scalar(0, 255, 0);
	border_thickness = 2;
	roi_ptr = (src)(Rect(u_corner.x, u_corner.y, l_corner.x - u_corner.x, l_corner.y - u_corner.y));
}

void My_ROI::draw_rectangle(Mat src) {

	rectangle(src, upper_corner, lower_corner, color, border_thickness);
	//return Rect(upper_corner.x, upper_corner.y, lower_corner.x - upper_corner.x, lower_corner.y - upper_corner.y);
}


My_ROI::~My_ROI()
{
}

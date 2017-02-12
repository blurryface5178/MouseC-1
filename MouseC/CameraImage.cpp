#include "CameraImage.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;



CameraImage::CameraImage()
{
}
CameraImage::CameraImage(int videoCameraid, int frame_width, int frame_height,int frame_rate)
{
	VideoCapture *cap = new VideoCapture();
	cap->open(videoCameraid);
	cap->set(CAP_PROP_FRAME_WIDTH, frame_width);
	cap->set(CAP_PROP_FRAME_HEIGHT, frame_height);
	cap->set(CV_CAP_PROP_FPS, frame_rate);
	cap->read(src);
	flip(src, src, 180);

}


CameraImage::~CameraImage()
{
}

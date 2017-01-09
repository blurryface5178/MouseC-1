#include "CameraInterface.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;


CameraInterface cf;
CameraInterface::CameraInterface(){

}


CameraInterface::CameraInterface(int id, int frame_width, int frame_height)
{
	
	cf.openCamera(id, frame_width, frame_height);


}


CameraInterface::~CameraInterface()
{
	
}

bool CameraInterface::openCamera(int id, int frame_width, int frameHeight)
{
	stream.open(id);
	stream.set(CAP_PROP_FRAME_WIDTH, frame_width);
	stream.set(CAP_PROP_FRAME_HEIGHT, frame_height);
	stream.set(CV_CAP_PROP_FPS, frame_rate);
	while (true)
	{
		stream.read(img);
		flip(img, img, 180);
		cvtColor(img, img, CV_BGR2BGRA);
		double fps = stream.get(CV_CAP_PROP_FPS);
		putText(img, to_string(fps), cvPoint(30, 30),FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
		namedWindow("MouseC");
		imshow("MouseC", img);
		if (waitKey(20) == 27) {
			break;
		}


	}

	return false;
}



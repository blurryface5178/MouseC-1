#include"CameraInterface.h"
#include"extCont.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include"CameraImage.h"


using namespace cv;
using namespace std;


void dispose();


int main()
{
	CameraImage *cImg = new CameraImage(0, 500, 500, 20);
	CameraInterface *cI = new CameraInterface();
	cI->palmPixExt(cImg);
	

	dispose();
	return 0;
}

void dispose() {

}



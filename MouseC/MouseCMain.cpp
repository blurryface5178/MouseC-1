#include"CameraInterface.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>

#include<iostream>


using namespace cv;
using namespace std;

void dispose(CameraInterface*);

int main()
{
	CameraInterface cI(0, 480, 360);



	return 0;
}



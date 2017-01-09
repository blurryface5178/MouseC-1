#include "CameraInterface.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

int main() 
{
	CameraInterface *cI = new CameraInterface(0, 480, 360);
	
}
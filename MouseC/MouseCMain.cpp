#include "CameraInterface.h"
#include"ColorCodecConversion.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

void dispose(CameraInterface*);

int main() 
{
	CameraInterface *cI = new CameraInterface(0, 480, 360);
	ColorCodecConversion *ccConversion = new ColorCodecConversion(cI);
	ccConversion->bgrToHSB();

	dispose(cI);
}


void dispose(CameraInterface *cI) {

	delete cI;
}
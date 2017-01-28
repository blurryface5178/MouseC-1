#include"CameraInterface.h"
#include"extCont.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>


using namespace cv;
using namespace std;

void dispose(CameraInterface*);

void Mouse(int event, int x, int y, int flag, void* in)
{
	//Input
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "LButtonClicked at (" << x << "," << y << ")" << endl;
	}
	if (event == EVENT_RBUTTONDOWN)
	{
		cout << "RButtonClicked at (" << x << "," << y << ")" << endl;
	}
	if (event == EVENT_MBUTTONDOWN)
	{
		cout << "MButtonClicked at (" << x << "," << y << ")" << endl;
	}
}


int main()
{
	CameraInterface cI(0, 500, 500);
	extCont eC;
	while (true)
	{
		cI.openCamera();
		//namedWindow("Click");
		//setMouseCallback("Click", Mouse, NULL);
		//imshow("Click", cI.getImg());
		//thresh_callback(cI.getThreshold());
		
		eC.beginExt(cI.getImg());
		
		if (waitKey(20) == 27) {
			break;
		}

	}


	return 0;
}



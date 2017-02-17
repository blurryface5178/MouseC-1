#include"CameraInterface.h"
#include"extCont.h"
#include"CameraImage.h"

#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>


using namespace cv;
using namespace std;


void dispose();


int main()
{
	CameraImage *cImg = new CameraImage(0, 500, 500, 20);
	CameraInterface *cI = new CameraInterface();
	cI->palmPixExt(cImg);
	cI->average(cImg);
	while (true) {
		cImg->cap->read(cImg->src);
		flip(cImg->src, cImg->src, 1);
		pyrDown(cImg->src, cImg->srcLR);
		blur(cImg->srcLR, cImg->srcLR, Size(3, 3));
		cvtColor(cImg->srcLR, cImg->srcLR, CV_BGR2HSV);
		cI->BGRtoHSV(cImg);
		Mat result = cI->getMergedData();
		cI->showVideo(result, "result");

		if (waitKey(30) == 27) break;


	}

	dispose();
	return 0;
}

void dispose() {

}



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
		cI->createBlur(cImg->srcLR, 4);
		blur(cImg->srcLR, cImg->srcLR, Size(3, 3));
		cvtColor(cImg->srcLR, cImg->srcLR, CV_BGR2HLS);
		cI->BGRtoHSV(cImg);
		Mat result1 = cI->getMergedData();
		cvtColor(cImg->srcLR, cImg->srcLR, CV_HLS2BGR);
		cvtColor(cImg->srcLR, cImg->srcLR, CV_BGR2HSV);
		cI->BGRtoHSV(cImg);
		Mat result2 = cI->getMergedData();
		Mat result = result1 + result2;
		cI->showVideo(result, "result");
		cI->morphologicalDilate(result, 3);
		if (waitKey(30) == 27) break;


	}

	dispose();
	return 0;
}

void dispose() {

}



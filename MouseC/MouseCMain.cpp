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
CameraImage *cImg = new CameraImage(0);
CameraInterface *cI = new CameraInterface();

extCont *extcont = new extCont();

int main(char** argv)
{
	
	cout << "place your palm in the rectangles" << endl;
	cI->palmPixExt(cImg);
	cI->average(cImg);
	destroyWindow("getvalue");
	cout << "taking out the average value from the pixel" << endl;
	cI->initWindows();
	cI->initTrackbars();
	while (true) {
		cImg->cap->read(cImg->src);
		flip(cImg->src, cImg->src, 1);
		pyrDown(cImg->src, cImg->srcLR);
		blur(cImg->srcLR, cImg->srcLR, Size(3, 3));
		cvtColor(cImg->srcLR, cImg->srcLR, CV_BGR2HLS);
		cI->BGRtoHSL(cImg);
		Mat result1 = cI->getMergedData();

        //cI->morphologicalDilate(result1, 4);
		cI->showVideo(result1, "result");
		extcont->findingContours(result1, cImg->src);
		if (waitKey(30) == 27) break;


	}

	dispose();
	return 0;
}

void dispose() {
	delete cImg, cI, extcont;
}



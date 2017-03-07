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
CameraImage *cImg = new CameraImage(0, 500, 500, 20);
CameraInterface *cI = new CameraInterface();
CameraImage *cImg1 = new CameraImage(0, 500, 500, 20);
CameraInterface *cI1 = new CameraInterface();
extCont *extcont = new extCont();

int main()
{
	cout << "place your palm in the rectangles" << endl;
	cI->palmPixExt(cImg);
	cI->average(cImg);
	cout << "place your palm in different position the rectangle" << endl;
	cI1->palmPixExt(cImg1);
	cI1->average(cImg1);
	cout << "taking out the average value from the pixel" << endl;
	while (true) {
		cImg->cap->read(cImg->src);
		flip(cImg->src, cImg->src, 1);
		pyrDown(cImg->src, cImg->srcLR);
		cI->createBlur(cImg->srcLR, 4);
		blur(cImg->srcLR, cImg->srcLR, Size(3, 3));
		cvtColor(cImg->srcLR, cImg->srcLR, CV_BGR2HLS);
		cI->BGRtoHSV(cImg);
		Mat result1 = cI->getMergedData();
		//cvtColor(cImg->srcLR, cImg->srcLR, CV_HLS2BGR);
		//cvtColor(cImg->srcLR, cImg->srcLR, CV_BGR2HSV);
		//cI->BGRtoHSV(cImg);
		//Mat result2 = cI->getMergedData();

		cImg1->cap->read(cImg1->src);
		flip(cImg1->src, cImg1->src, 1);
		
		pyrDown(cImg1->src, cImg1->srcLR);

		blur(cImg1->srcLR, cImg1->srcLR, Size(3, 3));
		cvtColor(cImg1->srcLR, cImg1->srcLR, CV_BGR2HLS);
		cI1->BGRtoHSV(cImg1);
		Mat result1_2 = cI1->getMergedData();
		//cvtColor(cImg1->srcLR, cImg1->srcLR, CV_HLS2BGR);
		//cvtColor(cImg1->srcLR, cImg1->srcLR, CV_BGR2HSV);
		//cI1->BGRtoHSV(cImg1);
		//Mat result2_2 = cI1->getMergedData();




		Mat result = result1 + result1_2 ;
		cI->morphologicalDilate(result, 4);
		cI->showVideo(result, "result");
		//extcont->beginExt(cImg->srcLR, result, cI);
		extcont->findingContours(result, cImg->src);
		if (waitKey(30) == 27) break;


	}

	dispose();
	return 0;
}

void dispose() {
	delete cImg, cI, extcont;
}



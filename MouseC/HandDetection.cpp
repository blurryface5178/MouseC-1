#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include<iostream>
#include <stdio.h>
#include "CameraInterface.h"

#include "HandDetection.h"

using namespace cv;
using namespace std;

FileNode cascadeNames;

HandDetection::HandDetection(Mat img)
{
	/*Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);*/
}

HandDetection::HandDetection()
{

}

HandDetection::~HandDetection()
{

}

void HandDetection::Detect(Mat src)
{
	Mat gray;
	CascadeClassifier file;
	vector<Rect> faces;
	file.load(file_name);
	cvtColor(src, gray, CV_BGR2GRAY);
	//	if(!file.read(cascadeNames)) printf("Error loading classifier");
	file.detectMultiScale(gray, faces, 1.1, 3, 0 | CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(src, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 255, 255), 4, 8, 0);

		Mat faceROI = gray(faces[i]);

		//-- In each face, detect eyes
		
	}
	namedWindow("Recog");
	imshow("Recog", gray);

}

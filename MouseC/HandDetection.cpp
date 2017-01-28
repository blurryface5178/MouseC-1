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
	CascadeClassifier palms;
	CascadeClassifier fists;
	vector<Rect> gesture1;
	vector<Rect> gesture2;
	palms.load(palmxml);
	fists.load(fistxml);
	//vector<Rect> faces;
	//file.load(file_name);
	//cvtColor(src, gray, CV_BGR2GRAY);
	//	if(!file.read(cascadeNames)) printf("Error loading classifier");
	/*file.detectMultiScale(gray, faces, 1.1, 3, 0 | CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(src, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 255, 255), 4, 8, 0);

		Mat faceROI = gray(faces[i]);

		//-- In each face, detect eyes
		
	}
	namedWindow("Recog");
	imshow("Recog", gray);
	*/

	cvtColor(src, gray, CV_BGR2GRAY);
	palms.detectMultiScale(gray, gesture1, 2.1, 1, 0 | CV_HAAR_FIND_BIGGEST_OBJECT, Size(35, 35));
	fists.detectMultiScale(gray, gesture2, 1.2, 1, 0 | CV_HAAR_FIND_BIGGEST_OBJECT, Size(35, 35));
	for (size_t i = 0; i < gesture1.size() || i< gesture2.size(); i++)
	{
	if (gesture1.size() > i)
	{
	Point center(gesture1[i].x + gesture1[i].width / 2, gesture1[i].y + gesture1[i].height / 2);
	ellipse(gray, center, Size(gesture1[i].width / 2, gesture1[i].height / 2), 0, 0, 360, Scalar(255, 255, 255), 4, 8, 0);
	Mat gesture1ROI = gray(gesture1[i]);
	namedWindow("ROI1");
	imshow("ROI1", gesture1ROI);
	putText(gray, "Scissors", cvPoint(50, 50), FONT_HERSHEY_PLAIN, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	}
	else if (gesture2.size() > i)
	{
	Point center(gesture2[i].x + gesture2[i].width / 2, gesture2[i].y + gesture2[i].height / 2);
	ellipse(gray, center, Size(gesture2[i].width / 2, gesture2[i].height / 2), 0, 0, 360, Scalar(255, 255, 255), 4, 8, 0);
	Mat gesture2ROI = gray(gesture2[i]);
	namedWindow("ROI2");
	imshow("ROI2", gesture2ROI);
	putText(gray, "Paper", cvPoint(50, 50), FONT_HERSHEY_PLAIN, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	}
	else
	{
	putText(gray, "Rock", cvPoint(50, 50), FONT_HERSHEY_PLAIN, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	}
	}
	if (gesture1.size()>0) putText(gray, "Scissors", cvPoint(30, 50), FONT_HERSHEY_PLAIN, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	else if (gesture2.size()>0) putText(gray, "Paper", cvPoint(30, 50), FONT_HERSHEY_PLAIN, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	else putText(gray, "Rock", cvPoint(30, 50), FONT_HERSHEY_PLAIN, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	namedWindow("Recog");
	imshow("Recog", gray);


}

#include"extCont.h"
#include"CameraInterface.h"
#include"CameraImage.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>

using namespace std;
using namespace cv;


extCont::extCont()
{	
	//createTrack();
	B_MIN = 9;

}

void extCont::beginExt(Mat src,Mat thresholdvalue, CameraInterface *cI)
{
	this->cI = cI;
	extSrc = src;
	//extROI = cI->ROI(&extSrc, 260, 10, 250, 250);
	//cvtColor(extROI, gray_scale, CV_RGB2GRAY);
	//cI->createBlur(gray_scale, B_MIN);
	//threshold(gray_scale, gray_threshold, T_MIN, T_MAX, THRESH_BINARY_INV + THRESH_OTSU);
	//gray_threshold = thresholdvalue;
	//cI->morphologicalErode(gray_threshold, E_MIN);
	//cI->morphologicalDilate(gray_threshold, D_MIN);
	//findingContours();
}

void extCont::showVideo()
{
	cI->showVideo(extSrc, "ORIGINAL");
	//cI->showVideo(extROI, "Region of Interest");
	//cI->showVideo(gray_scale, "gray");
	cI->showVideo(gray_threshold, "threshold");
}

String extCont::getText()
{
	return a;
}


extCont::~extCont()
{
}



void extCont::createTrack()
{
	namedWindow("trackbar");
	createTrackbar("blur", "trackbar", &B_MIN, B_MAX);
	createTrackbar("threshold", "trackbar", &T_MIN, T_MAX);
	createTrackbar("ERODE", "trackbar", &E_MIN, E_MAX);
	createTrackbar("DILATE", "trackbar", &D_MIN, D_MAX);
}

void extCont::findingContours(Mat gray_threshold, Mat src)
{
	flip(src, src, 1);
	this->extSrc = src;
	this->gray_threshold = gray_threshold;
	findContours(gray_threshold, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());
	if (contours.size() > 0) {
		size_t indexOfBiggestContour = -1;
		size_t sizeOfBiggestContour = 0;

		for (size_t i = 0; i < contours.size(); i++) {
			if (contours[i].size() > sizeOfBiggestContour) {
				sizeOfBiggestContour = contours[i].size();
				indexOfBiggestContour = i;
			}
		}
		vector<vector<int> >hull(contours.size());//needed for convexHull
		vector<vector<Point> >hullPoint(contours.size());
		vector<vector<Vec4i> >defects(contours.size());
		vector<vector<Point> >defectPoint(contours.size());
		vector<vector<Point> >contours_poly(contours.size());
		Point2f rect_point[4];
		vector<RotatedRect>minRect(contours.size());
		vector<Rect> boundRect(contours.size());
		for (size_t i = 0; i < contours.size(); i++) {
			if (contourArea(contours[i]) > 5000) {
				convexHull(contours[i], hull[i], true);
				convexityDefects(contours[i], hull[i], defects[i]);
				if (indexOfBiggestContour == i) {
					minRect[i] = minAreaRect(contours[i]);
					for (size_t k = 0; k < hull[i].size(); k++) {
						int ind = hull[i][k];
						hullPoint[i].push_back(contours[i][ind]);
					}
					count = 0;

					for (size_t k = 0; k < defects[i].size(); k++) {
						if (defects[i][k][3] > 13 * 256) {
							//int p_start=defects[i][k][0];   
							int p_end = defects[i][k][1];
							int p_far = defects[i][k][2];
							defectPoint[i].push_back(contours[i][p_far]);
							circle(extSrc, contours[i][p_end], 3, Scalar(0, 255, 0), 2);
							count++;
						}

					}


					if (count == 1 || count == 2 || count == 3)
						strcpy(a, "Scissor");
					else if (count == 4 || count == 5)
						strcpy(a, "Paper ");
					else
						strcpy(a, "Rock BaBy");

					putText(extSrc, a, Point(70, 70), CV_FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 0, 0), 2, 8, false);
					drawContours(gray_threshold, contours, i, Scalar(255, 255, 0), 2, 8, vector<Vec4i>(), 0, Point());
					drawContours(gray_threshold, hullPoint, i, Scalar(255, 255, 0), 1, 8, vector<Vec4i>(), 0, Point());
					//drawContours(extSrc, hullPoint, i, Scalar(0, 0, 255), 2, 8, vector<Vec4i>(), 0, Point());
					approxPolyDP(contours[i], contours_poly[i], 3, false);
					boundRect[i] = boundingRect(contours_poly[i]);
					//rectangle(extSrc, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 0), 2, 8, 0);
					minRect[i].points(rect_point);
					for (size_t k = 0; k < 4; k++) {
						line(extSrc, rect_point[k], rect_point[(k + 1) % 4], Scalar(0, 255, 0), 2, 8);
					}

				}
			}

		}
		showVideo();
	
	}
	
	

}

void extCont::dispose()
{
	if (cI != nullptr) {
		delete cI;
	}
}

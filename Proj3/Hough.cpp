/*
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2\legacy\legacy.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc,char* argv[])
{
	
	if(argc != 7)
	{
		printf("usage: %s [rho] [theta divisor] [threshold] [srn] [stn] [target]",argv[0]);

		return 0;
	}
	Mat input = imread(argv[6],0);
	
	double rho = atof(argv[1]);
	double theta = CV_PI / atof(argv[2]);
	int thresh = atoi(argv[3]);
	int srn = atoi(argv[4]);
	int stn = atoi(argv[5]);
	
	vector<Vec2f> lines;

	HoughLines(input,lines,rho,theta,thresh,srn,stn);
	

	//"print" lines to result image
	Mat result;
	cvtColor(input,result,CV_GRAY2RGB);
	int i;
	//Point a,b; //will hold start and end points of line segments
	double dx,dy;
	double xcen,ycen; //center point of line segment
	double scale = 1000; //scale factor for drawing lines
	
	vector<Vec2d> lineSlopeInt;

	for(i=0; i<lines.size(); i++)
	{
		rho = lines[i][0];
		theta = lines[i][1];

		dx = cos(theta);
		dy = sin(theta);
		xcen = rho*dx; //r*theta = (x,y)
		ycen = rho*dy;
		Point a,b;
		a.x = cvRound(xcen - scale*-dy);
		a.y = cvRound(ycen - scale*dx);
		b.x = cvRound(xcen + scale*-dy);
		b.y = cvRound(ycen + scale*dx);

		line(result,a,b,Scalar(0,0,255),1, CV_AA);

		//calc slope and y_int of line and save to vector
		if(a.x!=b.x) //line is non-vertical
		{
			double slope = (b.y - a.y)/(b.x - a.x);
			double y_int = b.y - slope*b.x;
			double slope_abs = abs(slope);
			if(slope_abs > 0.1) //filter out horizontal lines
			{
				if(slope_abs < 30.0) //filter out almost vertical lines
				{
					lineSlopeInt.push_back(Vec2d(slope,y_int));
				}
			}
		}
	}

	namedWindow("w1",1);
	imshow("w1",result);

	waitKey(0);
	
	//write result image to new file with h_ prefix on original filename
	string output_name(argv[6]);
	output_name.insert(0,"h_");
	const char* out_name = output_name.c_str();
	printf("\n%s",out_name);
	imwrite(out_name,result);

	vector<Vec2i> intersects;

	for(int i=0; i<lineSlopeInt.size()-1; i++)//
	{
		//select the line to be tested against all other lines
		Vec2d line_a = lineSlopeInt[i];

		for(int j=i+1; j<lineSlopeInt.size(); j++)//first test against non-vertical lines
		{
			Vec2d line_b = lineSlopeInt[j];

			//getIntercept(line_a,line_b,intersects);
			if(line_a[0]!=line_b[0])
			{
				double x = (line_b[1] - line_a[1])/(line_a[0] - line_b[0]);
				double y = line_a[0]*x + line_a[1];

				//if (x,y) is within boundaries of the image, add to intersects list
				intersects.push_back(Vec2i((int)x,(int)y));

				circle(result,Point((int)x,(int)y),10,Scalar(255,0,255),1,8,0);
			}
		}
	}

	namedWindow("vpoints",1);
	imshow("vpoints",result);
	waitKey(0);

	//Find potential vanishing point of all lines
	int thresh_dist = 20;

	vector<int> vanishScore; //keeps track of how many other intersections are within threshold distance of the i'th intersection

	for(int i=0;i<intersects.size();i++)
	{
		vanishScore.push_back(0);
	}

	for(int i=0;i<intersects.size()-1;i++)
	{
		Vec2i isx_a = intersects[i]; //set potential vanishing point

		for(int j=i+1; j<intersects.size(); j++)
		{
			Vec2i isx_b = intersects[j];
			//calc distance between the two intersections
			int distance = (int)sqrt(double(pow(isx_a[0] - isx_b[0],2) + pow(isx_a[1] - isx_b[1],2)));
			if(distance<thresh_dist) //if the intersections are near, they are likely the same vanishing point
			{
				vanishScore[i]++;
				vanishScore[j]++;
			}
		}
	}
	int best_guess = 0; //stores index intersection w/ highest vanishScore
	for(int i=0;i<vanishScore.size();i++)
	{
		if(vanishScore[i] > vanishScore[best_guess])
		{
			best_guess = i;
		}
	}

	circle(result,Point(intersects[best_guess][0],intersects[best_guess][1]),15,Scalar(0,255,0),2,8,0);
	circle(result,Point(intersects[best_guess][0],intersects[best_guess][1]),3,Scalar(0,255,0),-1,8,0);
	namedWindow("vanishingpoint",1);
	imshow("vanishingpoint",result);

	//write result image to new file with h_ prefix on original filename
	string output_name_v(argv[6]);
	output_name_v.insert(0,"ints_h_");
	const char* out_name_v = output_name_v.c_str();
	printf("\n%s",out_name_v);
	imwrite(out_name_v,result);

	waitKey(0);

	return 0;
}
*/
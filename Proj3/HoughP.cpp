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
	
	if(argc != 5)
	{
		printf("usage: %s [rho] [theta divisor] [threshold] [target]",argv[0]);

		return 0;
	}
	printf("\na");
	Mat input = imread(argv[4],0);
	
	printf("\nb");
	waitKey(0);
		
	double rho = atof(argv[1]);
	double theta = CV_PI / atof(argv[2]);
	int thresh = atoi(argv[3]);

	printf("\nc");
	waitKey(0);

	printf("\n");

	vector<Vec4i> lines;
	HoughLinesP(input,lines,rho,theta,thresh,50,10);
	waitKey(0);

	//"print" lines to result image
	Mat result;
	cvtColor(input,result,CV_GRAY2RGB);

	vector<Vec2i> lineSlopeInt; //store slope and intercept of non-vertical lines
	vector<int> xIntercepts; //store x-intercept of vertical lines

	printf("lines.size() = %d",lines.size());
	for( int i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);

		//calc slope and y-intercept of line
		printf("\nx2 = %d\tx1 = %d",l[2],l[0]);
		if(l[0]!=l[2])//if line isn't vertical, i.e. x's are different, store slope and intercept
		{
			int slope = (l[3] - l[1])/(l[2]-l[0]);
			int y_int = (l[1] - slope*l[0]);
			
			//store slope and intercept of line in another vector for intersect finding
			lineSlopeInt.push_back(Vec2i(slope,y_int));
		} else//line is vertical so store just x-intercept
		{
			xIntercepts.push_back(l[0]);
		}
    }
	printf("\n\nreached it yeah");
	namedWindow("w1",1);
	imshow("w1",result);
	waitKey(0);
	
	//write result image to new file with h_ prefix on original filename
	string output_name(argv[4]);
	output_name.insert(0,"hP_");
	const char* out_name = output_name.c_str();
	printf("\n%s",out_name);
	imwrite(out_name,result);

	vector<Vec2i> intersects;

	for(int i=0; i<lineSlopeInt.size()-1; i++)//
	{
		//select the line to be tested against all other lines
		Vec2i line_a = lineSlopeInt[i];

		for(int j=i+1; j<lineSlopeInt.size(); j++)//first test against non-vertical lines
		{
			Vec2i line_b = lineSlopeInt[j];

			//getIntercept(line_a,line_b,intersects);
			if(line_a[0]!=line_b[0])
			{
				double x = (line_b[1] - line_a[1])/(line_a[0] - line_b[0]);
				double y = line_a[0]*x + line_a[1];

				//if (x,y) is within boundaries of the image, add to intersects list
				intersects.push_back(Vec2i((int)x,(int)y));

				circle(result,Point((int)x,(int)y),25,Scalar(255,0,255),1,8,0);
			}
		}

		for(int j=0; j<xIntercepts.size(); j++)
		{
			//
			double x = xIntercepts[j];
			double y = line_a[0]*x + line_a[1];
			intersects.push_back(Vec2i((int)x,(int)y));

			circle(result,Point((int)x,(int)y),25,Scalar(255,0,255),1,8,0);
		}
	}

	namedWindow("vpoints",1);
	imshow("vpoints",result);
	waitKey(0);
	
	//write result image to new file with h_ prefix on original filename
	string output_name_v(argv[4]);
	output_name_v.insert(0,"ints_hP_");
	const char* out_name_v = output_name_v.c_str();
	printf("\n%s",out_name_v);
	imwrite(out_name_v,result);

	return 0;
}
*/
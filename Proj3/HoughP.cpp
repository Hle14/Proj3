
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
	
	Mat input = imread(argv[4],0);
	
	double rho = atof(argv[1]);
	double theta = CV_PI / atof(argv[2]);
	int thresh = atoi(argv[3]);

	vector<Vec4i> lines;
	HoughLinesP(input,lines,rho,theta,thresh,50,10);
	

	//"print" lines to result image
	Mat result;
	cvtColor(input,result,CV_GRAY2RGB);

	vector<Vec2d> lineSlopeInt; //store slope and intercept of non-vertical lines

	for( int i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);

		//calc slope and y-intercept of line
		if(l[0]!=l[2])//if line isn't vertical, i.e. x's are different, store slope and intercept
		{
			double slope = (double(l[3]) - double(l[1]))/(double(l[2])-double(l[0]));
			double y_int = (l[1] - slope*l[0]);
			
			//store slope and intercept of line in another vector for intersect finding
			if(abs(slope) > 0.1) //slope magnitude must be greater than 0.1 to be considered non-horizontal
			{
				if(abs(slope) < 30.0)
				{
					lineSlopeInt.push_back(Vec2d(slope,y_int));
				}
			}
		}
    }

	namedWindow("w1",1);
	imshow("w1",result);


	//write result image to new file with h_ prefix on original filename
	string output_name(argv[4]);
	output_name.insert(0,"hP_");
	const char* out_name = output_name.c_str();
	printf("\n%s",out_name);
	imwrite(out_name,result);

	waitKey(0);

	vector<Vec2i> intersects; //intersections of lines

	for(int i=0; i<lineSlopeInt.size()-1; i++)
	{
		//select the line to be tested against all other lines
		Vec2d line_a = lineSlopeInt[i];

		for(int j=i+1; j<lineSlopeInt.size(); j++)//intersection line_a with non-vertical lines
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
	int thresh_dist = 10;

	vector<int> vanishScore; //keeps track of how many other intersections are within threshold distance of the i'th intersection

	for(int i=0;i<intersects.size();i++) //initialize scores of each intersection to 0
	{
		vanishScore.push_back(0);
	}

	//create "vanish point scores" which determine likelihood of being the actual vanishing point
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
	//draw the vanishing point on the image
	circle(result,Point(intersects[best_guess][0],intersects[best_guess][1]),15,Scalar(0,255,0),2,8,0);
	circle(result,Point(intersects[best_guess][0],intersects[best_guess][1]),3,Scalar(0,255,0),-1,8,0);
	namedWindow("vanishingpoint",1);
	imshow("vanishingpoint",result);

	//write result image to new file with ints_hP_ prefix on original filename
	string output_name_v(argv[4]);
	output_name_v.insert(0,"ints_hP_");
	const char* out_name_v = output_name_v.c_str();
	printf("\n%s",out_name_v);
	imwrite(out_name_v,result);

	waitKey(0);

	return 0;
}

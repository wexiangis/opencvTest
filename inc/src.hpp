#ifndef __SRC_H_
#define __SRC_H_

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat colorReduce(Mat& input, vector<uchar> &wideOfBit) //wideOfBit[3] RGB 三色分别使用几位色? 默认 color&oxFF
{
	Mat output = input.clone();
	vector<uchar> wide;
	if(wideOfBit.size() < 3)
	{
		int i = 0;
		for(; i < wideOfBit.size(); i++)
			wide.push_back(wideOfBit[i]);
		for(; i < 3; i++)
			wide.push_back(0xFF);
	}
	else
		wide = wideOfBit;

	cout<<"row/"<<output.rows<<" col/"<<output.cols<<" chn/"<<output.channels()<<endl;

	//type 1
	// int rowSize = output.rows;
	// int colSize = output.cols*output.channels();
	// for(int rowC = 0; rowC < rowSize; rowC++)
	// {
	// 	uchar *data = output.ptr<uchar>(rowC);///////////
	// 	for(int colC = 0; colC < colSize;)
	// 	{
	// 		data[colC++] = data[colC]&wide.at(2);
	// 		if(colC < colSize) data[colC++] = data[colC]&wide.at(1);
	// 		if(colC < colSize) data[colC++] = data[colC]&wide.at(0);
	// 	}
	// }

	//type 2
	int rowSize = output.rows;
	int colSize = output.cols;
	for(int rowC = 0; rowC < rowSize; rowC++)
	{
		for(int colC = 0; colC < colSize; colC++)
		{
			output.at<Vec3b>(rowC, colC)[0] = input.at<Vec3b>(rowC, colC)[0]&wide.at(2);
			output.at<Vec3b>(rowC, colC)[1] = input.at<Vec3b>(rowC, colC)[1]&wide.at(1);
			output.at<Vec3b>(rowC, colC)[2] = input.at<Vec3b>(rowC, colC)[2]&wide.at(0);
		}
	}

	return output;
}

#endif

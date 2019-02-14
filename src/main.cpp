
#include <opencv2/opencv.hpp>

#include "res.h"

using namespace cv; 

int main(int argc, char **argv)
{
	Mat img = imread(TJPG1);
	imshow("t1", img);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dstImage;
	erode(img, dstImage, element);
	imshow("t2", dstImage);
	
	waitKey(0);
}


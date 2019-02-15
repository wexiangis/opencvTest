
#include <opencv2/opencv.hpp>

#include "res.h"

using namespace cv; 

int main(int argc, char **argv)
{
	Mat srcImage = imread(TJPG1);
	imshow("t1", srcImage);

	//--- 腐蚀 ---
	/*Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	imshow("t2", dstImage);*/

	//--- blur模糊 ---
	/*Mat dstImage2; 
	blur(srcImage, dstImage2, Size(7, 7)); 
	imshow("t3", dstImage2);*/

	//--- 边缘检测 ---
	Mat dstImage3, edge, grayImage;	//参数定义
	//创建与src同类型和大小的矩阵(dst)
	dstImage3.create(srcImage.size(), srcImage.type());
	//将原图像转换为灰度图像
	//此句代码的OpenCV2版为：
	//cvtColor( srcImage, grayImage, CV_BGR2GRAY);
	//此句代码的OpenCV3版为：
	cvtColor( srcImage, grayImage, COLOR_BGR2GRAY);
	//先用使用 3x3内核来降噪
	blur( grayImage, edge, Size(3,3));
	//运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	//
	imshow("t4", edge);

	waitKey(0);
}


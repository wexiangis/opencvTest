
#include <iostream>
#include <opencv2/opencv.hpp>

#include "res.h"

using namespace std; 
using namespace cv; 

int main(int argc, char **argv)
{
	/*
	Mat srcImage = imread(TJPG1);
	imshow("t1", srcImage);*/

	/*
	//--- 腐蚀 ---
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	imshow("t2", dstImage);*/

	/*
	//--- blur模糊 ---
	Mat dstImage2; 
	blur(srcImage, dstImage2, Size(7, 7)); 
	imshow("t3", dstImage2);*/

	/*
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
	imshow("t4", edge);*/
  
	//从摄像头读入视频
	//sudo modprobe bcm2835-v4l2
	//echo "bcm2835-v4l2" >> /etc/modules
	VideoCapture capture(0);
	if(!capture.isOpened())
	{
		cout<<"camera open failure"<<endl;
		return -1;
	}
	//循环显示每一帧
	while(1)
	{
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
		capture>>frame;//读取当前帧
		imshow("读取视频",frame);//显示当前帧
		waitKey(50);//延时30ms
	}

	waitKey(0);
}


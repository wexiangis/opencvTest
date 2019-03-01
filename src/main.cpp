

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
// #include "opencv2/core/operations.hpp"//format()
using namespace cv;
using namespace std;

#define MY_TEST 3

#if(MY_TEST == 3) // setMouseCallback() MouseCallback()

void my_mouseCallback(int event, int x, int y, int flags, Mat* srcImg)
{
	printf("event = %d, flags = %d [%d, %d]\n", event, flags, x, y);

	if(event == 0)
	{
		srcImg->at<Vec3b>(y, x)[0] = 0;//B
		srcImg->at<Vec3b>(y, x)[1] = 0;//G
		// srcImg->at<Vec3b>(x, y)[2] = 0;//R
	}

	imshow("t1", *srcImg);
}

int main(int argc, char **argv)
{
	Mat srcImg = imread("./res/t1.jpg", CV_LOAD_IMAGE_UNCHANGED);

	imshow("t1", srcImg);

	setMouseCallback("t1", (MouseCallback)(&my_mouseCallback), &srcImg);

	int ms[3] = {3, 2, 1};
	Mat mat(3, ms, CV_8UC1, Scalar::all(1));//长2 宽2 高1

	int ms2[2] = {3, 2};
	Mat mat2(2, ms2, CV_8UC3, Scalar(1,2,3));
	cout<<"mat2 ="<<endl<<mat2<<endl; //仅在2维时可用

	Mat mat011_7 = (Mat_<double>(3,2) << 0, 1, 2, 3, 4, 5);
	cout<<"mat011_7 = "<<endl<<mat011_7<<endl;

	Mat mat011_8 = mat011_7.row(1).clone();
	cout<<"mat011_8 = "<<endl<<mat011_8<<endl;

	Mat mat011_4 = Mat::eye(3, 3, CV_8U);//返回3rows,2cols的 单位矩阵
	cout<<"mat011_4 = "<<endl<<mat011_4<<endl;

	Mat mat011_5 = Mat::ones(3, 2, CV_8U);//返回3rows,2cols的 全是1的矩阵
	cout<<"mat011_5 = "<<endl<<mat011_5<<endl;

	Mat mat011_6 = Mat::zeros(3, 2, CV_8U);//返回3rows,2cols的 全是0的矩阵
	cout<<"mat011_6 = "<<endl<<mat011_6<<endl;

	Mat mat012_1(3, 2, CV_8UC3, Scalar(1, 2, 3));
	cout<<"mat012_1 = "<<endl<<mat012_1<<endl;
	cout<<"mat012_1 = "<<endl<<format(mat012_1, 3)<<endl;

	Point2i mp2i(1, 2);
	cout<<"mp2i = "<<mp2i<<endl;

	Point3f mp3f(1.1, 2.2, 3.3);
	cout<<"mp3f = "<<mp3f<<endl;

	vector<int> vet013(2, 255);
	vet013.push_back(1);
	vet013.push_back(2);
	vet013.push_back(3);
	cout<<"vet013 = "<<Mat(vet013)<<endl;

	vector<Point3i> vet013_2(3);
	vet013_2[0] = Point3i(1, 2, 3);
	vet013_2[1] = Point3i(4, 5, 6);
	vet013_2[2] = Point3i(7, 8, 9);
	cout<<"vet013_2 = "<<format(Mat(vet013_2), 3)<<endl;

	waitKey(0);

	return 0;
}

#elif(MY_TEST == 2) // namedWindow() createTrackbar() Range()

#define WIN_NAME 	  "test"
#define TRACKBAR_NAME "tBar"

static Mat srcImg, distImg;

void my_trackbar_callback(int count, void *argv)
{
	if(count > 0)
		// distImg = srcImg(Range(0, srcImg.rows/count), Range(0, srcImg.cols));
		distImg = srcImg(Rect(0, 0, srcImg.cols, srcImg.rows/count));

	imshow(WIN_NAME, distImg);
}

int main(int argc, char **argv)
{
	srcImg = imread("./res/t2.jpg");

	distImg = srcImg(Range(0, srcImg.rows), Range(0, srcImg.cols));

	namedWindow(WIN_NAME);

	int value = 0;
	createTrackbar(TRACKBAR_NAME, WIN_NAME, &value, 10, my_trackbar_callback);

	imshow(WIN_NAME, distImg);

	waitKey(0);

	return 0;
}

#elif(MY_TEST == 1) // vector() imwrite() addWeighted()

void creatAlphaMat(Mat& mat)
{
	for(int i = 0; i < mat.rows; i++)
	{
		for(int j = 0; j < mat.cols; j++)
		{
			Vec4b& rgba = mat.at<Vec4b>(i, j);
			rgba[0] = 255;
			rgba[1] = saturate_cast<uchar>( (float (mat.cols - j)) / (float (mat.cols)) *255 );
			rgba[2] = saturate_cast<uchar>( (float (mat.rows - i)) / (float (mat.rows)) *255 );
			rgba[3] = saturate_cast<uchar>( 05 * (rgba[1] + rgba[2]) );
		}
	}
}

int main( int argc, char** argv )
{
	Mat mat(240, 240, CV_8UC4);
	creatAlphaMat(mat);

	Mat srcImg = imread("./res/t1.jpg");
	Mat src2Img = imread("./res/t2.jpg");

	Mat pice1 = srcImg(Range(50, 50+100), Range(50, 50+100));//从t1中截取一块
	Mat pice2 = src2Img(Range(50, 50+100), Range(50, 50+100));//~

	vector<int>compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try{
		imwrite("./res/imwrite_alpha.png", mat, compression_params);
		imshow("test", mat);

		addWeighted(pice1, 0.5, pice2, 0.5, 0.0, pice2);//把pice1叠到pice2上,并输出到pice2所在的t2原图上

		imshow("t1", srcImg);
		imshow("t2", src2Img);

		waitKey(0);
	}
	catch(runtime_error &ex)
	{
		fprintf(stderr, "异常错误");
		return 1;
	}

	return 0;
}

#elif(MY_TEST == 0) // test

int main( int argc, char** argv )
{
	// 【1】载入原始图，且必须以二值图模式载入
	Mat srcImage=imread("res/t2.jpg", 0);
	imshow("原始图",srcImage);

	//【2】初始化结果图
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//【3】srcImage取大于阈值119的那部分
	srcImage = srcImage > 119;
	imshow( "取阈值后的原始图", srcImage );

	//【4】定义轮廓和层次结构
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//【5】查找轮廓
	//此句代码的OpenCV2版为：
	//findContours( srcImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//此句代码的OpenCV3版为：
	findContours( srcImage, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE );

	// 【6】遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		Scalar color( rand()&255, rand()&255, rand()&255 );
		//此句代码的OpenCV2版为：
		//drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
		//此句代码的OpenCV3版为：
		drawContours( dstImage, contours, index, color, FILLED, 8, hierarchy );
	}

	//【7】显示最后的轮廓图
	imshow( "轮廓图", dstImage );

	imwrite("./res/imwrite_test.jpg", dstImage);

	waitKey(0);

}

#endif

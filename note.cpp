
#include <iostream>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

//===== 001 图像载入 =====

// Mat imread(const string& filename, int flags = 1);

//--- flag ---
enum{
    //8bit, color or not
    CV_LOAD_IMAGE_UNCHANGED = -1,
    //8bit, gray 灰度图
    CV_LOAD_IMAGE_GRAYSCALE = 0,
    //?, color 已废弃
    CV_LOAD_IMAGE_COLOR = 1,
    //any depth
    CV_LOAD_IMAGE_ANYDEPTH = 2,
    //?, any color
    CV_LOAD_IMAGE_ANYCOLOR = 4,
    
    //无损载使用 CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR

    //flags > 0 返回3通道彩色图像
    //falgs = 0 返回灰度图像
    //flags < 0 返回含Alpha通道的图像
};

//===== 002 图像显示 =====

void imshow(const string& winName, InputArray mat);

//CV_WINDOW_AUTOSIZE 控制显示原始大小

//不管8,16,32位还是32位浮点都要转换为8位无符[0,255]的像素再输出
//32位浮点[0,1]将乘以255

//===== 003 窗口命名 =====

void namedWindow(const string& winName, int flags = WINDOW_AUTOSIZE);

//===== 004 输出图像到文件 =====

bool imwrite(const string& fileName, InputArray img, const vector<int>& param=vector<int>());

//fileName 输出文件名,需自带后缀.jpg
//img 使用Mat类型

//vector(); 创建一个空向量
//vector(int nSize); 创建一个元素个数为nSize的向量
//vector(int nSize, const t& t); 创建一个元素个数为nSize的向量,且元素都为t
//vector(const vector&); 复制构造函数
//vector(begin, end); 赋值区间数值到另一个vector

//v.push_back(const T& x); 往尾部添加元素
//...

//jpeg: 0~100 默认95 CV_IMWRITE_JPEG_CHROMA_QUALITY 图片质量
//png: 0~9 默认3 CV_IMWRITE_PNG_COMPRESSION 压缩时间
//ppm,pgm,pbm: 0/1 CV_IMWRITE_PXM_BINARY 

//===== 005 图片叠加 =====

void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype = -1);

//src1, src1的透明度, src2, src2的透明度, 灰度系数(默认0), 输出至dst

//===== 006 c++中的 &(引用) 的使用 =====

void f(int& i)
{
    i = i + 1;
}

//1. 意为传参i后,函数可以直接 调用 和 修改 原变量的值
//2. 传入为结构体,访问结构体内的参数时用 i.xxx, 而不是 i->xxx

//===== 007 滑动条 =====

int createTrackbar(const string& trackbarName, const string& winName, int* value, int count, TrackbarCallback onChange = 0, void* usrdata = 0);

//*value 传递一个整形变量,用来设置滑块当前位置
//count 设置滑动条最大值,最小值为0
//onChange 滑块变动时回调 函数原型 void XXX(int, void*) 前者为滑块位置,后者为用户数据(即传入的 usrdata)
//usrdata 用户数据

int getTrackbarPos(const string& trackbarName, const string& winName); //读取滑动条位置

//===== 008 裁剪和拷贝图片 ====

Mat A008(240, 320, CV_8UC3, Scalar(255, 0, 0));   //Mat(int rows, int cols, int type, Scalar(初始值));
// 1
Mat B008(A008, Rect(0, 0, A008.rows, A008.cols));  // Rect(x, y, width, height)
// 2
Mat C008 = A008(Rect(0, 0, A008.rows, A008.cols)); //范围界定
// 3
Mat D008 = A008(Range(0, A008.rows), Range(0, A008.cols)); //范围界定
// 4
Mat E008 = A008.clone(); //完全复制 !!
// 5
Mat F008(A008); //拷贝构造函数
// 6
Mat G008 = A008;
// 7
Mat H008;
A008.copyTo(H008); //完全复制 !!


//===== 009 convertTo =====

// Mat srcImg009(240, 320, CV_32FC3, Scalar(0, 0, 0));
// Mat srcImg009 = imread("./res/t2.jpg");
// srcImg009.convertTo(srcImg009, CV_8UC3, 0.5, 0);

//===== 010 鼠标 =====

void setMouseCallback(const string& winName, MouseCallback onMouse, void* useData = 0);

// void onMouse(int event, int x, int y, int flags, void* userdata);
// x,y base on map
// event = MouseEventTypes :
enum MouseEventTypes {
       EVENT_MOUSEMOVE      = 0, //!< indicates that the mouse pointer has moved over the window.
       EVENT_LBUTTONDOWN    = 1, //!< indicates that the left mouse button is pressed.
       EVENT_RBUTTONDOWN    = 2, //!< indicates that the right mouse button is pressed.
       EVENT_MBUTTONDOWN    = 3, //!< indicates that the middle mouse button is pressed.
       EVENT_LBUTTONUP      = 4, //!< indicates that left mouse button is released.
       EVENT_RBUTTONUP      = 5, //!< indicates that right mouse button is released.
       EVENT_MBUTTONUP      = 6, //!< indicates that middle mouse button is released.
       EVENT_LBUTTONDBLCLK  = 7, //!< indicates that left mouse button is double clicked.
       EVENT_RBUTTONDBLCLK  = 8, //!< indicates that right mouse button is double clicked.
       EVENT_MBUTTONDBLCLK  = 9, //!< indicates that middle mouse button is double clicked.
       EVENT_MOUSEWHEEL     = 10,//!< positive and negative values mean forward and backward scrolling, respectively.
       EVENT_MOUSEHWHEEL    = 11 //!< positive and negative values mean right and left scrolling, respectively.
     };
// flags = MouseEventFlags :
enum MouseEventFlags {
       EVENT_FLAG_LBUTTON   = 1, //!< indicates that the left mouse button is down.
       EVENT_FLAG_RBUTTON   = 2, //!< indicates that the right mouse button is down.
       EVENT_FLAG_MBUTTON   = 4, //!< indicates that the middle mouse button is down.
       EVENT_FLAG_CTRLKEY   = 8, //!< indicates that CTRL Key is pressed.
       EVENT_FLAG_SHIFTKEY  = 16,//!< indicates that SHIFT Key is pressed.
       EVENT_FLAG_ALTKEY    = 32 //!< indicates that ALT Key is pressed.
     };

//===== 011 矩阵创建 =====

//-- 1 -- 构造函数初始化
Mat mat011(2, 2, CV_8UC3, Scalar(0, 0, 255));
//CV_8UC3 : CV_[位数][有/无符:S/U][类型前缀]C[通道数]

//-- 2 --
int ms011[3] = {3, 2, 1};
Mat mat011_2(3, ms011, CV_8UC1, Scalar::all(255));//3x2x1矩阵

//-- 3 -- 构造函数 + 数组
Mat mat011_3;
mat011_3.create(3, 2, 1, CV_8UC(1));//3x2x1矩阵 CV_8UC(1)同CV_8UC1
//没法设置初始值...

//-- 4 -- matlab 
Mat mat011_4 = Mat::eye(3, 2, CV_8U);//返回3rows,2cols的 单位矩阵
Mat mat011_5 = Mat::ones(3, 2, CV_8U);//返回3rows,2cols的 全是1的矩阵
Mat mat011_6 = Mat::zeros(3, 2, CV_8U);//返回3rows,2cols的 全是0的矩阵

//-- 5 -- 
Mat mat011_7 = (Mat_<double>(3,2) << 0, 1, 2, 3, 4, 5);//按顺序3行2列
//[ 0, 1;
//  2, 3;
//  4, 5]

//-- 6 --
Mat mat011_8 = mat011_7.row(1).clone();//得到 [2, 3]

//===== 012 矩阵格式化输出 =====

//-- randu() 随机值填充 --
Mat mat012_1(3, 2, CV_8UC3, Scalar(1, 2, 3));
cout<<"mat012_1 = "<<endl<<mat012_1<<endl;
cout<<"mat012_1 = "<<endl<<format(mat012_1, 0)<<endl;// 0/1/2/3/4/5/6...

//===== 013 Point[几维][数据类型] =====

Point2i mp2i013(1, 2);

Point3f mp3f013(1.1, 2.2, 3.3);

vector<int> vet013(2, 255);//先在前面填2个255
vet013.push_back(1);
vet013.push_back(2);
vet013.push_back(3);
cout<<"vet013 = "<<Mat(vet013)<<endl;//5x1矩阵

vector<Point3i> vet013_2(3);
vet013_2[0] = Point3i(1, 2, 3);
vet013_2[1] = Point3i(4, 5, 6);
vet013_2[2] = Point3i(7, 8, 9);
cout<<"vet013_2 = "<<format(Mat(vet013_2), 3)<<endl;//3x3矩阵

//===== 014 cvtColor() =====

void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0);
//code -> enum ColorConversionCodes -> CV_XXXYYY
//dstCn 目标图像的通道数

//===== 015 <math.h>常用工具 =====

//防止内存溢出 alignPtr(), alignSize(), allocate(), deallocate(), fastMalloc(), fastFree();
//计算向量角度 fastAtan2()
//计算立方根 cubRoot()
//向上取整数 cvCeil() 向下取整 cvFloor()
//四舍五入 cvRound()
//是否无穷大 cvisInf() 是否非数值 cvIsNaN()
//文字相关 getTextSize(), cvInitFont(), putText()
//作图相关 circle(), clipLine(), ellipse(), ellipse2Poly(), line(), rectangle(), polylines(), 类LineIterator
//填充相关 fillConvexPloy(), fillPoly()
//随机数 RNG()

GaussianBlur();//高斯模糊
bilateralFilter();//双边过滤
boxFilter();//箱过滤
sqrBoxFilter();
blur();
filter2D();
sepFilter2D();
Sobel();//特征值提取
spatialGradient();//控件梯度
Scharr();
Laplacian();//拉普拉斯算子
Canny();//边沿检测
cornerMinEigenVal();//角检测
cornerHarris();
cornerEigenValsAndVecs();
preCornerDetect();

erode();//腐蚀
dilate();//膨胀

warpAffine();//用矩阵处理矩阵
warpPerspective();
remap();

Rect boundingRect();//求外接矩形
applyColorMap();//颜色滤镜

//===== 016 getTickCount()*1000/getTickFrequency() ms =====

//===== 017 auto =====

//c++11
auto i = 0.12; //double
auto i = 3; //int

//c++11
int v[] = {1, 3, 5, 7};
for(auto i : v)
    cout<<i<<endl;
for(auto i : {1, 3, 5, 7})
    cout<<i<<endl;
for(auto& i : v)
    ++i;

const //承诺不会改变该变量的值
constexpr //编译时求值 //后接常量表达式 即函数的传参必须是固定值

//===== 018 resize() =====

cv::resize( InputArray src, OutputArray dst,
            Size dsize, double fx = 0, double fy = 0,
            int interpolation = INTER_LINEAR );

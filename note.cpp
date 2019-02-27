
#include <iostream>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

//===== 图像载入 =====

Mat imread(const string& filename, int flags = 1);

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

//===== 图像显示 =====

void imshow(const string& winName, InputArray mat);

//CV_WINDOW_AUTOSIZE 控制显示原始大小

//不管8,16,32位还是32位浮点都要转换为8位无符[0,255]的像素再输出
//32位浮点[0,1]将乘以255

//===== 窗口命名 =====

void namedWindow(const string& winName, int flags = WINDOW_AUTOSIZE);

//===== 输出图像到文件 =====

bool imwrite(const string& fileName, InputArray img, const vector<int>& param=vector<int>());

//fileName 输出文件名,需自带后缀.jpg
//img 使用Mat类型
//vector(); 创建一个空向量
//vector(int nSize); 创建一个元素个数为nSize的向量
//vector(int nSize, const t& t); 创建一个元素个数为nSize的向量,且元素都为t
//vector(const vector&); 复制构造函数
//...


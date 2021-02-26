//步骤  ：
//输入图像彩色图像 imread
//转换为灰度图像 – cvtColor
//转换为二值图像 – adaptiveThreshold
//定义结构元素
//开操作 （腐蚀 + 膨胀）提取 水平与垂直线


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("D:/vcprojects/images/chars.png");        //读入原彩色图像
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "result image";
	namedWindow(INPUT_WIN, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);

	Mat gray_src;                                  //转为灰度图像
	cvtColor(src, gray_src, CV_BGR2GRAY);
	imshow("gray image", gray_src);

	Mat binImg;                                      //再由灰度图像转为二值图像
	adaptiveThreshold(~gray_src, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	                 //参数分别为   二值图像最大值，自适应方法，阈值类型，块大小，常量c
	imshow("binary image", binImg);

	//定义结构元素
	// 水平结构元素
	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	// 垂直结构元素
	Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16), Point(-1, -1));
	// 矩形结构元素
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	//进行开操作
	Mat temp;  //先定义一个中间变量
	erode(binImg, temp, hline);    //先腐蚀
	dilate(temp, dst, hline);      //再膨胀
	// morphologyEx(binImg, dst, CV_MOP_OPEN, hline);      //或者直接用开操作,结果一样的
	bitwise_not(dst, dst);         //再补充一步，把背景变为白色，效果更好
	//blur(dst, dst, Size(3, 3), Point(-1, -1));        //再优化效果，让结果显示的更圆滑
	imshow("Final Result", dst);                      //显示最终结果,提取到了水平线   如果想得到垂直线，把45、46行改为vline

	//最牛逼的是用kernel  可以去除图片中干扰到文字的斜线！！！  把45、46 行中改为kernel即可

	waitKey(0);
	return 0;
} 
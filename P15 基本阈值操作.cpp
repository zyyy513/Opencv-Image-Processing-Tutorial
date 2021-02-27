#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
Mat src, gray_src, dst;        //原图，中间灰度图，输出图
int threshold_value = 127;    //先初始化一个滑动条值
int threshold_max = 255;      //滑动条量程255          

//新加功能：给5种阈值操作编号，可用滑动条切换
int type_value = 2;
int type_max = 4;              
const char* output_title = "binary image";
void Threshold_Demo(int, void*);             //声明  阈值操作函数
int main(int argc, char** argv) {
	src = imread("D:/vcprojects/images/test.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	//在输出图像中创建两个滑动条    注意括号中的参数
	createTrackbar("Threshold Value:", output_title, &threshold_value, threshold_max, Threshold_Demo);
	createTrackbar("Type Value:", output_title, &type_value, type_max, Threshold_Demo);
	
	Threshold_Demo(0, 0);     //调用

	waitKey(0);
	return 0;
}

void Threshold_Demo(int, void*) {         //定义
	cvtColor(src, gray_src, CV_BGR2GRAY);    //把原图转为灰度图像
	threshold(gray_src, dst, 0, 255, THRESH_TRIANGLE | type_value); 
	//用THRESH_TRIANGLE算法帮我们寻找阈值，但前提是八通道的，所以要把原图转为灰度图像，再进行阈值操作    
	
	//如果自己找阈值的话：
	//threshold(gray_src, dst, threshold_value,threshold_max,type_value);
	
	imshow(output_title, dst);
}
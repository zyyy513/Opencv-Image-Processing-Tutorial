#include<opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
Mat src, gray_src, dst;
int t1_value = 70;     //滑动条参数   设初始值为50  
int max_value = 255;    //因为是二值图像，所以最大量程就是255 
const char* OUTPUT_TITLE = "Canny Result";    //输出窗口为什么这么定义，之前的代码也有 
void Canny_Demo(int, void*);      //声明 
int main(int argc, char** argv) {
	src = imread("touxiang.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_TITLE[] = "input image";
	namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_TITLE, src);

	cvtColor(src, gray_src, CV_BGR2GRAY);
	createTrackbar("Threshold Value:", OUTPUT_TITLE, &t1_value, max_value, Canny_Demo);
	//滑动条"Threshold Value"   窗口是output title   
	Canny_Demo(0, 0);   //调用函数canny demo

	waitKey(0);
	return 0;
}

void Canny_Demo(int, void*) {        //定义 

	blur(gray_src, gray_src, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);   //先模糊降噪 
	Mat edge_output;
	Canny(gray_src, edge_output, t1_value, t1_value * 2, 3, false);   //输入灰度图像，输出边缘二值图像（背景为黑色）
	//然后是低阈值和高阈值（阈值的选择影响结果，在平时就要注意积累经验值），卷积核大小，用L1归一化（对应bool类型为false） 


	imshow(OUTPUT_TITLE, edge_output);
	//imshow(OUTPUT_TITLE, ~edge_output);     //如果不想让背景为黑色，可取反，让背景为白色 

	////加下面两行，输出是彩色的边缘  
	//dst.create(src.size(), src.type());    
	//src.copyTo(dst, edge_output);
	//imshow(OUTPUT_TITLE, dst);

}

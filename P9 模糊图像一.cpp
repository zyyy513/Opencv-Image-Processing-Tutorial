//本节内容就是对输入图像分别进行均值模糊和高斯模糊，再分别输出显示
//但不能只会API  要理解这两种模糊的原理

#include <opencv2/opencv.hpp> 
#include <iostream> 
using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("D:/vcprojects/images/test.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char input_title[] = "input image";
	char output_title[] = "blur image";
	namedWindow(input_title, CV_WINDOW_AUTOSIZE);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(input_title, src);

	blur(src, dst, Size(11, 11), Point(-1, -1));    //size窗口大小是调整模糊程度的 还可以控制是在x or y轴模糊
	imshow(output_title, dst);

	Mat gblur;                        //再弄一个图像   这样三幅图像会一起输出，对比直观
	GaussianBlur(src, gblur, Size(11, 11), 11, 11);
	imshow("gaussian blur", gblur);         //没namedwindow 系统会自己创建

	waitKey(0);
	return 0;
}
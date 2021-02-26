#include <opencv2/opencv.hpp>
#include <iostream>
#include "math.h"

using namespace cv;
int main(int agrc, char** argv) {
	Mat src, dst;
	src = imread("D:/vcprojects/images/cat.jpg");
	if (!src.data) {
		printf("could not load image...");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "sample up";
	namedWindow(INPUT_WIN, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);

	// 上采样
	pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	imshow(OUTPUT_WIN, dst);                       //结果显示图像确实放大了

	// 降采样
	Mat s_down;
	pyrDown(src, s_down, Size(src.cols / 2, src.rows / 2));
	imshow("sample down", s_down);            //降采样，缩小了

	// DOG高斯不同      先生成高斯金字塔，在金字塔每层做DOG就可以提取每层的特征
	Mat gray_src, g1, g2, dogImg;
	cvtColor(src, gray_src, CV_BGR2GRAY);       //把原图转为灰度图像
	GaussianBlur(gray_src, g1, Size(5, 5), 0, 0);    //对灰度图像高斯模糊成g1
	GaussianBlur(g1, g2, Size(5, 5), 0, 0);    //再模糊成g2
	subtract(g1, g2, dogImg, Mat());            //相减，得到高斯不同

	// 归一化显示    不归一化的话，看上去很暗
	normalize(dogImg, dogImg, 255, 0, NORM_MINMAX);
	imshow("DOG Image", dogImg);

	waitKey(0);
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("D:/vcprojects/images/bin2.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1；
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);
	char output_title[] = "morphology demo";
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11), Point(-1, -1));
	//要定义结构元素 kernel   三个参数分别为 形状、大小、锚点
	morphologyEx(src, dst, CV_MOP_OPEN, kernel);     //把操作改为CLOSE GRANDIENT TOPHAT BLACKHAT 分别实现闭、梯度、顶帽、黑帽
	imshow(output_title, dst);

	waitKey(0);
	return 0;
}
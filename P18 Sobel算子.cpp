//sobel算子的四步操作

#include<opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include<math.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src, dst;
	src = imread("touxiang.jpg");
	if (src.empty())
	{
		printf("Could not find the image!\n");
		return -1;
	}

	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	//①先对原图进行高斯模糊成dst
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	//②转为灰度图像
	Mat gray_src;
	cvtColor(dst, gray_src, CV_BGR2GRAY);
	imshow("gray image", gray_src);
	//③sobel算子求x y两个方向上的梯度  并输出这两个图像
	Mat xgrad, ygrad;  
	Sobel(gray_src, xgrad, CV_16S, 1, 0, 3);   //CV_16S是输出图像深度  1 0 是x为一阶导，y不求导  3是卷积核大小
	Sobel(gray_src, ygrad, CV_16S, 0, 1, 3);

	//Scharr(gray_src, xgrad, CV_16S, 1, 0, 3);   //或者用scharr优化
	//Scharr(gray_src, ygrad, CV_16S, 0, 1, 3);

	//下面是为了避免出现负像素值，用scaleabs取绝对值，全变成正的
	convertScaleAbs(xgrad, xgrad);
	convertScaleAbs(ygrad, ygrad);
	imshow("xgrad", xgrad);
	imshow("ygrad", ygrad);

	//④图像混合，把上面xgrad ygrad混合
	Mat xygrad;
	addWeighted(xgrad, 0.5, ygrad, 0.5, 0, xygrad);
	imshow("xygrad", xygrad);
	/*   下面是遍历所有像素 将xgrad ygrad像素直接相加，而不用图像混合   而且比图像混合效果要好！
	Mat xygrad = Mat(xgrad.size(), xgrad.type());
	printf("type : %d\n", xgrad.type());     这行没看懂
	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);
		}
	}
	*/
	waitKey(0);
	return 0;
}

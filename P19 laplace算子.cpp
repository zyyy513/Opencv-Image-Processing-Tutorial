//Laplace算子

#include<opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
int main(int arga, char** argv)
{
	Mat src, dst;
	src = imread("touxiang.jpg");
	if (!src.data)
	{
		cout << "无法加载图像！" << endl;
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	//①高斯模糊
	GaussianBlur(src, dst, Size(3, 3), 0, 0);    //3*3就够用了
	//②转为灰度
	Mat gray_image;
	cvtColor(dst, gray_image, CV_BGR2GRAY);
	//③Laplace算子
	Mat edge_image;
	Laplacian(gray_image, edge_image, CV_16S, 3);    //CV_16S位图深度  3是卷积核大小
	//④取绝对值
	convertScaleAbs(edge_image, edge_image);

	//⑤显示结果
	//补充，对结果不满意的话，再加上阈值操作
	threshold(edge_image, edge_image, 0, 255, THRESH_OTSU | THRESH_BINARY);
	namedWindow("final result", CV_WINDOW_AUTOSIZE);
	imshow("final result",edge_image );

	waitKey(0);
	return 0;
}

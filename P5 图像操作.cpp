//前面已经了解到读写图像的API:
//imread 可以指定加载为灰度或者RGB图像
//imwrite 保存图像文件，类型由扩展名决定

//另外的 如下，是代码模板
/*
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc,char** argv)
{
	Mat src;
	src = imread("D:aaaa.png");
	if (src.empty())
	{
		cout << "图像读取失败！coule not load image..." << endl;
		return -1;
	}
	namedwindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	waitkey(0);
	return 0;
}
*/

//下面介绍读写像素的操作
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src,gray_src;                       //将原图像RGB转为灰度图像
	src = imread("D:aaaa.png");
	if (src.empty())
	{
		cout << "图像读取失败！coule not load image..." << endl;
		return -1;
	}
	namedwindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	cvt(src, gray_src, CV_BGR2GRAY);
	namedwindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", gray_src);                         //显示灰度图像
	int height = image.rows;         //就是高度row
	int width = image.cols;          //就是宽度col
	   
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {         //遍历所有像素
			int gray = gray_src.at<uchar>(row, col);     //获取上面灰度图像的每个像素
			gray_src.at<uchar>(row, col) = 255 - gray;        //反差操作
		}
	}

	//53—58行是单通道，下面拓展到多通道的情况
	Mat dst;
	dst.create(src.size(), src.type());
	height = src.rows;
	width = src.cols;
	int nc = src.channels();   //通道数
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {         //遍历所有像素
			if (nc == 1)             //如果是单通道，同上
			{
				int gray = gray_src.at<uchar>(row, col);     //获取上面灰度图像的每个像素
				gray_src.at<uchar>(row, col) = 255 - gray;        //反差操作
			}
			else if (nc == 3)       //如果是三通道
			{
				int b = dst.at<Vec3b>(row, col)[0];
				int g = dst.at<Vec3b>(row, col)[1];
				int r = dst.at<Vec3b>(row, col)[2];        //这三行是读写像素操作
				dst.at<Vec3b>(row, col)[0] = 255 - b;
				dst.at<Vec3b>(row, col)[1] = 255 - g;
				dst.at<Vec3b>(row, col)[2] = 255 - r;
			}
		}
	}

	//补充：用下面这一行可以达到与66—83行相同的效果
	bitwise_not(src, dst);

	imshow("gray invert", gray_src/*(或者dst)*/);       //显示反差图像  （注意，没有创建窗口，但系统会自动生成一个窗口）
	waitkey(0);
	return 0;
}


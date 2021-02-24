


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
	char input_win[] = "input image";            //学了一种新写法，与以前不同
	//  cvtColor(src, src, CV_BGR2GRAY);    如果想测试灰度图像的话，可把原图转为灰度图像，发现照样可以改变亮度与对比度
	namedWindow(input_win, CV_WINDOW_AUTOSIZE);
	imshow(input_win, src);

	// contrast and brigthtness changes 
	int height = src.rows;           //高度
	int width = src.cols;            //宽度
	dst = Mat::zeros(src.size(), src.type());    //创建一张大小与类型都与原图像一致的图像  且是RGB格式，但是在三个通道中的排序是B G R
	
	float alpha = 1.2;     //定义参数，大小可以自己更改，仅作测试
	float beta = 30;

	Mat m1;
	src.convertTo(m1, CV_32F);      //为后面3f铺垫
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {         //遍历
			if (src.channels() == 3) {          //如果是三通道
				//先获取三个通道
				float b = m1.at<Vec3f>(row, col)[0];// blue通道
				float g = m1.at<Vec3f>(row, col)[1]; // green通道
				float r = m1.at<Vec3f>(row, col)[2]; // red通道

				// 再output
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);
			}
			else if (src.channels() == 1) {       //如果是单通道
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha + beta);
			}
		}
	}

	//输出显示
	char output_title[] = "contrast and brightness change demo";          //延续了开头的新写法
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(output_title, dst);

	waitKey(0);
	return 0;
}
//本节介绍中值滤波和双边滤波
//要学以致用，学了是为了使用的  面对实际问题要知道用哪种滤波来处理


#include <opencv2/opencv.hpp> 
#include <iostream> 
using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("D:/vcprojects/images/cvtest.png");    //加载一张有椒盐噪声的图像
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	
	medianBlur(src, dst, 3);               //中值滤波
	namedWindow("median Filter Result", CV_WINDOW_AUTOSIZE);
	imshow("median Filter Result", dst);                           //输出发现经过中值滤波，原图像椒盐噪声减少了
	
	bilateralFilter(src, dst, 15, 100, 5);       //双边滤波
	namedWindow("BiBlur Filter Result", CV_WINDOW_AUTOSIZE);
	imshow("BiBlur Filter Result", dst);

	Mat gblur;                        //再与高斯滤波做对比
	GaussianBlur(src, gblur, Size(15, 15), 3, 3);
	imshow("gaussian blur", gblur);

	//双滤波和高斯滤波的对比可以发现，高斯滤波全是模糊的，但双边滤波保留了轮廓，效果很好看

	Mat resultImg;
	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);         //之前的掩膜操作，提高对比度
	filter2D(dst, resultImg, -1, kernel, Point(-1, -1), 0);
	imshow("Final Result", resultImg);           //再在上面双边滤波的基础上进行掩膜，对比度提高了，效果非常好！！

	waitKey(0);
	return 0;

}
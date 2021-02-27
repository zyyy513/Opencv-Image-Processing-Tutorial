//掌握卷积原理，几种卷积算子（Kernel）

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;

	src = imread("D:/vcprojects/images/test1.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "Robert x";
	namedWindow(INPUT_WIN, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);

	imshow(INPUT_WIN, src);

	//Robert算子 x方向
	Mat kernel_x = (Mat_<int>(2, 2)) << (1, 0, 0, -1);     //x方向的2*2矩阵 （135度）
	filter2D(src, dst, -1, kernel_x, Point(-1, -1), 0.0);      //用filter2D是为了提高对比度？
	imshow(OUTPUT_WIN, dst);
	//Robert算子 y方向
	Mat ying;
	Mat kernel_y = (Mat_<int>(2, 2)) << (0，1, 0, -1);     //y方向的2*2矩阵  （45度）
	filter2D(src, ying, -1, kernel_y, Point(-1, -1), 0.0);
	imshow("Robert y", ying);

	// Sobel X 方向
	// Mat kernel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);   //sobel算子是3*3矩阵
	// filter2D(src, dst, -1, kernel_x, Point(-1, -1), 0.0);
	// imshow(OUTPUT_WIN, dst);

	// Sobel Y 方向
	// Mat yimg;
	// Mat kernel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0,0,0, 1,2,1);
	// filter2D(src, yimg, -1, kernel_y, Point(-1, -1), 0.0);
	// imshow("sobel y", yimg)

	// 拉普拉斯算子
	//Mat kernel_y = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	//filter2D(src, dst, -1, kernel_y, Point(-1, -1), 0.0);
	// imshow(OUTPUT_WIN, dst);
	
	
	//补充：自定义卷积模糊
	int c = 0;
	int index = 0;
	int ksize = 0;
	while (true) {
		c = waitKey(500);   //隔500毫秒，自动模糊
		if ((char)c == 27) {// 意思是按ESC键退出   
			break;
		}
		
		ksize = 5 + (index % 8) * 2;
		//定义卷积核
		Mat kernel = Mat::ones(Size(ksize, ksize), CV_32F) / (float)(ksize * ksize);    //ksize*ksize转为float型
		//这行没看明白   （宽高都是ksize大小的矩阵，每个元素是1/ksize*ksize，相当于均值模糊）
		filter2D(src, dst, -1, kernel, Point(-1, -1));
		index++;    //时间越长，模糊程度越大
		imshow("自定义卷积模糊", dst);
	}

	// imshow("Sobel Y", yimg);
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	//先加载并显示图像
	Mat src;
	src = imread("D:/vcprojects/images/test.png");
	if (src.empty()) {
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	/*Mat dst;
	dst = Mat(src.size(), src.type());         //初始化了一个mat对象，大小与类型都与初始图象src一致
	dst = Scalar(127, 0, 255);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);*/                       //这是生成了一个背景图像


	Mat dst = src.clone();           //这是克隆（复制）原图像
	//src.copyTo(dst);             //这种方式也可以克隆
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);


	cvtColor(src, dst, CV_BGR2GRAY);
	printf("input image channels : %d\n", src.channels());         //原图像是3通道
	printf("output image channels : %d\n", dst.channels());        //通过灰度转换后，输出图像是单通道


	int cols = dst.cols;     //得到全部列
	int rows = dst.rows;     //得到全部行
	printf("rows : %d cols : %d\n", rows, cols);       //输出行数、列数
	const uchar* firstRow = dst.ptr<uchar>(0);
	printf("fist pixel value : %d\n", *firstRow);         //第一个像素的灰度值


	Mat M(100, 100, CV_8UC1, Scalar(127));        //Mat构造函数M  是100*100的  8表示8位，uc表示uchar，3表示三通道，scalar是向量，其长度要与通道数一致
	cout << "M =" << endl << M << endl;

	Mat m1;                                //通过create方式创建与原图像相同大小的图像  且显示为红色
	m1.create(src.size(), src.type());
	m1 = Scalar(0, 0, 255);

	Mat csrc;                            //定义一个小数组3*3   可用于掩膜提高对比度操作
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src, csrc, -1, kernel);

	Mat m2 = Mat::zeros(src.size(), src.type());     //创建原图像大小相同的纯黑图像

	Mat m2 = Mat::eye(2, 2, CV_8UC1);    //创建单位矩阵  2*2的
	cout << "m2 =" << endl << m2 << endl;

	imshow("output", m2);
	waitKey(0);
	return 0;
}

//本文介绍线性混合操作的理论，并给出相关API：addweighted

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src1, src2, dst;              //两幅原始图像合成dst
	src1 = imread("D:/vcprojects/images/LinuxLogo.jpg");
	src2 = imread("D:/vcprojects/images/win7logo.jpg");
	if (!src1.data) {
		cout << "could not load image Linux Logo..." << endl;
		return -1;
	}
	if (!src2.data) {
		cout << "could not load image WIN7 Logo..." << endl;
		return -1;
	}                             //读入两幅图像，并检测是否读取成功               

	double alpha = 0.5;              //定义权重
	if (src1.rows == src2.rows && src1.cols == src2.cols && src1.type() == src2.type()) {                //两幅图像的大小和类型都要一致
		 addWeighted(src1, alpha, src2, (1.0 - alpha), 0.0, dst);            //addweighted API，注意里面的参数
		// multiply(src1, src2, dst, 1.0);     //补充：相乘操作

		imshow("linuxlogo", src1);
		imshow("win7logo", src2);
		namedWindow("blend demo", CV_WINDOW_AUTOSIZE);
		imshow("blend demo", dst);                    //输出显示这三幅图像，注意src1 src2都没有namedwindow，因为不写也可以，系统会默认创建窗口
	}
	else {                     //否则，两幅图像不一致，无法线性混合
		printf("could not blend images , the size of images is not same...\n");
		return -1;
	}

	waitKey(0);
	return 0;
}
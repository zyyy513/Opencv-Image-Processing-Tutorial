#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("D:/vcprojects/images/test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char INPUT_WIN[] = "input image";
	char OUTPUT_WIN[] = "Border Demo";
	namedWindow(INPUT_WIN, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_WIN, src);

	// 定义边缘长度  先获取原图的宽高   并强制转为int型
	int top = (int)(0.05*src.rows);          上
	int bottom = (int)(0.05*src.rows);       下
	int left = (int)(0.05*src.cols);         左
	int right = (int)(0.05*src.cols);        右
	RNG rng(12345);                          //生成随机数rng  后面生成随机颜色
	int borderType = BORDER_DEFAULT;        //边缘处理方法


	int c = 0;
	while (true) {
		c = waitKey(500);    //每隔半秒生成颜色
		// ESC
		if ((char)c == 27) {
			break;
		}

		//新添功能：通过waitkey捕捉键盘输入字符，在循环中切换边缘处理方法bordertype
		if ((char)c == 'r') {
			borderType = BORDER_REPLICATE;
		} else if((char)c == 'w') {
			borderType = BORDER_WRAP;
		} else if((char)c == 'c') {
			borderType = BORDER_CONSTANT;
		}

		//给图像添加边缘 copymakeborder
		//上面已定义了上下左右边缘长度  下面定义颜色   用上面的随机数rng    只有BORDER_CONSTANT才会用到这个指定颜色  
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));     //都是0—255之间生成颜色
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);
		imshow(OUTPUT_WIN, dst);
	}
	
	/*    下面没看懂要干嘛
	GaussianBlur(src, dst, Size(5, 5), 0, 0);
	imshow(OUTPUT_WIN, dst);
	*/ 

	waitKey(0);
	return 0;
}
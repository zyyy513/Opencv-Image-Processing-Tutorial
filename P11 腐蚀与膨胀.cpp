#include <opencv2/opencv.hpp> 
#include <iostream> 
using namespace cv;

Mat src, dst;
 

//下面三行是加入动态调整结构元素大小功能       在输出中加入滑动条  自己运行就知道了
int element_size = 3;
int max_size = 21;           //滑动条长度
void CallBack_Demo(int, void*);     //声明

int main(int argc, char** argv) {

	src = imread("D:/vcprojects/images/test1.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	char OUTPUT_WIN[] = "output image";
	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);
	createTrackbar("Element Size :", OUTPUT_WIN, &element_size, max_size, CallBack_Demo);    //滑动条
	CallBack_Demo(0, 0);     //调用

	waitKey(0);
	return 0;
}

void CallBack_Demo(int, void*) {           //定义
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));   //三个参数分别为形状、大小、锚点
	dilate(src, dst, structureElement, Point(-1, -1), 1);    //膨胀
	erode(src, dst, structureElement);                       //腐蚀
	imshow(OUTPUT_WIN, dst);
	return;
}
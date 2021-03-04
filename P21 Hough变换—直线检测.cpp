//先进行边缘检测  再Hough直线检测
#include<opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat src, src_gray, dst;
	src = imread("line0.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_TITLE[] = "input image";
	char OUTPUT_TITLE[] = "hough-line-detection";
	namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
	imshow(INPUT_TITLE, src);

	// extract edge canny边缘检测 提取边缘 
	Canny(src, src_gray, 150, 200);   //高低阈值分别为150，200  //src就是黑白的，不用转为灰度了 
	cvtColor(src_gray, dst, CV_GRAY2BGR);      //灰度转彩色 
	imshow("edge image", src_gray);


	vector<Vec4f> plines;     //把Hough变换得出来的结果放到plines数组中 
	HoughLinesP(src_gray, plines, 1, CV_PI / 180.0, 10, 0, 10);   //了解这些参数   
	Scalar color = Scalar(0, 0, 255);     //检测出来的直线用红线表示 
	for (size_t i = 0; i < plines.size(); i++) {     //把size_t 看成int   遍历数组 
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 2, LINE_AA);
		//线宽是2  line_aa是反锯齿的line_type 
	}
	imshow(OUTPUT_TITLE, dst);

	/*   补充：HoughlinesAPI  一般不用
	vector<Vec2f> lines;
	HoughLines(src_gray, lines, 1, CV_PI / 180, 150, 0, 0);
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0]; // 极坐标中的r长度
		float theta = lines[i][1]; // 极坐标中的角度
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		// 转换为平面坐标的四个点
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}
	*/


	waitKey(0);
	return 0;
}

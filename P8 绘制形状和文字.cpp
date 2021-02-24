//注意函数声明——函数调用——函数实现的步骤


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat bgImage;           //在背景图backgroundimage上绘制形状
const char* drawdemo_win = "draw shapes and text demo";             //这行怎么理解？C++的内容
void MyLines();              //先声明   绘制直线的函数
void MyRectangle();          //绘制矩形
void MyEllipse();              //绘制椭圆
void MyCircle();            //绘制圆
void MyPolygon();            //绘制多边型
void RandomLineDemo();       //绘制随机直线（长度、位置、颜色都随机）

int main(int argc, char** argv) {
	bgImage = imread("D:/vcprojects/images/test1.png");
	if (!bgImage.data) {
		printf("could not load image...\n");
		return -1;
	}
	//函数调用
	Mylines();              
	Myrectangle();
	Myellipse();
	Mycircle();
	Mypolygon();

	putText(bgImage, "Hello OpenCV", Point(300, 300), CV_FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 23, 200), 3, 8);
	//这是在图像上绘制文字操作，文字内容为"Hello OpenCV"    1.0是文字尺寸   CV_FONT_HERSHEY_COMPLEX是字体，可以更改

	namedWindow(drawdemo_win, CV_WINDOW_AUTOSIZE);
	imshow(drawdemo_win, bgImage);

	RandomLineDemo();    

	waitKey(0);
	return 0;
}

void MyLines() {                             //定义绘制直线函数
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 400;
	p2.y = 400;                                    //定义p1p2两个点   两种定义方式
	Scalar color = Scalar(0, 0, 255);            //颜色为红色
	line(bgImage, p1, p2, color, 1, LINE_AA);      //注意括号中的参数   1代表线宽  line aa是反锯齿    line_type分为4 8 和AA
}

void MyRectangle() {                 
	Rect rect = Rect(200, 100, 300, 300);        //绘制矩形有四个参数 200，100是起始位置 300，300是宽高
	Scalar color = Scalar(255, 0, 0);            //颜色为蓝色
	rectangle(bgImage, rect, color, 2, LINE_8);     //线宽为2
}

void MyEllipse() {
	Scalar color = Scalar(0, 255, 0);     //绿色
	ellipse(bgImage, Point(bgImage.cols / 2, bgImage.rows / 2), Size(bgImage.cols / 4, bgImage.rows / 8), 90, 0, 360, color, 2, LINE_8);    
	//point()是椭圆中心  size()是长短轴    90 是正椭圆  0—360度
}

void MyCircle() {
	Scalar color = Scalar(0, 255, 255);               //绿色加红色=黄色
	Point center = Point(bgImage.cols / 2, bgImage.rows / 2);    //圆心
	circle(bgImage, center, 150, color, 2, 8);     //150是半径
}

void MyPolygon() {
	Point pts[1][5];                   //一行五列的数组，定义一个五边形，分别给出每个点的坐标
	pts[0][0] = Point(100, 100);
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 200);
	pts[0][3] = Point(200, 100);
	pts[0][4] = Point(100, 100);

	const Point* ppts[] = { pts[0] };         //这是什么？
	int npt[] = { 5 };                       // npt是多边形顶点数目

	Scalar color = Scalar(255, 12, 255);
	fillPoly(bgImage, ppts, npt, 1, color, 8);    //fillpoly是用color颜色填满该多边形 
}

void RandomLineDemo() {
	RNG rng(12345);            //随机种子  rng= random number generater
	Point pt1;
	Point pt2;         //定义两个点
	Mat bgimage2 = Mat::zeros(bgImage.size(), bgImage.type());    //重新生成一个图像，与bgimage大小类型都一致   颜色是黑的
	namedWindow("random line demo", CV_WINDOW_AUTOSIZE);               //随机绘制直线与上面独立，要把上面的各种注释掉   而且是在黑背景上画
	
	for (int i = 0; i < 100000; i++) {      //因为画很多线，所以用循环
		pt1.x = rng.uniform(0, bgImage.cols);        //下面四行的意思是两个点的位置都不要超出范围
		pt2.x = rng.uniform(0, bgImage.cols);          //uniform是生成正态分布随机数
		pt1.y = rng.uniform(0, bgImage.rows);
		pt2.y = rng.uniform(0, bgImage.rows);
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));    //而且颜色也是随机的
		if (waitKey(50) > 0) {           //给一个停止命令
			break;
		}
		line(bgimage2, pt1, pt2, color, 1, 8);       //开始画
		imshow("random line demo", bgimage2);
	}
}

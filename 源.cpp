#include<opencv2\opencv.hpp>    //头文件可以包含需要的各模块的头文件，如highgui.hpp  但用总的头文件oopencv.hpp 比较省心，虽然编译时间较长
#include<iostream>
#include<math.h>

using namespace cv;   //命名空间cv   可免去在每个函数前再加cv::

int main(int argc, char** argv)   //形参列表好像也可以不加这两个
{
	Mat src = imread("D:/aaaaa.jpg");        //mat类负责图像数据的存储，可以自动分配内存和自动释放，可理解为智能指针
                                      //imread是读取图像，D:/aaaaa是图像所在位置
	if (src.empty())             //读取后用empty() 来判断是否读取成功
	{
		cout << "无法加载图像！could not load image!" << endl;
		return -1;
	}

	namedwindow("test opencv setup", CV_WINDOW_AUTOSIZE);    //创建用于图像显示的窗口 autosize的作用是自动根据图像大小，显示窗口大小
	imshow("test opencv setup"，src);     //imshow用于显示  而且之后一定要用waitkey(

	waitkey(0);
	return 0;
}


//上面介绍了imread namedwindow imshow 三个api
//下面介绍加载，修改，保存操作 imread cvtcolor 和 imwrite
#include<opencv2\opencv.hpp>   
#include<iostream>
#include<math.h>

using namespace cv;   

int main(int argc, char** argv)   
{
	//① 加载图像
	Mat src = imread("D:/aaaaa.jpg",IMREAD_GRAYSCALE);        //后面一个参数是加载的图像类型 有灰度图像，RGB图像等等				
	if (src.empty())             
	{
		cout << "无法加载图像！could not load image!" << endl;
		return -1;
	}

	//② 显示图像
	namedwindow("test opencv setup", CV_WINDOW_AUTOSIZE);
	imshow("test opencv setup"，src);     

	//③ 修改图像  是把图像从一个色彩空间转换到另一个色彩空间，有三个参数    （还要再namedwindow，用于显示修改后的图像）
	namedwindow("output window", CV_WINDOW_AUTOSIZE);   
	Mat output_image;
	cvtcolor(src, output_image, CV_BGR2GRAY);        //含义是初始图象src通过CV_BGR2GRAY转换成灰度图像output_image
	imshow("output window"，output_image);

	//④ 保存图像
	imwrite("D:/bbbb.png", output_image);    //保存到D:/bbbb处，并且为png格式  也可以是jpg,tif等

	waitkey(0);
	return 0;
}


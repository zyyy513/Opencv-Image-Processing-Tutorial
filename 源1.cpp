#include<opencv2/opencv.hpp
#include<iostream>
#include<math,h>
using namespace cv;

int main(int argc,char** argv)    //char** 说明argv是二重指针？
{
	Mat src, dst;           //初始图象src和处理后的图像dst
	src = imread("D:/aaaa.png");
	if (!src.data)                 //补充点：不用empty(),用data也能判断是否读取成功   多学一些api!
	{
		cout << "图像读取失败！" << endl;
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input immage", src);
	//上面完成了对象的加载与显示

	//用掩膜操作，实现图像对比度增强
	int cols = (src.cols-1) * src.channels();         //宽度  要乘以通道数  （RGB是三通道）
	int offsetx = src.channels;      //通道数
	int rows = src.rows;              //高度
	dst = Mat::zeros(src.size(), src.type());     //对输出图像进行初始化  zeros的作用是让输出图像与原始输入图像的大小、类型都一致

	for (int row = 1; row < rows - 1; row++)
	{
		const uchar* current = src.ptr<uchar>(row-1);
		const uchar* previous = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row+1);           //上中下三行是用指针访问图像像素
		uchar* output = dst.ptr<uchar>(row);
		for (int col = offsetx; col < cols; col++)
			{
				output[col] = saturate_cast<uchar>(5 * current[col] - (current[col - offsetx] + current[col + offsetx] + previous[col] + next[vol]));
				//一定要回这个api，是处理像素范围的函数saturate_cast   它的作用是确保RGB的取值在0—255之间。小于0的返回0；大于255的返回255。
			}
	}

	//再显示掩模处理后的图像
	namedWindow("contrast image demo", CV_WINDOW_AUTOSIZE);
	imshow("contrast image demo", dst);

	

	//除了19—40行的方法。用api : filter2D 也能实现通过样的操作！ 只需两行！！    虽然函数好用，只有两行  但是也要明白上面第一种方法的原理！不要光会掉API
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);    //定义掩膜
	filter2D(src, dst, src.depth(), kernel);

	waitkey(0);
	return 0;
}
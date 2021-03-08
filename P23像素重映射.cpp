#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
Mat src, dst, map_x, map_y;     //定义XY两个映射表
const char* OUTPUT_TITLE = "remap demo";
int index = 0;
void update_map(void);
int main(int argc, char** argv) {
	src = imread("girl.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	char input_win[] = "input image";
	namedWindow(input_win, CV_WINDOW_AUTOSIZE);
	namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
	imshow(input_win, src);

	map_x.create(src.size(), CV_32FC1);  //表示32位的单通道
	map_y.create(src.size(), CV_32FC1);

	int c = 0;
	while (true) {     //500ms循环一次   按esc退出
		c = waitKey(500);
		if ((char)c == 27) {
			break;
		}
		index = c % 4;
		update_map();
		remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 255));   //remap的API   （边缘用的黄色填充）
		imshow(OUTPUT_TITLE, dst);
	}

	return 0;
}

void update_map(void) {
	//获取像素
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			switch (index) {      //给几种选项
			//缩小一半
			case 0:
				if (col > (src.cols * 0.25) && col <= (src.cols * 0.75) && row > (src.rows * 0.25) && row <= (src.rows * 0.75)) {
					map_x.at<float>(row, col) = 2 * (col - (src.cols * 0.25));  
					map_y.at<float>(row, col) = 2 * (row - (src.rows * 0.25));
				}
				else {
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
			//左右对调
			case 1:
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = row;
				break;
			//上下对调
			case 2:
				map_x.at<float>(row, col) = col;
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			//上下左右全对调
			case 3:
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			}

		}
	}
}

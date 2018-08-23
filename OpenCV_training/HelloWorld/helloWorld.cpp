#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using std::cout;

void displayImage(const char* path)
{
	Mat image;
	image = imread(path, 1);

	if (!image.data) {
		cout << "No image data!\n";
		return;
	}

	imshow("Display Image", image);

	waitKey(0);
}

int main()
{
	const char* path = "./images/tree-17.png";
	displayImage(path);
	return 0;
}
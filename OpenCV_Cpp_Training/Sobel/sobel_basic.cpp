#include "opencv2/imgproc.hpp"		// image processing
#include "opencv2/imgcodecs.hpp"	// image I/O
#include "opencv2/highgui.hpp"		// high level GUI and Media
#include "opencv2/core.hpp"			// core functionality
#include <iostream>

using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
	// Default path
	string folder = "images/";
	string original_path = folder + "leaf_disease.png";

	// Command line parsing
	// CommandLineParser parser(argc, argv,"{@input | original_path | input image}");

	// Load image [source, destination or mask]
	// Mat source = imread(parser.get<string>("@input"));
	
	Mat source = imread(original_path);
	
	if(source.empty()) {
        cout << "could not open or find the image!\n";
        // cout << "ssage: " << argv[0] << " <input image>\n";
        return EXIT_FAILURE;
	}

	Mat gray;
	cvtColor(source, gray, COLOR_BGR2GRAY);

	Mat sobelx;
	Sobel(gray, sobelx, CV_32F, 1, 0);

	double minVal, maxVal;
	minMaxLoc(sobelx, &minVal, &maxVal);

	Mat result;
	sobelx.convertTo(result, CV_8U, 250.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

	imshow("Input", source);
	imshow("Gray", gray);
	imshow("Sobelx", sobelx);
	imshow("Result", result);	

	waitKey(0);

	return 0;
}
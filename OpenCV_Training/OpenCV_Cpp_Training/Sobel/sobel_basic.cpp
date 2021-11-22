/* OpenCV 4.5.1 */
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    // Default path
    string folder = "../../../Images/";
    string original_path = folder + "folha_doente_falsa.png";

    // Command line parsing
    CommandLineParser parser(argc, argv, "{@input || image path}");
    if (!parser.get<String>("@input").empty()) {
        original_path = parser.get<String>("@input");
    }

    // Original
    Mat source = imread(original_path);

    if (source.empty()) {
        cout << "could not open or find the image!\n";
        cout << "message: " << argv[0] << " <input image>\n";
        return EXIT_FAILURE;
    }

    Mat gray;
    cvtColor(source, gray, COLOR_BGR2GRAY);

    Mat sobel;
    Sobel(gray, sobel, CV_32F, 1, 0);

    double minVal, maxVal;
    minMaxLoc(sobel, &minVal, &maxVal); // Finds the global minimum and maximum in an array.

    Mat result;
    //  Converts source pixel values to the target data type. src (sobel) => dst (result)
    sobel.convertTo(result, CV_8U, 250.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

    imshow("Input", source);
    imshow("Gray", gray);
    imshow("Sobel", sobel);
    imshow("Result", result);

    waitKey(0);

    return 0;
}
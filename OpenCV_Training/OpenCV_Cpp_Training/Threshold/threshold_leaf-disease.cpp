/* OpenCV 4.5.1 */
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    string folder = "../../../Images/";
    string name = "folha_doente_falsa.png";
    // string name = "folha_cafeeiro_doente.png";
    string original_path = folder + name;

    CommandLineParser parser(argc, argv, "{@input || image path}");
    if (!parser.get<String>("@input").empty()) {
        original_path = parser.get<String>("@input");
    }

    Mat src = imread(original_path);
    if (src.empty()) {
        cout << "Error loading" <<  src << "\n";
        return EXIT_FAILURE;
    }

    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    Mat src_bin, src_bin_inv;
    int min = 100, max = 150;
    threshold(src_gray, src_bin, min, max, THRESH_BINARY);
    threshold(src_gray, src_bin_inv, min, max, THRESH_BINARY_INV);

    Mat src_hsv;
    cvtColor(src, src_hsv, COLOR_BGR2HSV);

    Mat src_hsv_inRange = Mat::zeros(src.size(), CV_8UC3);
    inRange(src_hsv, Scalar(20, 10, 10), Scalar(90, 255, 255), src_hsv_inRange);

    Mat src_leafSpots;
    bitwise_not(src_hsv_inRange, src_leafSpots, src_bin_inv);

    Mat result;
    Mat mRed(src.size(), CV_8UC3, Scalar(0, 0, 255));
    bitwise_or(mRed, mRed, result, src_leafSpots);

    imshow("Original", src);
    imshow("Gray", src_gray);
    imshow("Binary", src_bin);
    imshow("Binary Inverted", src_bin_inv);
    imshow("HSV", src_hsv);
    imshow("HSV in Range", src_hsv_inRange);
    imshow("Leaf Spots", src_leafSpots);
    imshow("Result", result);

    waitKey();

    return 0;
}
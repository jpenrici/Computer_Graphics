/* OpenCV 4.5.1 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using std::cout;

int main(int argc, char **argv)
{
    Mat src, dst;

    // Original
    src = imread("../../../Images/anthurium_alpha.png");
    if (src.empty()) {
        cout << "Error loading" << src << "\n";
        return EXIT_FAILURE;
    }

    // Rect(x, y, width, height)
    Rect roi(src.cols / 2, src.rows / 2, src.cols / 2, src.rows / 2);
    src(roi).copyTo(dst);

    imshow("Original", src);
    imshow("ROI", dst);

    waitKey();

    return 0;
}
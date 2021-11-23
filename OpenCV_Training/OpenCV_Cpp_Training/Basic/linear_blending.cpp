/* OpenCV 4.5.1 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using std::cin;
using std::cout;

int main(int argc, char **argv)
{
    Mat src, dst;

    // Original
    src = imread("../../../Images/anthurium_alpha.png");
    if (src.empty()) {
        cout << "Error loading " <<  src << "\n";
        return -1;
    }

    // Green background
    Mat bg(src.size(), src.type(), Scalar(0, 128, 0));

    // Calculates the weighted sum of two arrays (src and bg) and copies it into array dst.
    double alpha(0.5);
    double beta(1.0 - alpha);
    addWeighted(src, alpha, bg, beta, 0.0, dst);

    imshow("Linear Blend", dst);
    imshow("Background", bg);

    waitKey(0);

    return 0;
}
/* OpenCV 4.5.1 */
#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat src_gray;
int thresh = 100;
void thresh_callback(int, void *);

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

    Mat src = imread(original_path);
    if (src.empty()) {
        cout << "Error loading" <<  src << "\n";
        return EXIT_FAILURE;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow("Window", WINDOW_AUTOSIZE);
    imshow("Window", src);

    const int max_thresh = 255;
    createTrackbar("Canny thresh", "Window", &thresh, max_thresh, thresh_callback);

    waitKey();

    return 0;
}

void thresh_callback(int, void *)
{

    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(drawing, contours, (int)i, Scalar(0, 0, 256), 2, LINE_8, hierarchy, 0);
    }

    imshow("Contours", drawing);
}
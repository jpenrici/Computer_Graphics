/* OpenCV 4.5.1 */
#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

vector<Point> points;
Mat original, bkp;

void mouseHandler(int, int, int, int, void *);

int main(int argc, char **argv)
{
    original = imread("../../../Images/folha_doente_falsa.png", IMREAD_COLOR);
    if (original.empty()) {
        cout << "Error loading\n";
        return EXIT_FAILURE;
    }

    original.copyTo(bkp);
    points.clear();

    namedWindow("Window", WINDOW_AUTOSIZE);
    setMouseCallback("Window", mouseHandler, NULL);
    imshow("Window", original);

    waitKey(0);

    return 0;
}

void mouseHandler(int event, int x, int y, int, void *)
{

    if (event == EVENT_LBUTTONDOWN) {
        cout << "Point (" << x << ", " <<  y << ")\n";
        if (!points.empty()) {
            line(bkp, points.back(), Point(x, y), Scalar(0, 0, 255), 2, 8, 0);
        }
        points.push_back(Point(x, y));
        imshow("Window", bkp);
    }

    if (event == EVENT_MBUTTONDOWN) {
        cout << "Reset ...\n";
        points.clear();
        original.copyTo(bkp);
        imshow("Window", bkp);
    }

    if (event == EVENT_RBUTTONDOWN && !points.empty()) {
        Mat result = Mat::zeros(original.size(), CV_8UC3);
        Mat mask = Mat::zeros(original.size(), CV_8UC1);

        int npts = (int) points.size();
        vector<Point> tmp = points;
        const Point *elementPoints[1] = { &tmp[0] };
        cout << "elementsPoints=" << elementPoints << endl;

        fillPoly(mask, elementPoints, &npts, 1, Scalar(128, 128, 128), 8);
        bitwise_and(original, original, result, mask);
        imshow("Mask", result);
    }
}
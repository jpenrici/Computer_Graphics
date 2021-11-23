/* OpenCV 4.5.1 */
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int edgeThresh = 1;
int edgeThreshScharr = 1;
Mat src, gray, blurImg, edge1, edge2, cedge;

static void onTrackbar(int, void *);

int main(int argc, const char **argv)
{
    string folder = "../../../Images/";
    string original_path = folder + "folha_doente_falsa.png";

    CommandLineParser parser(argc, argv, "{@input || image path}");
    if (!parser.get<String>("@input").empty()) {
        original_path = parser.get<String>("@input");
    }

    src = imread(original_path, IMREAD_COLOR);
    if (src.empty()) {
        cout << "Error loading" <<  src << "\n";
        return EXIT_FAILURE;
    }

    cedge.create(src.size(), src.type());
    cvtColor(src, gray, COLOR_BGR2GRAY);

    namedWindow("Edge1", 1);
    namedWindow("Edge2", 1);
    createTrackbar("Canny threshold default", "Edge1", &edgeThresh, 100, onTrackbar);
    createTrackbar("Canny threshold Scharr", "Edge2", &edgeThreshScharr, 400, onTrackbar);
    onTrackbar(0, 0);

    waitKey(0);

    return 0;
}

static void onTrackbar(int, void *)
{
    blur(gray, blurImg, Size(3, 3));

    Canny(blurImg, edge1, edgeThresh, edgeThresh * 3, 3);
    cedge = Scalar::all(0);

    src.copyTo(cedge, edge1);
    imshow("Edge1", cedge);

    // Canny detector with scharr
    Mat dx, dy;

    Scharr(blurImg, dx, CV_16S, 1, 0);
    Scharr(blurImg, dy, CV_16S, 0, 1);

    Canny(dx, dy, edge2, edgeThreshScharr, edgeThreshScharr * 3);
    cedge = Scalar::all(0);

    src.copyTo(cedge, edge2);
    imshow("Edge2", cedge);
}
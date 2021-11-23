/* OpenCV 4.5.1 */
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

const int max_value_H = 360 / 2;
const int max_value = 255;
const string window_name = "Input";
const string window_detection_name = "Threshold_HSV";

int low_H = 0, high_H = max_value;
int low_S = 0, high_S = max_value;
int low_V = 0, high_V = max_value;

static void on_low_H_thresh_trackbar(int, void *)
{
    low_H = min(high_H - 1, low_H);
    setTrackbarPos("Low H", window_detection_name, low_H);
}

static void on_high_H_thresh_trackbar(int, void *)
{
    high_H = max(high_H, low_H + 1);
    setTrackbarPos("High H", window_detection_name, high_H);
}

static void on_low_S_thresh_trackbar(int, void *)
{
    low_S = min(high_S - 1, low_S);
    setTrackbarPos("Low S", window_detection_name, low_S);
}

static void on_high_S_thresh_trackbar(int, void *)
{
    high_S = max(high_S, low_S + 1);
    setTrackbarPos("High S", window_detection_name, high_S);
}

static void on_low_V_thresh_trackbar(int, void *)
{
    low_V = min(high_V - 1, low_V);
    setTrackbarPos("Low V", window_detection_name, low_V);
}

static void on_high_V_thresh_trackbar(int, void *)
{
    high_V = max(high_V, low_V + 1);
    setTrackbarPos("High V", window_detection_name, high_V);
}

int main(int argc, char **argv)
{
    // Default path
    string folder = "../../../Images/";
    string name = "folha_doente_falsa.png";
    string original_path = folder + name;

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

    namedWindow(window_name);
    namedWindow(window_detection_name);

    // Trackbars to set thresholds for HSV values
    createTrackbar("Low H", window_detection_name,
                   &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name,
                   &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name,
                   &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name,
                   &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name,
                   &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name,
                   &high_V, max_value, on_high_V_thresh_trackbar);

    Mat frame, frame_HSV, frame_threshold;

    frame = imread(original_path);
    imshow(window_name, frame);

    while (true) {

        // Convert from BGR to HSV colorspace
        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);

        // Detect the object based on HSV Range Values
        inRange(frame_HSV, Scalar(low_H, low_S, low_V),
                Scalar(high_H, high_S, high_V), frame_threshold);

        // Show the frames
        imshow(window_detection_name, frame_threshold);

        char key = (char) waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
        if (key == 's') {
            string output("");
            output += "output/" + name;
            output += "-H(" + to_string(low_H) + "-" + to_string(high_H);
            output += ")_S(" + to_string(low_S) + "-" + to_string(high_S);
            output += ")_V(" + to_string(low_V) + "-" + to_string(high_V);
            output += ").png";
            imwrite(output, frame_threshold);
        }
    }

    return 0;
}
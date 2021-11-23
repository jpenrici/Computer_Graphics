/* OpenCV 4.5.1 */
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void Sharpen(const Mat &image, Mat &result);

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

    Mat dst_sharpen, result_sharpen;

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    Sharpen(src, dst_sharpen);

    Mat kernel = (
                     Mat_<char>(3, 3) <<
                     0, -1,  0,
                     -1,  5, -1,
                     0, -1,  0);

    filter2D(src, result_sharpen, src.depth(), kernel);

    imshow("Input", src);
    imshow("Output", result_sharpen);

    waitKey(0);

    return 0;
}

void Sharpen(const Mat &image, Mat &result)
{
    CV_Assert(image.depth() == CV_8U);

    const int nChannels = image.channels();
    result.create(image.size(), image.type());

    for (int j = 1; j < image.rows - 1; ++j) {
        const uchar *previous = image.ptr<uchar>(j - 1);
        const uchar *current  = image.ptr<uchar>(j);
        const uchar *next     = image.ptr<uchar>(j + 1);

        uchar *output = result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (image.cols - 1); ++i) {
            *output++ = saturate_cast<uchar>(
                            5 * current[i]
                            - current[i - nChannels]
                            - current[i + nChannels]
                            - previous[i]
                            - next[i]);
        }
    }

    result.row(0).setTo(Scalar(0));
    result.row(result.rows - 1).setTo(Scalar(0));
    result.col(0).setTo(Scalar(0));
    result.col(result.cols - 1).setTo(Scalar(0));
}
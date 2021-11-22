/* OpenCV 4.5.1 */
#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    // Default path
    string folder = "../../../Images/";
    string original_path = folder + "folha_cafeeiro_doente.png";

    // Command line parsing
    CommandLineParser parser(argc, argv, "{@input || image path}");
    if (!parser.get<String>("@input").empty()) {
        original_path = parser.get<String>("@input");
    }

    // Original
    Mat img = imread(original_path, IMREAD_COLOR);
    if (img.rows * img.cols <= 0) {
        cout << original_path << " is empty or cannot be found.\n";
        return EXIT_FAILURE;
    }

    // SimpleBlobDetector - Class for extracting blobs from an image.
    // https://docs.opencv.org/4.x/d0/d7a/classcv_1_1SimpleBlobDetector.html
    SimpleBlobDetector::Params pDefaultBlob;
    pDefaultBlob.filterByArea = false;
    pDefaultBlob.filterByCircularity = false;
    pDefaultBlob.filterByColor = false;
    pDefaultBlob.filterByConvexity = false;
    pDefaultBlob.filterByInertia = false;
    pDefaultBlob.blobColor = 0;  // 0 to extract dark blobs and 255 to extract light blobs
    pDefaultBlob.minArea = 10;   // pixels
    pDefaultBlob.maxArea = 5000;
    pDefaultBlob.minCircularity = 0.9f;
    pDefaultBlob.maxCircularity = (float) 1e37;
    pDefaultBlob.minConvexity = 0.95f;
    pDefaultBlob.maxConvexity = (float) 1e37;
    pDefaultBlob.minInertiaRatio = 0.1f;
    pDefaultBlob.maxInertiaRatio = (float) 1e37;
    pDefaultBlob.minThreshold = 10;
    pDefaultBlob.maxThreshold = 220;
    pDefaultBlob.thresholdStep = 5;
    pDefaultBlob.minDistBetweenBlobs = 10;
    pDefaultBlob.minRepeatability = 2;

    // Descriptor array for Blob
    vector<String> typeDesc;

    // Param array for Blob
    vector<SimpleBlobDetector::Params> paramBlob;
    vector<SimpleBlobDetector::Params>::iterator itParmBlob;

    // Color palette - BGR
    vector<Vec3b > palette;
    palette.push_back(Vec3b(220, 248, 255));
    palette.push_back(Vec3b(205, 235, 255));
    palette.push_back(Vec3b(196, 228, 255));
    palette.push_back(Vec3b(173, 222, 255));
    palette.push_back(Vec3b(179, 222, 245));
    palette.push_back(Vec3b(135, 184, 222));
    palette.push_back(Vec3b(140, 180, 210));
    palette.push_back(Vec3b(143, 143, 188));
    palette.push_back(Vec3b(96, 164, 244));
    palette.push_back(Vec3b(32, 165, 218));
    palette.push_back(Vec3b(63, 133, 205));
    palette.push_back(Vec3b(30, 105, 210));
    palette.push_back(Vec3b(19, 69, 139));
    palette.push_back(Vec3b(45, 82, 160));
    palette.push_back(Vec3b(42, 42, 165));
    palette.push_back(Vec3b(0, 0, 128));
    palette.push_back(Vec3b(170, 232, 238));
    palette.push_back(Vec3b(140, 230, 240));
    palette.push_back(Vec3b(107, 183, 189));
    palette.push_back(Vec3b(0, 128, 128));
    palette.push_back(Vec3b(0, 51, 51));
    palette.push_back(Vec3b(31, 56, 70));
    palette.push_back(Vec3b(62, 69, 67));

    // Descritors
    typeDesc.push_back("BLOB");
    paramBlob.push_back(pDefaultBlob);
    paramBlob.back().minThreshold = 55;
    paramBlob.back().maxThreshold = 180;
    paramBlob.back().filterByColor = true;
    paramBlob.back().blobColor = 0;

    // Initialize
    itParmBlob = paramBlob.begin();
    vector<double> desMethCmp;
    Ptr<Feature2D> ptrBlob;

    // Descriptor loop
    vector<String>::iterator itDesc;
    for (itDesc = typeDesc.begin(); itDesc != typeDesc.end(); ++itDesc) {
        if (*itDesc == "BLOB") {
            ptrBlob = SimpleBlobDetector::create(*itParmBlob);
            ++itParmBlob;
        }
        try {
            // We can detect keypoint with detect method
            vector<Rect> zone;
            vector<KeyPoint> keyImg;
            vector<vector<Point> > region;
            Mat desc;
            Mat result(img.rows, img.cols, CV_8UC3);
            if (ptrBlob.dynamicCast<SimpleBlobDetector>() != NULL) {
                Ptr<SimpleBlobDetector> sbd = ptrBlob.dynamicCast<SimpleBlobDetector>();
                sbd->detect(img, keyImg, Mat());
                drawKeypoints(img, keyImg, result);
                int i = 0;
                for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); ++k, ++i) {
                    // circle(InputOutputArray img,Point center,int radius, const Scalar &color, ...)
                    circle(result, k->pt, (int)k->size, Scalar(128, 0, 128));
                }
            }
            // View
            namedWindow(*itDesc, WINDOW_AUTOSIZE);
            imshow(*itDesc, result);
            waitKey(0);
        }
        catch (Exception &e) {
            cout << "Feature : " << *itDesc << "\n";
            cout << e.msg << endl;
        }
    }
    return 0;
}
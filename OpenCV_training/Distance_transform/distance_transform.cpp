#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <exception>

using namespace std;
using namespace cv;

void save_image (string filename, const Mat& mat_image)
{
    string path("./images/");
    path.append(filename);
    path.append(".png");
    try {
        imwrite(path, mat_image);
    } catch(exception& e) {
        cout << e.what() << endl;
    }
}

int main (int argc, char** argv)
{
    // Load the image
    CommandLineParser parser( argc, argv, 
        "{@input | ./images/original/leaf_diseases.png | input image}" );
    Mat src = imread(parser.get<string>("@input"));
    if (src.empty()) {
        cout << "Could not open or find the image!\n";
        cout << "Usage: " << argv[0] << " <input image>\n";
        return EXIT_FAILURE;
    }

    // Show source image
    imshow("Source image", src);
    save_image("Img1_Source_image", src);

    // Change the blackground from black
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            if (src.at<Vec3b>(i,j) == Vec3b(255,255,255)) {
                src.at<Vec3b>(i,j)[0] = 0;
                src.at<Vec3b>(i,j)[1] = 0;
                src.at<Vec3b>(i,j)[2] = 0;
            }
        }
    }

    // Show output image
    // imshow("Black Background Image", src);
    save_image("Img2_Black_Background_Image", src);

    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3,3) <<
                    1, 1,  1,
                    1, -8, 1,   // an approximation of second derivate,
                    1, 1,  1);  // a quite strong kernel

    // Laplacian filtering
    Mat imgLaplacian;
    filter2D(src, imgLaplacian, CV_32F, kernel);

    Mat sharp;
    src.convertTo(sharp, CV_32F);   
    Mat imgResult = sharp - imgLaplacian;

    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    // imshow("Laplace Filtered Image", imgLaplacian);
    // imshow("New Sharped Image", imgResult);
    save_image("Img3_Laplace_Filtered_Image", imgLaplacian);
    save_image("Img4_New_Sharped_Image", imgResult);


    // Create binary image from source image
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    // imshow("Binary Image", bw);
    save_image("Img5_Binary_Image", bw);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    normalize(dist, dist, 0.0, 1.0, NORM_MINMAX);
    imshow("Distance Transform Image", dist);
    // save_image("Img6_Distance_Transform_Image", dist);

    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);

    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    // imshow("Peaks", dist);
    save_image("Img7_Peaks", dist);

    // Create the CV_8U version of the distance image
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);

    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); ++i) {
        drawContours(markers, contours, static_cast<int>(i),
            Scalar(static_cast<int>(i)+1), -1);
    }

    // Draw the background marker
    circle(markers, Point(5,5), 3, Scalar(255), -1);
    // imshow("Markers", markers*10000);
    save_image("Img8_Markers", markers*10000);

    // Perform the watershed algorithm
    watershed(imgResult, markers);

    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);
    // imshow("Markers_v2", mark);
    save_image("Img9_Markers_v2", mark);


    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size())) {
                dst.at<Vec3b>(i,j) = colors[index-1];
            }
        }
    }

    imshow("Final Result", dst);
    save_image("Img0_Final_Result", dst);

    // Pause
    waitKey();

    return EXIT_SUCCESS;
}
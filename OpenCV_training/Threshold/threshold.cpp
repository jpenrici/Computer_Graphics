#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    String imageName = "./images/tree-17.png";
    if (argc > 1) imageName = argv[1];

    Mat image = imread(imageName, IMREAD_COLOR);

    if (image.empty()) {
        std::cout << "Cannot read image: " << imageName << "\n";
        return -1;
    }

    // Grayscale matrix
    Mat grayscale_image(image.size(), CV_8U);

    // Convert BGR to Gray
    cvtColor(image, grayscale_image, CV_BGR2GRAY);

    // Binary image
    Mat binary_image(grayscale_image.size(), grayscale_image.type());

    // Apply thresholding
    threshold(grayscale_image, binary_image, 1, 255, THRESH_BINARY);

    // Show the original
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);

    // Show the results
    namedWindow("Output", WINDOW_AUTOSIZE);
    imshow("Output", binary_image);

    // Save automatically
    // imwrite("Output", binary_image);

    waitKey();

    return 0;
}
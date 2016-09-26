/**
 *  This example shows how to use basic OpenCV functions.
 *
 *  History:
 *
 *      2016-09-21
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char const *argv[]) {
  cv::Mat image;
  image = cv::imread(argv[1], 1);

  if (!image.data) {
    std::cout << "[Error]: No image data!\n" << std::endl;
    return -1;
  }
  cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Display Image", image);

  cv::waitKey(0);

  return 0;
}

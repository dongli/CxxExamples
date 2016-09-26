/**
 *  This example shows how to smooth an image using OpenCV.
 *
 *  History:
 *
 *      2016-09-26
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main(int argc, char const *argv[]) {
  cv::Mat image;
  image = cv::imread(argv[1], 1);

  if (!image.data) {
    std::cout << "[Error]: No image data!\n" << std::endl;
    return -1;
  }

  std::string method = argv[2];

  cv::Mat smoothedImage;

  unsigned short ngbWidthX = 10;
  unsigned short ngbWidthY = 10;

  if (method == "blur") {
    cv::blur(image, smoothedImage, cv::Size(ngbWidthX, ngbWidthY), cv::Point(-1, -1));
  } else if (method == "gaussian") {
    cv::GaussianBlur(image, smoothedImage, cv::Size(ngbWidthX, ngbWidthY), 0, 0);
  } else if (method == "median") {
    cv::medianBlur(image, smoothedImage, 9);
  } else if (method == "bilateral") {
    cv::bilateralFilter(image, smoothedImage, ngbWidthX, ngbWidthX*2, ngbWidthX/2);
  }

  cv::Mat displayImages(image.size().height, image.size().width * 2, CV_8UC3);
  cv::Mat leftImage(displayImages, cv::Rect(0, 0, image.size().width, image.size().height));
  cv::Mat rightImage(displayImages, cv::Rect(image.size().width, 0, image.size().width, image.size().height));

  image.copyTo(leftImage);
  smoothedImage.copyTo(rightImage);

  cv::imshow("Original and Smoothed Image", displayImages);

  cv::waitKey(0);

  return 0;
}

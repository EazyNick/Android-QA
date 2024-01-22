#ifndef PREPROCESSIMAGE_H
#define PREPROCESSIMAGE_H

#include <opencv2/opencv.hpp>

// Function to preprocess the image for better OCR results
cv::Mat preprocessImage(const cv::Mat& src) {
    cv::Mat gray, thresh;
    // Convert the image to grayscale
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // Apply binary thresholding
    cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    return thresh;
}

#endif // PREPROCESSIMAGE_H
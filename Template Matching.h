// TemplateMatching.h
#ifndef TEMPLATE_MATCHER_H
#define TEMPLATE_MATCHER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

std::pair<int, int> findTemplateCenter(const cv::Mat& img, const cv::Mat& templ, double scale, double threshold);

#endif // TEMPLATE_MATCHER_H

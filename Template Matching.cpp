// TemplateMatcher.cpp
#include "Template Matching.h"
#include <iostream>

std::pair<int, int> findTemplateCenter(const cv::Mat& img, const cv::Mat& templ, double scale, double threshold) {

    //cv::Mat resized_img, resized_templ;
    //cv::resize(img, resized_img, cv::Size(), scale, scale);
    //cv::resize(templ, resized_templ, cv::Size(), scale, scale);

    cv::Mat result;
    cv::matchTemplate(img, templ, result, cv::TM_CCOEFF_NORMED);

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    if (maxVal >= threshold) {
        cv::Point matchLoc = maxLoc;
        std::pair<int, int> center(matchLoc.x + templ.cols / 2, matchLoc.y + templ.rows / 2);
        return center;
    }
    else {
        std::cerr << "No match found!" << std::endl;
        return std::make_pair(-1, -1); // Return an invalid point if no match found
    }
}

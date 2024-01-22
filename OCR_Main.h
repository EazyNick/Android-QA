#ifndef OCR_MAIN_H
#define OCR_MAIN_H

#include <opencv2/opencv.hpp>
#include <string>
#include <utility> // For std::pair

// OCR_Main(imagePath, 찾고자하는 targetText, language, ROI관련 x1, y1, width, height)
std::pair<int, int> OCR_Main(const std::string& imagePath, const std::string& targetText, 
	const std::string& language = "kor", int x = 0, int y = 0, int width = 1080, int height = 2400);

#endif // OCR_MAIN_H

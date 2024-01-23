#include "OCR_Main.h"
#include <iostream>
#include "Template Matching.h"

int main() {
    std::pair<int, int> coordinates = OCR_Main("Assets/Test.png", u8"포인");

    if (coordinates.first != -1 && coordinates.second != -1) {
        std::cout << "Performance " << "Coordinates: (" << coordinates.first << ", " << coordinates.second << ")" << std::endl;
    }
    else {
        std::cout << "Error or word not found." << std::endl;
        return 1;
    }

    // 이미지 로드
    cv::Mat img = cv::imread("Assets/test.png", cv::IMREAD_COLOR); // 대상 이미지
    cv::Mat templ = cv::imread("Assets/test2.png", cv::IMREAD_COLOR); // 템플릿 이미지
    double scale = 0.5;
    double threshold = 0.8;

    std::pair<int, int> coordinates2 = findTemplateCenter(img, templ, scale, threshold);

    if (coordinates2.first != -1 && coordinates2.second != -1) {
        std::cout << "Performance " << "Coordinates2: (" << coordinates2.first << ", " << coordinates2.second << ")" << std::endl;
    }
    else {
        std::cout << "Error or word not found2." << std::endl;
        return 1;
    }





    return 0;
}

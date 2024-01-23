//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//int main() {
//    // 이미지 로드
//    cv::Mat img = cv::imread("Assets/test.png", cv::IMREAD_COLOR); // 대상 이미지
//    cv::Mat templ = cv::imread("Assets/test2.png", cv::IMREAD_COLOR); // 템플릿 이미지
//
//    // 이미지나 템플릿이 제대로 로드되지 않은 경우 오류 메시지 출력
//    if (img.empty() || templ.empty()) {
//        std::cout << "Could not read the image files." << std::endl;
//        return 1;
//    }
//
//    // 템플릿 매칭 수행
//    cv::Mat result;
//    cv::matchTemplate(img, templ, result, cv::TM_CCOEFF_NORMED);
//
//    // 최대 유사도 위치 찾기
//    double minVal, maxVal;
//    cv::Point minLoc, maxLoc, matchLoc;
//    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
//
//    // 템플릿 매칭 성공 여부 확인
//    const double threshold = 0.8; // 임계값, 필요에 따라 조정
//    if (maxVal >= threshold) {
//        cv::Point matchLoc = maxLoc;
//        cv::rectangle(img, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), cv::Scalar::all(0), 2, 8, 0);
//        cv::imshow("Matched Image", img);
//    }
//    else {
//        std::cout << "No match found!" << std::endl;
//    }
//
//    // 이미지 사이즈 조정
//    cv::Mat resized_img, resized_templ;
//    double scale = 0.4; // 여기서는 원본 크기의 50%로 줄입니다. 필요에 따라 조정하세요.
//    cv::resize(img, resized_img, cv::Size(), scale, scale);
//    cv::resize(templ, resized_templ, cv::Size(), scale, scale);
//
//    // 결과 이미지 표시
//    cv::imshow("Matched Image", resized_img);
//    cv::waitKey(0);
//
//    return 0;
//}

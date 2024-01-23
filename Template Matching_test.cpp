//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//int main() {
//    // �̹��� �ε�
//    cv::Mat img = cv::imread("Assets/test.png", cv::IMREAD_COLOR); // ��� �̹���
//    cv::Mat templ = cv::imread("Assets/test2.png", cv::IMREAD_COLOR); // ���ø� �̹���
//
//    // �̹����� ���ø��� ����� �ε���� ���� ��� ���� �޽��� ���
//    if (img.empty() || templ.empty()) {
//        std::cout << "Could not read the image files." << std::endl;
//        return 1;
//    }
//
//    // ���ø� ��Ī ����
//    cv::Mat result;
//    cv::matchTemplate(img, templ, result, cv::TM_CCOEFF_NORMED);
//
//    // �ִ� ���絵 ��ġ ã��
//    double minVal, maxVal;
//    cv::Point minLoc, maxLoc, matchLoc;
//    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
//
//    // ���ø� ��Ī ���� ���� Ȯ��
//    const double threshold = 0.8; // �Ӱ谪, �ʿ信 ���� ����
//    if (maxVal >= threshold) {
//        cv::Point matchLoc = maxLoc;
//        cv::rectangle(img, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), cv::Scalar::all(0), 2, 8, 0);
//        cv::imshow("Matched Image", img);
//    }
//    else {
//        std::cout << "No match found!" << std::endl;
//    }
//
//    // �̹��� ������ ����
//    cv::Mat resized_img, resized_templ;
//    double scale = 0.4; // ���⼭�� ���� ũ���� 50%�� ���Դϴ�. �ʿ信 ���� �����ϼ���.
//    cv::resize(img, resized_img, cv::Size(), scale, scale);
//    cv::resize(templ, resized_templ, cv::Size(), scale, scale);
//
//    // ��� �̹��� ǥ��
//    cv::imshow("Matched Image", resized_img);
//    cv::waitKey(0);
//
//    return 0;
//}

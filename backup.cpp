/* OCR 좌표 값 반환 구현 완료
#include "FreeTypeTextRenderer.h"
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <windows.h> // SetConsoleOutputCP 사용
#include "Find_Center.h"

int main() {

    FT_Library ft;
    FT_Face face;

    FreeTypeTextRenderer TextRenderer("D:/SkillUpProject/Assets/NanumBarunGothic-YetHangul.ttf");

    if (!TextRenderer.InitFreeType(ft, face, "D:/SkillUpProject/Assets/NanumBarunGothic-YetHangul.ttf")) { // 폰트 경로를 지정하세요
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Tesseract 초기화
    if (api->Init(NULL, "kor")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // 이미지 불러오기 (OpenCV 사용)
    cv::Mat image = cv::imread("D:/SkillUpProject/Assets/Test.png");
    api->SetImage(image.data, image.cols, image.rows, 3, image.step);

    // 텍스트 인식
    api->Recognize(0);
    std::string utf_text = api->GetUTF8Text();
    std::string text = TextRenderer.UTF8ToANSI(utf_text.c_str());

    // Check if the word "스테이지" is found in the recognized text
    if (utf_text.find(u8"스테이지") != std::string::npos) {
        std::cout << "Find Find Find Find!" << std::endl; // "Found it!"
    }

    tesseract::ResultIterator* ri = api->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;

    // 바운딩 박스 그리기 및 텍스트 표시 (OpenCV 사용)
    if (ri != 0) {
        do {
            int x1, y1, x2, y2;
            ri->BoundingBox(level, &x1, &y1, &x2, &y2);
            cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 2);

            // 인식된 텍스트 추출
            char* word = ri->GetUTF8Text(level);
            std::string text(word);
            delete[] word;

            //좌표값 구하는 곳
            FindCenter findCenterInstance;
            std::pair<int, int> center = findCenterInstance.FindCenterOfStage(text, x1, y1, x2, y2);


            // 텍스트 이미지에 그리기 (사용자 정의 폰트 사용)
            // FreeType을 사용하여 텍스트 이미지에 그리기
            TextRenderer.PutTextFT(image, utf_text, cv::Point(x1, y2 + 24), face, 24, cv::Scalar(255, 255, 255));
            std::cout << text << std::endl;

        } while (ri->Next(level));
    }


    // 이미지 크기 조정
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(), 0.4, 0.4); // 원본 크기의 50%로 조정

    // 이미지 화면에 표시
    cv::imshow("Image with Bounding Boxes and Text", resizedImage);
    cv::waitKey(0);

    // 정리
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    delete ri;
    api->End();

    return 0;
}
*/

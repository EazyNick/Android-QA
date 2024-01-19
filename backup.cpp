/* OCR ��ǥ �� ��ȯ ���� �Ϸ�
#include "FreeTypeTextRenderer.h"
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <windows.h> // SetConsoleOutputCP ���
#include "Find_Center.h"

int main() {

    FT_Library ft;
    FT_Face face;

    FreeTypeTextRenderer TextRenderer("D:/SkillUpProject/Assets/NanumBarunGothic-YetHangul.ttf");

    if (!TextRenderer.InitFreeType(ft, face, "D:/SkillUpProject/Assets/NanumBarunGothic-YetHangul.ttf")) { // ��Ʈ ��θ� �����ϼ���
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Tesseract �ʱ�ȭ
    if (api->Init(NULL, "kor")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // �̹��� �ҷ����� (OpenCV ���)
    cv::Mat image = cv::imread("D:/SkillUpProject/Assets/Test.png");
    api->SetImage(image.data, image.cols, image.rows, 3, image.step);

    // �ؽ�Ʈ �ν�
    api->Recognize(0);
    std::string utf_text = api->GetUTF8Text();
    std::string text = TextRenderer.UTF8ToANSI(utf_text.c_str());

    // Check if the word "��������" is found in the recognized text
    if (utf_text.find(u8"��������") != std::string::npos) {
        std::cout << "Find Find Find Find!" << std::endl; // "Found it!"
    }

    tesseract::ResultIterator* ri = api->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;

    // �ٿ�� �ڽ� �׸��� �� �ؽ�Ʈ ǥ�� (OpenCV ���)
    if (ri != 0) {
        do {
            int x1, y1, x2, y2;
            ri->BoundingBox(level, &x1, &y1, &x2, &y2);
            cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 2);

            // �νĵ� �ؽ�Ʈ ����
            char* word = ri->GetUTF8Text(level);
            std::string text(word);
            delete[] word;

            //��ǥ�� ���ϴ� ��
            FindCenter findCenterInstance;
            std::pair<int, int> center = findCenterInstance.FindCenterOfStage(text, x1, y1, x2, y2);


            // �ؽ�Ʈ �̹����� �׸��� (����� ���� ��Ʈ ���)
            // FreeType�� ����Ͽ� �ؽ�Ʈ �̹����� �׸���
            TextRenderer.PutTextFT(image, utf_text, cv::Point(x1, y2 + 24), face, 24, cv::Scalar(255, 255, 255));
            std::cout << text << std::endl;

        } while (ri->Next(level));
    }


    // �̹��� ũ�� ����
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(), 0.4, 0.4); // ���� ũ���� 50%�� ����

    // �̹��� ȭ�鿡 ǥ��
    cv::imshow("Image with Bounding Boxes and Text", resizedImage);
    cv::waitKey(0);

    // ����
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    delete ri;
    api->End();

    return 0;
}
*/

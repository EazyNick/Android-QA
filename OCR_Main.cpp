#include "OCR_Main.h"
#include "FreeTypeTextRenderer.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <windows.h>
#include "Find_Center.h"
#include <string>
#include <opencv2/opencv.hpp>

cv::Mat preprocessImage(const cv::Mat& src) {
    cv::Mat gray, thresh;
    // Convert to grayscale
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // Apply thresholding
    cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    return thresh;
}

std::pair<int, int> OCR_Main(const std::string& imagePath, const std::string& targetText, const std::string& language
, int x, int y, int width, int height) {
    FT_Library ft;
    FT_Face face;
    FreeTypeTextRenderer TextRenderer("Assets/NanumBarunGothic-YetHangul.ttf");

    if (!TextRenderer.InitFreeType(ft, face, "Assets/NanumBarunGothic-YetHangul.ttf")) {
        return std::make_pair(-1, -1); // Error in initializing, return invalid coordinates
    }

    SetConsoleOutputCP(CP_UTF8);
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    if (api->Init(NULL, language.c_str())) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    // Define the ROI (x, y, width, height)
    //int x2 = 
    //int y2 = 
    
    //cv::Rect roi(160, 300, 730, 300); // Example coordinates
    cv::Rect roi(x, y, width, height);
    cv::Mat cropped_img = cv::imread(imagePath);
    cv::Mat image = cropped_img(roi);
    // Pass the cropped image to Tesseract
    preprocessImage(image);

    api->SetImage(image.data, image.cols, image.rows, 3, image.step);
    api->Recognize(0);

    std::string utf_text = api->GetUTF8Text();
    std::string text = TextRenderer.UTF8ToANSI(utf_text.c_str());

    std::cout << "Find All Text : " << utf_text << std::endl;
    //std::cout << "Text : " << text << std::endl;

    tesseract::ResultIterator* ri = api->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    std::pair<int, int> center(-1, -1); // Initialize with invalid coordinates


    if (text.find(targetText) != std::string::npos) {
        std::cout << "Find Text : " << text << std::endl;
    }


    if (ri != 0) {
        do {
            const char* word = ri->GetUTF8Text(level);
            std::string text(word);
            delete[] word;

            if (text.find(targetText) != std::string::npos) {
                std::cout << "Find Text : " << targetText << std::endl;

                int x1, y1, x2, y2;
                ri->BoundingBox(level, &x1, &y1, &x2, &y2);
                std::cout << "Coordinates: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;

                // If you need the center of the bounding box
                int centerX = (x1 + x2) / 2;
                int centerY = (y1 + y2) / 2;
                std::cout << "Center: (" << centerX << ", " << centerY << ")" << std::endl;

                break; // Break if you only want the first occurrence
            }

        } while (ri->Next(level));
    }

    //if (ri != 0) {
    //    do {
    //        int x1, y1, x2, y2;
    //        ri->BoundingBox(level, &x1, &y1, &x2, &y2);
    //        char* word = ri->GetUTF8Text(level);
    //        text = std::string(word);
    //        delete[] word;

    //        FindCenter findCenterInstance;
    //        center = findCenterInstance.FindCenterOfStage(text, x1, y1, x2, y2);

    //        // Break if the desired word is found
    //        if (text.find(targetText) != std::string::npos) {
    //            std::cout << "Find Text : " << text << std::endl;
    //            break;
    //        }

    //    } while (ri->Next(level));
    //}

    // Cleaning up
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    delete ri;
    api->End();

    return center; // Return the found coordinates
}



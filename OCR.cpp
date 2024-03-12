#include "OCR.h"
#include "FreeTypeTextRenderer.h"
#include "Find_Center.h"
#include "PreProcessImage.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

// Main OCR function which processes an image to find a given text and returns its center coordinates
std::pair<int, int> OCR_Main(const std::string& imagePath, const std::string& targetText, const std::string& language, int x, int y, int width, int height) {
    // Initialize FreeType library for text rendering
    FT_Library ft;
    FT_Face face;
    FreeTypeTextRenderer TextRenderer("Assets/NanumBarunGothic-YetHangul.ttf");

    // If FreeType initialization fails, return invalid coordinates
    if (!TextRenderer.InitFreeType(ft, face, "Assets/NanumBarunGothic-YetHangul.ttf")) {
        return std::make_pair(-1, -1);
    }

    // Set console output to UTF-8 to support Unicode characters
    SetConsoleOutputCP(CP_UTF8);
    // Initialize Tesseract API
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // If Tesseract initialization fails, print an error and exit
    if (api->Init(NULL, language.c_str())) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Define the ROI based on input parameters
    cv::Rect roi(x, y, width, height);
    // Load the image from the given path
    cv::Mat cropped_img = cv::imread(imagePath);
    // Crop the image to the specified ROI
    cv::Mat image = cropped_img(roi);
    // Preprocess the cropped image for better OCR results
    preprocessImage(image);

    // Set the preprocessed image data for Tesseract OCR
    api->SetImage(image.data, image.cols, image.rows, 3, image.step);
    // Perform OCR on the image
    api->Recognize(0);

    // Get the recognized text as UTF-8
    std::string utf_text = api->GetUTF8Text();
    // Convert UTF-8 text to ANSI encoding
    std::string text = TextRenderer.UTF8ToANSI(utf_text.c_str());

    // Output all recognized text for debugging
    std::cout << "Find All Text : " << utf_text << std::endl;

    // Initialize result iterator to iterate over recognized words
    tesseract::ResultIterator* ri = api->GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    // Initialize the center coordinate pair with invalid values
    std::pair<int, int> center(-1, -1);

    // If the target text is found in the recognized text
    if (text.find(targetText) != std::string::npos) {
        std::cout << "Find Text : " << text << std::endl;
    }

    // Iterate over recognized words to find the target text and its coordinates
    if (ri != 0) {
        do {
            const char* word = ri->GetUTF8Text(level);
            std::string text(word);
            delete[] word;

            // If the current word matches the target text
            if (text.find(targetText) != std::string::npos) {
                std::cout << "Find Text : " << targetText << std::endl;

                // Get the bounding box for the current word
                int x1, y1, x2, y2;
                ri->BoundingBox(level, &x1, &y1, &x2, &y2);
                std::cout << "Coordinates: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;

                // Calculate the center point of the bounding box
                int centerX = (x1 + x2) / 2;
                int centerY = (y1 + y2) / 2;
                std::cout << "Center: (" << centerX << ", " << centerY << ")" << std::endl;

                center.first = centerX;
                center.second = centerY;

                // If only the first occurrence is needed, break after finding it
                break;
            }

        } while (ri->Next(level)); // Continue to the next word
    }

    // Clean up resources
    //FT_Done_Face(face);
    //FT_Done_FreeType(ft);
    delete ri;
    api->End();

    // Return the center coordinates of the found text
    return center;
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


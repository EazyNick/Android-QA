#ifndef FREETYPE_TEXT_RENDERER_H
#define FREETYPE_TEXT_RENDERER_H

#include <string>
#include <opencv2/opencv.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class FreeTypeTextRenderer {
public:
    FreeTypeTextRenderer(const std::string& fontPath);
    ~FreeTypeTextRenderer();
    void PutTextFT(cv::Mat& img, const std::string& text, cv::Point pos, FT_Face& face, int fontSize, cv::Scalar color);
    bool InitFreeType(FT_Library& ft, FT_Face& face, const char* fontPath);
    char* UTF8ToANSI(const char* pszCode);

private:
    FT_Library ft;
    FT_Face face;
    //bool InitFreeType(FT_Library& ft, FT_Face& face, const char* fontPath);
    //char* UTF8ToANSI(const char* pszCode);
};

#endif // FREETYPE_TEXT_RENDERER_H

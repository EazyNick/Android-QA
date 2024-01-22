#include "FreeTypeTextRenderer.h"
#include <windows.h>
#include <OleAuto.h>

// FreeType 초기화 및 폰트 로드 함수
bool FreeTypeTextRenderer::InitFreeType(FT_Library & ft, FT_Face & face, const char* fontPath) {
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Could not init freetype library" << std::endl;
        return false;
    }

    if (FT_New_Face(ft, fontPath, 0, &face)) {
        std::cerr << "Could not open font" << std::endl;
        return false;
    }

    return true;
}

FreeTypeTextRenderer::FreeTypeTextRenderer(const std::string& fontPath) {
    if (!InitFreeType(ft, face, fontPath.c_str())) {
        throw std::runtime_error("Could not initialize the FreeType library or open the font.");
    }
}

FreeTypeTextRenderer::~FreeTypeTextRenderer() {
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

// FreeType을 사용하여 이미지에 텍스트 렌더링
void FreeTypeTextRenderer::PutTextFT(cv::Mat& img, const std::string& text, cv::Point pos, FT_Face& face, int fontSize, cv::Scalar color) {
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    int x = pos.x;
    int y = pos.y;

    for (char c : text) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        FT_GlyphSlot g = face->glyph;

        // 글리프가 비어 있는 경우 건너뛰기
        if (g->bitmap.width == 0 || g->bitmap.rows == 0) {
            x += g->advance.x >> 6; // x 좌표만 업데이트
            continue;
        }

        cv::Mat glyphImg(cv::Size(g->bitmap.width, g->bitmap.rows), CV_8UC1, g->bitmap.buffer, g->bitmap.pitch);

        cv::Mat glyphAlpha;
        cv::cvtColor(glyphImg, glyphAlpha, cv::COLOR_GRAY2BGRA);

        for (int i = 0; i < glyphAlpha.rows; ++i) {
            for (int j = 0; j < glyphAlpha.cols; ++j) {
                uchar pix = glyphAlpha.at<uchar>(i, j);
                if (pix > 0) {
                    int px = x + j + g->bitmap_left;
                    int py = y - i - g->bitmap_top + fontSize;
                    if (px >= 0 && px < img.cols && py >= 0 && py < img.rows) {
                        cv::Vec4b& pixel = img.at<cv::Vec4b>(py, px);
                        pixel[0] = color[0];
                        pixel[1] = color[1];
                        pixel[2] = color[2];
                    }
                }
            }
        }

        x += g->advance.x >> 6;
        y += g->advance.y >> 6;
    }
}

// 한글 사용을 위한 ANSI 형태 변환 함수
char* FreeTypeTextRenderer::UTF8ToANSI(const char* pszCode)
{
    BSTR    bstrWide;
    char* pszAnsi;
    int     nLength;

    // Get nLength of the Wide Char buffer
    nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1,
        NULL, NULL);
    bstrWide = SysAllocStringLen(NULL, nLength);

    // Change UTF-8 to Unicode (UTF-16)
    MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

    // Get nLength of the multi byte buffer
    nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
    pszAnsi = new char[nLength];

    // Change from unicode to mult byte
    WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
    SysFreeString(bstrWide);

    return pszAnsi;
}

// Implement InitFreeType, PutText, and UTF8ToANSI methods here.


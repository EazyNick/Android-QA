#include "FreeTypeTextRenderer.h"

// ... other methods ...

// Implement the FindCenterOfStage function
std::pair<int, int> FreeTypeTextRenderer::FindCenterOfStage(const std::string& text, int x1, int y1, int x2, int y2) {
    if (text.find(u8"스테이지") != std::string::npos) {
        int centerX = (x1 + x2) / 2;
        int centerY = (y1 + y2) / 2;
        return { centerX, centerY };
    }
    return { -1, -1 }; // Return invalid coordinates if "스테이지" is not found
}

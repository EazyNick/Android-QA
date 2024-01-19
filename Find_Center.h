#ifndef FIND_CENTER_H
#define FIND_CENTER_H

#include <string>
#include <utility>

class FindCenter {
public:
    FindCenter() {}
    ~FindCenter() {}

    std::pair<int, int> FindCenterOfStage(const std::string& text, int x1, int y1, int x2, int y2) {
        if (text.find(u8"스테이지") != std::string::npos) {
            int centerX = (x1 + x2) / 2;
            int centerY = (y1 + y2) / 2;
            std::cout << "Axis Click" << centerX << ',' << centerY << std::endl;
            return { centerX, centerY };
        }
        return { -1, -1 }; // Return invalid coordinates if not found
    }
};

#endif // FIND_CENTER_H

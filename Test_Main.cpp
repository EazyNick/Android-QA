#include "OCR_Main.h"
#include <iostream>

int main() {
    std::pair<int, int> coordinates = OCR_Main("Assets/Test.png", u8"Æ÷ÀÎ");

    if (coordinates.first != -1 && coordinates.second != -1) {
        std::cout << "Coordinates: (" << coordinates.first << ", " << coordinates.second << ")" << std::endl;
    }
    else {
        std::cout << "Error or word not found." << std::endl;
    }

    return 0;
}

#include <iostream>
#include "BMPReader.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: drawBmp.exe <path to BMP file>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    BMPReader bmpReader;

    bmpReader.createBMP("test.bmp");
    if (bmpReader.openBMP(fileName)) {
        bmpReader.displayBMP();
        bmpReader.closeBMP();
    }

    return 0;
}

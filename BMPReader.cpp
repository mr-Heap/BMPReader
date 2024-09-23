//
// Created by marina on 23.09.24.
//

#include <iostream>
#include "BMPReader.h"

bool BMPReader::openBMP(const std::string &fileName) {
    file.open(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Can't open file: " << fileName << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    if (fileHeader.signature != 0x4D42) {
        std::cerr << "File is not *.bmp: " << fileName << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.bitCount != 24 && infoHeader.bitCount != 32) {
        std::cerr << "Not 24-bit or 32-bit" << std::endl;
        return false;
    }

    file.seekg(fileHeader.dataOffset, std::ios::beg);

    int rowSize = (infoHeader.width * (infoHeader.bitCount / 8) + 3) & (~3);
    int dataSize = rowSize * abs(infoHeader.height);
    pixelData.resize(dataSize);

    file.read(reinterpret_cast<char*>(pixelData.data()), dataSize);

    return true;
}

void BMPReader::displayBMP() {
    if (pixelData.empty()) {
        std::cerr << "No image data to display" << std::endl;
        return;
    }

    char blackPixel = '*';
    char whitePixel = ' ';

    int rowSize = (infoHeader.width * (infoHeader.bitCount / 8) + 3) & (~3);

    for (int y = 0; y < abs(infoHeader.height); ++y) {
        unsigned char* rowData = pixelData.data() + (abs(infoHeader.height) - 1 - y) * rowSize;
        for (int x = 0; x < infoHeader.width; ++x) {
            unsigned char* pixel = rowData + x * (infoHeader.bitCount / 8);

            unsigned char blue = pixel[0];
            unsigned char green = pixel[1];
            unsigned char red = pixel[2];

            if (red == 255 && green == 255 && blue == 255) {
                std::cout << whitePixel;
            }
            else if (red == 0 && green == 0 && blue == 0) {
                std::cout << blackPixel;
            }
            else {
                std::cerr << "Image includes unsupported colors" << std::endl;
                return;
            }
        }
        std::cout << std::endl;
    }
}

void BMPReader::createBMP(const std::string &fileName) {
    std::ofstream file(fileName, std::ios::binary);

    if (!file) {
        std::cerr << "Can't open file for writing" << std::endl;
        return;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    int width = infoHeader.width;
    int height = infoHeader.height;
    int rowPadding = (4 - (width * 3) % 4) % 4;
    int dataSize = (width * 3 + rowPadding) * height;

    fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + dataSize;

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

//    chess board being drawn
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((x + y) % 2 == 0) {
                unsigned char black[3] = { 0, 0, 0 };
                file.write(reinterpret_cast<const char*>(black), 3);
            } else {
                unsigned char white[3] = { 255, 255, 255 };
                file.write(reinterpret_cast<const char*>(white), 3);
            }
        }
        unsigned char padding[3] = { 0, 0, 0 };
        file.write(reinterpret_cast<const char*>(padding), rowPadding);
    }

    file.close();
}

void BMPReader::closeBMP() {
    if (file.is_open()) {
        file.close();
    }
}

BMPReader::~BMPReader() {
    closeBMP();
}

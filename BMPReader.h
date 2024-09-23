//
// Created by marina on 23.09.24.
//
#pragma once

#include <fstream>
#include <string>
#include <vector>

#pragma pack(push, 1) // align

struct BMPFileHeader {
    uint16_t signature = 0x4D42;
    uint32_t fileSize = 0;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t dataOffset = 54;
};

struct BMPInfoHeader {
    uint32_t size = 40;
    int32_t width = 10;
    int32_t height = 10;
    uint16_t planes = 1;
    uint16_t bitCount = 24;
    uint32_t compression = 0;
    uint32_t sizeImage = 0;
    int32_t XpixelsPerMeter = 0;
    int32_t YpixelsPerMeter = 0;
    uint32_t colorsUsed = 0;
    uint32_t colorsImportant = 0;
};
#pragma pack(pop) // disable alignment

class BMPReader {
private:
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::ifstream file;
    std::vector<unsigned char> pixelData;

public:

    /**
    * Opens and reads a BMP file.
    *
    * @param fileName The name of the BMP file to open.
    * @return True if the BMP file was successfully opened and read, false otherwise.
    *
    * The method supports 24-bit and 32-bit BMP files.
    */
    bool openBMP(const std::string& fileName);

    /**
    * Displays the BMP image in the console.
    *
    * The image is displayed using '*' for black pixels and ' ' for white pixels.
    *
    */
    void displayBMP();

    /**
    * Creates a new BMP file with a simple black and white pattern.
    *
    * @param fileName The name of the BMP file to create.
    *
    */
    void createBMP(const std::string& fileName);

    /**
    * Closes the BMP file and frees any allocated memory.
    *
    *
    * It should be called after finishing reading the BMP file.
    * If no file is open or no data is allocated, this method does nothing.
    */
    void closeBMP();

    /**
    * Destructor that ensures the BMP file is closed and memory is freed.
    *
    */
    ~BMPReader();
};

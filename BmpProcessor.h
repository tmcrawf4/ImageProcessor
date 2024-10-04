#ifndef IMAGEPROCESSING_BMPPROCESSOR_H
#define IMAGEPROCESSING_BMPPROCESSOR_H
#include "PixelProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BmpHeader {
    char magicNumber[2];
    int size;
    short reserve1;
    short reserve2;
    int offsetPixel;
};
struct DibHeader {
    int size;
    int width;
    int height;
    short plane;
    short bitsPerPixel;
    int compress;
    int imageSize;
    int xPixels;
    int yPixels;
    int colors;
    int importantColors;
};

struct BmpHeader *initialBMPHeader();
struct DibHeader *initialDIBHeader();

void readBMPHeader(FILE* file, struct BmpHeader* header);

void writeBMPHeader(FILE* file, struct BmpHeader* header);

void readDIBHeader(FILE* file, struct DibHeader* header);

void writeDIBHeader(FILE* file, struct DibHeader* header);

void makeBMPHeader(struct BmpHeader* header, int width, int height);

void makeDIBHeader(struct DibHeader* header, int width, int height);

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

#endif //IMAGEPROCESSING_BMPPROCESSOR_H
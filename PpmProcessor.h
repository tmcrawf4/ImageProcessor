#ifndef PPMPROCESSOR_H
#define PPMPROCESSOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "PixelProcessor.h"

struct PpmHeader{
    char magicNumber[3];
    unsigned width;
    unsigned height;
    unsigned maxVal;
};

struct PpmHeader* ppmStart();

void readPPMHeader(FILE* file, struct PpmHeader* header);

void writePPMHeader(FILE* file, struct PpmHeader* header);

void makePPMHeader(struct PpmHeader* header, int width, int height);

void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height);

void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height);
#endif //IMAGEPROCESSING_PPMPROCESSOR_H
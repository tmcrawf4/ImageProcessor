#ifndef PIXELPROCESSOR_H
#define PIXELPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Pixel* firstPixel();

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift);

#endif //IMAGEPROCESSING_PIXELPROCESSOR_H

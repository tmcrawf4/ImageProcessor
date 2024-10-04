#include "PixelProcessor.h"

struct Pixel* firstPixel(){
    struct Pixel *pixelMem = calloc(1, sizeof*pixelMem);
    return pixelMem;
}
void colorShiftPixels(struct Pixel **pArr, int width, int height, int rShift, int gShift, int bShift) {
    struct Pixel *currentPixel = *pArr;

    for (int yIMage = 0; yIMage < height; yIMage++) {
        for (int xImage = 0; xImage < width; xImage++) {
            int counter = yIMage * width + xImage;

            if (rShift != 0) {
                int redVal = currentPixel[counter].r + rShift;
                currentPixel[counter].r = (unsigned char)((redVal > 255) ? 255 : (redVal < 0) ? 0 : redVal);
            }
            if (gShift != 0) {
                int greenVal = currentPixel[counter].g + gShift;
                currentPixel[counter].g = (unsigned char)((greenVal > 255) ? 255 : (greenVal < 0) ? 0 : greenVal);
            }
            if (bShift != 0) {
                int blueVal = currentPixel[counter].b + bShift;
                currentPixel[counter].b = (unsigned char)((blueVal > 255) ? 255 : (blueVal < 0) ? 0 : blueVal);
            }
        }
    }
}

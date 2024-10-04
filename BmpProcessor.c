/**
* This file implements the BMP header structs read and write functionality
* and includes a makeHeader for file conversions
*
* Completion time: 14 hours
*
* @author Tristan Crawford, Suthar
* @version CLion 2023.2
*
*/
#include "BmpProcessor.h"

struct BmpHeader *initialBMPHeader() {
    struct BmpHeader *pixBMP = calloc(1, sizeof *pixBMP);
    return pixBMP;
}

struct DibHeader *initialDIBHeader() {
    struct DibHeader *pixDIB = calloc(1, sizeof *pixDIB);
    return pixDIB;
}

void readBMPHeader(FILE *file, struct BmpHeader *header) {
    fread(&header->magicNumber, sizeof(char) * 2, 1, file);
    fread(&header->size, sizeof(int), 1, file);
    fread(&header->reserve1, sizeof(short), 1, file);
    fread(&header->reserve2, sizeof(short), 1, file);
    fread(&header->offsetPixel, sizeof(int), 1, file);
}

void writeBMPHeader(FILE *file, struct BmpHeader *header) {

    fwrite(&header->magicNumber, sizeof(char) * 2, 1, file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserve1, sizeof(short), 1, file);
    fwrite(&header->reserve2, sizeof(short), 1, file);
    fwrite(&header->offsetPixel, sizeof(int), 1, file);
}

void readDIBHeader(FILE *file, struct DibHeader *header) {

    fread(&header->size, sizeof(int), 1, file);
    fread(&header->width, sizeof(int), 1, file);
    fread(&header->height, sizeof(int), 1, file);
    fread(&header->plane, sizeof(short), 1, file);
    fread(&header->bitsPerPixel, sizeof(short), 1, file);
    fread(&header->compress, sizeof(int), 1, file);
    fread(&header->imageSize, sizeof(int), 1, file);
    fread(&header->xPixels, sizeof(int), 1, file);
    fread(&header->yPixels, sizeof(int), 1, file);
    fread(&header->colors, sizeof(int), 1, file);
    fread(&header->importantColors, sizeof(int), 1, file);

}
void writeDIBHeader(FILE *file, struct DibHeader *header) {
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->width, sizeof(int), 1, file);
    fwrite(&header->height, sizeof(int), 1, file);
    fwrite(&header->plane, sizeof(short), 1, file);
    fwrite(&header->bitsPerPixel, sizeof(short), 1, file);
    fwrite(&header->compress, sizeof(int), 1, file);
    fwrite(&header->imageSize, sizeof(int), 1, file);
    fwrite(&header->xPixels, sizeof(int), 1, file);
    fwrite(&header->yPixels, sizeof(int), 1, file);
    fwrite(&header->colors, sizeof(int), 1, file);
    fwrite(&header->importantColors, sizeof(int), 1, file);

}
void makeBMPHeader(struct BmpHeader *header, int width, int height) {
    struct BmpHeader *bmpHead = header;
    bmpHead->magicNumber[0] = 'B';
    bmpHead->magicNumber[1] = 'M';
    bmpHead->size = header->offsetPixel + width * height * 24 / 8;
    bmpHead->reserve1 = 0;
    bmpHead->reserve2 = 0;
    bmpHead->offsetPixel = 54;
}

void makeDIBHeader(struct DibHeader *header, int width, int height) {
    struct DibHeader *dibHead = header;
    dibHead->size = sizeof *dibHead;
    dibHead->width = width;
    dibHead->height = height;
    dibHead->plane = 1;
    dibHead->bitsPerPixel = 24;
    dibHead->compress = 0;
    dibHead->imageSize = width * height * 24 / 8;
    dibHead->xPixels = 3780;
    dibHead->yPixels = 3780;
    dibHead->colors = 0;
    dibHead->importantColors = 0;
}

void readPixelsBMP(FILE *file, struct Pixel **pArr, int width, int height) {
    int pixelCounter = 0;
    *pArr = (struct Pixel *)malloc(sizeof(struct Pixel) * width * height);
    struct Pixel *tempPix = *pArr;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            fread(&tempPix[pixelCounter].b, sizeof(char), 1, file);
            fread(&tempPix[pixelCounter].g, sizeof(char), 1, file);
            fread(&tempPix[pixelCounter].r, sizeof(char), 1, file);

            pixelCounter++;
        }

    }
}

void writePixelsBMP(FILE *file, struct Pixel **pArr, int width, int height) {
    int pixelCounter = 0;
    struct Pixel *temp = *pArr;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fwrite(&temp[pixelCounter].b, sizeof(char), 1, file);
            fwrite(&temp[pixelCounter].g, sizeof(char), 1, file);
            fwrite(&temp[pixelCounter].r, sizeof(char), 1, file);
            pixelCounter++;
        }
        
    }
}

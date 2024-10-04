/**
* This file implements the PPM header structs read and write functionality
* and includes a makeHeader for file conversions
*
*
* Completion time: 14 hours
*
* @author Tristan Crawford, Suthar
* @version CLion 2023.2
*
*/
#include "PpmProcessor.h"

struct PpmHeader* ppmStart() {

    struct PpmHeader *ppmHead = calloc(1, sizeof*ppmHead);
    return ppmHead;
}

void readPPMHeader(FILE* file, struct PpmHeader* header){
    fscanf(file, "%2s %u %u %u", &header->magicNumber, &header->width, &header->height, &header->maxVal);

    printf("magicNumber: %c%c\n", header->magicNumber[0], header->magicNumber[1]);
    printf("width: %u\n", header->width);
    printf("height: %u\n", header->height);
    printf("maxVal: %u\n", header->maxVal);
}

void writePPMHeader(FILE* file, struct PpmHeader* header){
    fprintf(file, "%2s\n%u %u\n %u\n", header->magicNumber, header->width, header->height, header->maxVal);

}

void makePPMHeader(struct PpmHeader* header, int width, int height){

    struct PpmHeader *makeHeader = header;

    makeHeader->magicNumber[0] = 'P';
    makeHeader->magicNumber[1] = '6';
    makeHeader->height = height;
    makeHeader->width = width;
    makeHeader->maxVal = 225;
    header = makeHeader;

}


void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height){
    int pixelCount = 0;
    struct Pixel* tempPixel = pArr;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++){
            fscanf(file, "%c", &tempPixel[pixelCount].r);
            fscanf(file, "%c", &tempPixel[pixelCount].g);
            fscanf(file, "%c", &tempPixel[pixelCount].b);

            pixelCount++;
        }
        fseek(file, sizeof(unsigned char) * width, SEEK_CUR);
    }
}
void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height){
    int pixCounter = 0;
    struct Pixel* tempPix = pArr;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++){
            pixCounter++;
        }
        fseek(file, sizeof(unsigned char) * width, SEEK_CUR);
    }
}

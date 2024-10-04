/**
* This program will take an image filename provided in the format of PPM or BMP,
* then will transform the image using a color shift in which the resulting file will be saved
* back on the host machine as a viewable BMP or PPM file.
*
* Completion time: 14 hours
*
* @author Tristan Crawford, Suthar
* @version CLion 2023.2
*
*/

////////////////////////////////////////////////////////////////////////////////
#include "BmpProcessor.h"
#include "PpmProcessor.h"
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {

    char *inputFile;
    char *outputFile;
    char *imageType;
    int inputOption;
    int rVal = 0;
    int gVal = 0;
    int bVal = 0;

    int oCheck = 0;
    int rCheck = 0;
    int gCheck = 0;
    int bCheck = 0;
    int tCheck = 0;

    while ((inputOption = getopt(argc, argv, ":i:o:r:g:b::t:")) != -1) {
        switch (inputOption) {
            case 'i':
                inputFile = optarg;
                printf("Input: %s\n", inputFile);
                break;
            case 'o':
                oCheck = 1;
                outputFile = optarg;
                printf("Output: %s\n", outputFile);
                break;
            case 'r':
                rCheck = 1;
                rVal = atoi(optarg);
                break;
            case 'g':
                gCheck = 1;
                gVal = atoi(optarg);
                break;
            case 'b':
                bCheck = 1;
                bVal = atoi(optarg);
                break;
            case 't':
                tCheck = 1;
                imageType = optarg;
                break;
        }
    }
    int fileIn;
    int fileOut;
    int fileType;

    if (inputFile != NULL) {
        fileIn = strlen(inputFile);
        if (fileIn >= 5 && ((strcmp(&inputFile[fileIn - 4], ".bmp") == 0) || (strcmp(&inputFile[fileIn - 4], ".ppm") == 0)) && (access(inputFile, F_OK) != -1)) {
            FILE *fileImport = fopen(inputFile, "r");
            struct Pixel *pixSize = firstPixel();
            int width = 0;
            int height = 0;

            if (strcmp(&inputFile[fileIn - 4], ".bmp") == 0) {
                struct BmpHeader *bmpHeader = initialBMPHeader();
                struct DibHeader *dibHeader = initialDIBHeader();
                readBMPHeader(fileImport, bmpHeader);
                readDIBHeader(fileImport, dibHeader);
                width = dibHeader->width;
                height = dibHeader->height;
                readPixelsBMP(fileImport, pixSize, width, height);
            }
            if (strcmp(&inputFile[fileIn - 4], ".ppm") == 0) {
                struct PpmHeader *ppmHead = ppmStart();
                readPPMHeader(fileImport, ppmHead);
                width = ppmHead->width;
                height = ppmHead->height;
                readPixelsPPM(fileImport, pixSize, width, height);
            }
            if (rCheck == 1 || bCheck == 1 || gCheck == 1) {
                colorShiftPixels(pixSize, width, height, rVal, gVal, bVal);
            }
            if (oCheck == 1) {
                fileOut = strlen(outputFile);
                if (fileOut == 0) {
                    outputFile = strcat(inputFile, "-copy");
                }
                FILE *Export = fopen(outputFile, "w");
                if (tCheck == 1) {
                    fileType = strlen(imageType);
                    if (strcmp(&imageType[fileType - 3], "PPM") == 0) {
                        struct PpmHeader *newPpmHeader = ppmStart();
                        makePPMHeader(newPpmHeader, width, height);
                        writePPMHeader(Export, newPpmHeader);
                        writePixelsPPM(Export, pixSize, width, height);
                    }
                    if (strcmp(&imageType[fileType - 3], "BMP") == 0) {
                        struct BmpHeader *newBMPHeader = initialBMPHeader();
                        struct DibHeader *newDIBHeader = initialDIBHeader();

                        makeBMPHeader(newBMPHeader, width, height);
                        makeDIBHeader(newDIBHeader, width, height);
                        writeBMPHeader(Export, newBMPHeader);
                        writeDIBHeader(Export, newDIBHeader);
                        writePixelsBMP(Export, pixSize, width, height);
                    }
                } else {
                    struct BmpHeader *newBMPHeader = initialBMPHeader();
                    struct DibHeader *newDIBHeader = initialDIBHeader();
                    makeBMPHeader(newBMPHeader, width, height);
                    printf("\nInput Header\n");
                    printf("signature: %c%c\n", newBMPHeader->magicNumber[0], newBMPHeader->magicNumber[1]);
                    printf("size: %d\n", newBMPHeader->size);
                    printf("reserved1: %d\n", newBMPHeader->reserve1);
                    printf("reserved2: %d\n", newBMPHeader->reserve2);
                    printf("offset_pixel_array: %d\n", newBMPHeader->offsetPixel);
                    makeDIBHeader(newDIBHeader, width, height);

                    printf("DIB Header size: %d\n", newDIBHeader->size);
                    printf("Image width: %d\n", newDIBHeader->width);
                    printf("Image height: %d\n", newDIBHeader->height);
                    printf("Planes: %d\n", newDIBHeader->plane);
                    printf("Bits Per Pixel: %d\n", newDIBHeader->bitsPerPixel);
                    printf("Compression: %d\n", newDIBHeader->compress);
                    printf("Image Size: %d\n", newDIBHeader->imageSize);
                    printf("X Resolution: %d\n", newDIBHeader->xPixels);
                    printf("Y Resolution: %d\n", newDIBHeader->yPixels);
                    printf("Colors in color table: %d\n", newDIBHeader->colors);
                    printf("Important color count: %d\n", newDIBHeader->importantColors);

                    writeBMPHeader(Export, newBMPHeader);
                    writeDIBHeader(Export, newDIBHeader);
                    writePixelsBMP(Export, pixSize, width, height);

                }

            }

            exit(1);
        }

        return 0;
    }
}
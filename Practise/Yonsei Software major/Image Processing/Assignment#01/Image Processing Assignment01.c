#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH  512
#define HEIGHT 512
#define BYTE   unsigned char
#define WORD   unsigned short
#define DWORD  unsigned int
#define LONG   int

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;
#pragma pack(pop)

void fillImage(BYTE* image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j <= 100) image[i * width + j] = 120; 
            else if (j < 200) image[i * width + j] = 120 + (BYTE)((j - 100) * (135 - 120) / 100);
            else if (j < 280) image[i * width + j] = 135 + (BYTE)((j - 200) * (225 - 135) / 80);
            else if (j < 300) image[i * width + j] = 225 + (BYTE)((j - 280) * (240 - 225) / 20);
            else image[i * width + j] = 240;
        }
    }
}

void saveRawImage(const char* filename, BYTE* image, int width, int height) {
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filename, "wb");
    if (err != 0 || fp == NULL) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        return;
    }
    fwrite(image, sizeof(BYTE), width * height, fp);
    fclose(fp);
}

void rotateImage(BYTE* image, BYTE* rotatedImage, int width, int height) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            rotatedImage[i * height + j] = image[(height - j - 1) * width + i];
        }
    }
}

void saveAsBmp(const char* filename, BYTE* image, int width, int height) {
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filename, "wb");
    if (err != 0 || fp == NULL) {
        perror("Error opening file");
        return;
    }

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    RGBQUAD palette[256];
    memset(&bfh, 0, sizeof(bfh));
    memset(&bih, 0, sizeof(bih));

    bfh.bfType = 0x4D42; 
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256;
    bfh.bfSize = bfh.bfOffBits + width * height;

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = width;
    bih.biHeight = -height; 
    bih.biPlanes = 1;
    bih.biBitCount = 8;
    bih.biCompression = 0;

    fwrite(&bfh, 1, sizeof(bfh), fp);
    fwrite(&bih, 1, sizeof(bih), fp);

    for (int i = 0; i < 256; ++i) {
        palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = i;
        palette[i].rgbReserved = 0;
    }
    fwrite(palette, 1, sizeof(RGBQUAD) * 256, fp);

    fwrite(image, 1, width * height, fp);
    fclose(fp);
}

int main() {
    BYTE* image = (BYTE*)malloc(WIDTH * HEIGHT);
    BYTE* rotatedImage = (BYTE*)malloc(WIDTH * HEIGHT);
    if (image == NULL || rotatedImage == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fillImage(image, WIDTH, HEIGHT);
    saveRawImage("ramp.raw", image, WIDTH, HEIGHT);
    saveAsBmp("ramp.bmp", image, WIDTH, HEIGHT);

    rotateImage(image, rotatedImage, WIDTH, HEIGHT);
    saveAsBmp("ramp_rotated.bmp", rotatedImage, HEIGHT, WIDTH);

    free(image);
    free(rotatedImage);

    return EXIT_SUCCESS;
}

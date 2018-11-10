#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef unsigned short int WORD;
typedef unsigned __int128 CIEXYZTRIPLE;

/**
 * Структура BMP формата
 */
#pragma pack(push, 1) // Устанавливаем размер выравнивания в 1 байт
typedef struct {
    WORD   bfType;         // "BM"
    int    bfSize;         // размер файла
    int    bfReserved;     // 0
    int    bfOffBits;      // смещение до поля данных
    int    biSize;         // размер струкуры(в байтах)
    int    biWidth;        // ширина
    int    biHeight;       // высота
    WORD   biPlanes;       // всегда должно быть 1
    WORD   biBitCount;     // 1 | 4 | 8 | 16 | 24 | 32
    int    biCompression;  // 0 | 1 | 2 | 3  | 6
    int    biSizeImage;    // Количество байт в поле данных
    int    biXPelsPerMeter;// горизонтальное разрешение
    int    biYPelsPerMeter;// вертикальное разрешение
    int    biClrUsed;      // Количество используемых цветов(если есть таблица цветов)
    int    biClrImportant; // Количество существенных цветов(0)

    //If version 4:
    int bvRedMask;
    int bvGreenMask;
    int bvBlueMask;
    int bvAlphaMask;
    int bvCSType;
    CIEXYZTRIPLE bvEndpoints;
    CIEXYZTRIPLE bvEndpoints2;
    int bvGammaRed;
    int bvGammaGreen;
    int bvGammaBlue;

    //If version 5:
    int bvIntent;
    int bvProfileData;
    int bvProfileSize;
    int bvReserved;

} BMPHeader;
#pragma pack(pop)

void FPUTC(int, FILE*);

// Обработка различных форматов BMP, в зависимости от количества бит на пиксель

void BMP4(FILE*, FILE*, int, int, int);

void BMP8(FILE*, FILE*, int, int, int);

void BMP16_5_5_5(FILE*, FILE*, int, int, int, int, int);

void BMP16_5_6_5(FILE*, FILE*, int, int, int, int);

void BMP24(FILE*, FILE*, int, int, int);

void BMP32(FILE*, FILE*, int, int, int);
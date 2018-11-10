#include "BMP.h"

/**
 * Структура пикселя формата RGB с 16 бит на пиксель(5-5-5-1)
 */
struct RGBBIT555 {
    unsigned short rgbBlue: 5;
    unsigned short rgbGreen: 5;
    unsigned short rgbRed: 5;
    unsigned short rgbAlpha: 1;
} BIT555;

/**
 * Пиксель
 */
union {
    struct RGBBIT555 BIT555 ;
    WORD RGB555;
} pixel;

/**
 * BMP обработичк для 16 бит на пиксель(5-5-5-1)
 * @param input входящий bmp файл
 * @param output результирующий файл
 * @param bfOffBits смещение до поля данных
 * @param sizeStruct размер структуры
 * @param bfSize размер файла
 * @param biSize размер структуры
 * @param gradient величина относительно которой строятся черно/белые цвета
 */
void BMP16_5_5_5(FILE *input, FILE *output, int bfOffBits , int sizeStruct, int bfSize, int biSize, int gradient) {
    unsigned int median;

    // Пропускаем заголовок файла, так как он уже был записан в функции main
    fseek( input , sizeStruct + 14 , SEEK_SET );

    // Считывание информационного поля
    for (int i = 0; i < bfOffBits - sizeStruct - 14; i++) {
        fputc(fgetc(input), output);
    }

    // Считывание пикселей
    for (int i = 0; i < bfSize - biSize - 14; i++) {
        fread(&pixel.RGB555, 1, 2, input);

        // Преобразование в монохром
        median = pixel.RGB555 / 67;
        if (median > gradient) {
            pixel.BIT555.rgbGreen = 31;
            pixel.BIT555.rgbRed = 31;
            pixel.BIT555.rgbBlue = 31;
            fwrite(&pixel.BIT555, 1, 2, output);
        } else {
            pixel.BIT555.rgbGreen = 0;
            pixel.BIT555.rgbRed = 0;
            pixel.BIT555.rgbBlue = 0;
            fwrite(&pixel.BIT555, 1, 2, output);

        }
    }
}


#include "BMP.h"

/**
 * Структура пикселя формата RGB с 16 бит на пиксель(5-6-5)
 */
struct RGBBIT5_6_5 {
    unsigned short rgbBlue: 5;
    unsigned short rgbGreen: 6;
    unsigned short rgbRed: 5;
} BIT565;

/**
 * Пиксель
 */
union {
    struct RGBBIT5_6_5 BIT565 ;
    WORD RGB565;
} pixel;

/**
 * BMP обработичк для 16 бит на пиксель(5-6-5)
 * @param input входящий bmp файл
 * @param output результирующий файл
 * @param bfOffBits смещение до поля данных
 * @param sizeStruct размер структуры
 * @param biSizeImage количество байт в поле данных
 * @param gradient величина относительно которой строятся черно/белые цвета
 */
void BMP16_5_6_5(FILE *input, FILE *output, int bfOffBits ,int sizeStruct, int biSizeImage, int gradient) {
    unsigned int median;

    // Пропускаем заголовок файла, так как он уже был записан в функции main
    fseek(input, sizeStruct + 14, SEEK_SET);

    // Считывание информационного поля
    for (int i = 0; i < bfOffBits - sizeStruct - 14; i++) {
        fputc(fgetc(input), output);
    }

    // Считывание пикселей
    for (int i = 0; i < biSizeImage; i++) {
        fread(&pixel.RGB565, 1, 2, input);

        // Преобразование в монохром
        median = pixel.RGB565 / 80;
        if (median > gradient) {
            pixel.BIT565.rgbGreen = 63;
            pixel.BIT565.rgbRed = 31;
            pixel.BIT565.rgbBlue = 31;
            fwrite(&pixel.BIT565, 1, 2, output);
        } else {
            pixel.BIT565.rgbGreen = 0;
            pixel.BIT565.rgbRed = 0;
            pixel.BIT565.rgbBlue = 0;
            fwrite(&pixel.BIT565, 1, 2, output);
        }
    }

}

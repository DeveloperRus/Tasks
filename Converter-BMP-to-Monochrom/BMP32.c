#include "BMP.h"

/**
 * Структура пикселя формата RGB с 32 бит на пиксель
 */
typedef struct {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserv;
} RGB32;

/**
 * BMP обработичк для 32 бит на пиксель
 * @param input входящий bmp файл
 * @param output результирующий файл
 * @param sizeStruct размер структуры
 * @param biSizeImage количество байт в поле данных
 * @param gradient величина относительно которой строятся черно/белые цвета
 */
void BMP32(FILE *input, FILE *output,int sizeStruct,  int biSizeImage, int gradient) {
    unsigned int median;
    RGB32* palette, * pixel;

    // Пропускаем заголовок файла, так как он уже был записан в функции main
    fseek(input, sizeStruct + 14, SEEK_SET);

    // Считывание пикселей
    for (int i = 0; i < biSizeImage; i++) {
        fread(&palette, 1, sizeof(RGB32), input);

        // Преобразование в монохром
        pixel = &palette;
        median = pixel->rgbBlue + pixel->rgbGreen + pixel->rgbRed;
        if (median > gradient) {
            fputc(255, output);
            fputc(255, output);
            fputc(255, output);
            fputc(pixel->rgbReserv, output);
        } else {
            fputc(0, output );
            fputc(0, output);
            fputc(0, output);
            fputc(pixel->rgbReserv, output);
        }
    }
}


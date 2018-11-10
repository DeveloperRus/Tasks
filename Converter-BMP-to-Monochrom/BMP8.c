#include "BMP.h"

/**
 * BMP обработичк для 8 бит на пиксель (используется таблица цветов)
 * @param input входящий bmp файл
 * @param output результирующий файл
 * @param sizeStruct размер структуры (смещение до поля данных)
 * @param bfSize размер файла
 * @param gradient величина относительно которой строятся черно/белые цвета
 */
void BMP8(FILE* input, FILE* output, int sizeStruct, int bfSize, int gradient ) {
    unsigned int red, green, blue, alpha;

    for (int i = 0; i < 256; i++) {
        // Установка указателей на ячейку в таблице цветов
        fseek(output, sizeStruct + 14 + i * 4, SEEK_SET);
        fseek(input, sizeStruct + 14 + i * 4, SEEK_SET);

        // Считывание каналов RGB этой ячейки
        red = fgetc(input);
        green = fgetc(input);
        blue = fgetc(input);
        alpha = fgetc(input);

        // Преобразование в монохром
        if (red + green + blue > gradient) {
            FPUTC(255, output);
            fputc(255, output);
        } else {
            FPUTC(0, output);
            fputc(0, output);
        }
    }
    // Установление указателй на пиксели, цвет которых задается
    // указателем на ячейку в таблице цветов
    fseek(output, 1078, SEEK_SET);
    fseek(input, 1078, SEEK_SET);

    // Запись данных с этой позиции из input в output
    for (int i = 0; i < bfSize - 1078; i++) {
        fputc(fgetc(input), output);
    }
}
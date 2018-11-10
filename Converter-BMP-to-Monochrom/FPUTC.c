#include "BMP.h"

/**
 * Запись в файл значения всех трех каналов RGB
 * (Установление цвета пикселя)
 * @param argument значение каналов
 * @param output файл
 */
void FPUTC(int argument, FILE* output) {
    fputc(argument, output); // Red
    fputc(argument, output); // Green
    fputc(argument, output); // Blue
}
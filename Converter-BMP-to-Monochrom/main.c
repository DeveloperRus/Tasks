#include "BMP.h"

// Формат аргументов
const char* FORMATINPUT = "--input=";
const char * FORMATOUTPUT = "--output=";
const char * FORMATBMP = ".bmp";

void main(int argc, char *argv[]) {
    int sizeStruct;   // Размер заголовка
    BMPHeader header; // Структура заголовка
    char * fileIn, * fileOut; // Имена входного и выходного файла

    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Not all parameters have been entered");
        exit(1);
    }

    // Проверка формата ввода
    for (int i = 1; i < 3; i++) {
        if (strstr(argv[i], FORMATINPUT) != NULL) {
            fileIn = strchr(argv[i], '=') + 1;
        }
        else if (strstr(argv[i], FORMATOUTPUT) != NULL) {
            fileOut = strchr(argv[i], '=') + 1;
        }
        else {
            printf("The %d argument have not right format", i);
            exit(1);
        }
    }
    if (strstr(fileOut, FORMATBMP) == NULL) {
        printf("Don't right format output");
        exit(1);
    }

    FILE* input = fopen(fileIn, "rb"); // Отркытие входного файла

    if (input == NULL) {
        printf("Don't exist file");
        exit(1);
    }

    //Считываем файл в структуру
    fseek( input , 14 , SEEK_SET );
    fread( &sizeStruct, 1, 4, input );
    fseek(input, 0 , SEEK_SET );
    fread( &header, 1, sizeStruct+14, input );

    // Проверка формата файла
    if (header.bfType != 19778) {
        printf("Format is not BMP");
        exit(1);
    }

    FILE* output = fopen(fileOut, "wb"); // Открытие выходного файла
    int gradient = 310; // Установление градиента (от него зависит преобладание черных и белых цветов)

    //Записываем в файл структуру
    fwrite( &header, 1, sizeStruct + 14, output );

    // В зависимости от BMP формата выбирается обработчик
    if (header.biBitCount == 16 && (header.biCompression == 3 || header.biCompression == 0)) {
        BMP16_5_6_5(input, output, header.bfOffBits, sizeStruct, header.biSizeImage, gradient);
    }
    else if (header.biBitCount == 16 && header.biCompression == 6) {
        BMP16_5_5_5(input, output, header.bfOffBits , sizeStruct, header.bfSize, header.biSize, gradient);
    }
    else if (header.biBitCount == 24) {
        BMP24(input, output, sizeStruct, header.biSizeImage, gradient);
    }
    else if (header.biBitCount == 8) {
        BMP8(input, output,sizeStruct, header.bfSize, gradient);
    }
    else if (header.biBitCount == 4) {
        BMP4(input, output, sizeStruct, header.bfSize, gradient);
    }
    else if (header.biBitCount == 32) {
        BMP32(input, output, sizeStruct, header.biSizeImage, gradient);
    }

    fclose(input);
    fclose(output);
}
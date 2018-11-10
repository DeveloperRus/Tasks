#ifndef EFFECTIVEMEMORYUSAGE_SET_H
#define EFFECTIVEMEMORYUSAGE_SET_H

#include <stdio.h>
#include <mm_malloc.h>

/**
 * Структура точки
 */
struct Point {
    unsigned char x: 4; // Координата X
    unsigned char y: 4; // Координата Y
};

/**
 * Структура множества
 */
struct Set {
    struct Point * points; // Указатель на массив точек
    int size;              // Размер множества
};

/**
 * Проверка на существование точки
 * @param point точка
 * @param points массив
 * @param size размер массива
 * @return результат проверки
 */
int checkPoint(struct Point * point, struct Point * points, int size);

/**
 * Удаление точки с конца
 * @param size размер множества
 * @param points массив точек
 */
void deleteLastPoint(int * size, struct Point ** points);

/**
 * Добавление точки в множество
 * @param point точка
 * @param size размер
 * @param points массив точек
 */
void addPoint(struct Point * point, int * size, struct Point ** points);

/**
 * Создания множества
 * @param points указатель на массив точек
 * @param point указатель на точку
 * @param size размер массива
 */
void createSet(struct Point ** points, struct Point * point, int * size);

/**
 * Прочитать множество и записать в файл
 * @param set множество
 */
void readSet(struct Set * set);

#endif //EFFECTIVEMEMORYUSAGE_SET_H

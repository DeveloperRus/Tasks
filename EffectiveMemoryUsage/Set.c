#include "Set.h"

int checkPoint(struct Point * point, struct Point * points, int size) {
    for (int i = 0; i < size; i++) {
        if(points[i].x == point->x)
            if (points[i].y == point->y)
                return 1;
    }
    return 0;
}

void deleteLastPoint(int * size, struct Point **points) {
    *size -= 1;
    *points = (struct Point*)realloc(*points, (*size) * sizeof(struct Point));
}


void addPoint(struct Point * point, int * size, struct Point ** points) {
    int input;

    // Узнаем координаты точки
    printf("Write coordinate x: ");
    scanf("%d", &input);
    point->x = input;

    printf("Write coordinate y: ");
    scanf("%d", &input);
    point->y = input;

    *size += 1;
    *points = (struct Point*)realloc(*points, (*size) * sizeof(struct Point));
    (*points)[*size - 1] = *point;
}

void readSet(struct Set *set) {
    FILE * out = fopen("output.txt", "w");
    char c;

    for (int i = 0; i < set->size; i++) {
        c = (set->points[i].x << 4) + set->points[i].y;
        fprintf(out, "%c", c);
    }

    fclose(out);
}

void createSet(struct Point **points, struct Point *point, int *size) {
    FILE * input = fopen("input.txt", "r");
    int counter = 0; // Счетчик символов, чтобы не записать мусор в множество

    while(!feof(input)) {
        char c;

        fseek(input, counter, SEEK_SET); // Устанавливаем указатель на последний считанный элемент
        counter++;

        fscanf(input, "%c", &c);
        point->x = c >> 4;
        point->y = c - ((c >> 4) << 4);

        *points = (struct Point*)realloc(*points, counter * sizeof(struct Point));
        (*points)[counter - 1] = *point;

        // Читаем символ после, так как в случае конца файла
        // тут будет мусор, который не надо заносить в множество
        fscanf(input, "%c", &c);
    }
    *size = counter;

    fclose(input);
}

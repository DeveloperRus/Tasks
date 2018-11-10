#include <stdio.h>
#include "Set.h"

int main() {
    struct Point point;
    struct Set set;

    set.size = 0;
    set.points = NULL;

    int flag;

    printf("Choose the command:\n1.Add point in set\n2.Delete last point in set\n"
                   "3.Check point in set\n4.Create set from file\n5.Read set in file\n"
                   "6.Exit\n");
    scanf("%d", &flag);

    while (flag != 6) {
        int coordinate;
        struct Point tmp;

        switch (flag) {
            case 1:
                addPoint(&point, &set.size, &set.points);
                break;
            case 2:
                deleteLastPoint(&set.size, &set.points);
                break;
            case 3:
                printf("Coordinate x of point: ");
                scanf("%d", &coordinate);
                tmp.x = coordinate;

                printf("Coordinate x of point: ");
                scanf("%d", &coordinate);
                tmp.y = coordinate;

                if (checkPoint(&tmp, set.points, set.size))
                    printf("Exist\n");
                else
                    printf("Doesn't exist\n");

                break;
            case 4:
                free(set.points);
                set.points = NULL;
                createSet(&set.points, &point, &set.size);
                break;
            case 5:
                readSet(&set);
                break;
            default:
                printf("Command doesn't correct\n");
                break;
        }
        printf("Choose the command:\n1.Add point in set\n2.Delete last point in set\n"
                       "3.Check point in set\n4.Create set from file\n5.Read set in file\n"
                       "6.Exit\n");
        scanf("%d", &flag);
    }

    return 0;
}
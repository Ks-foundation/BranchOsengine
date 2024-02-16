#include <stdio.h>

void print_rusty() {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if ((i + j) % 2 == 0) {
                printf(" ");
            } else {
                printf("░");
            }
            if (j != 9) {
                printf(",");
            }
        }
        printf("\n");
    }
}

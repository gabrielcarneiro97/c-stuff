#include <stdio.h>
#include <stdlib.h>

int **allocate(int size) {
    int **mtx = (int **) malloc(sizeof(int *) * size);

    for (int i = 0; i < size; i += 1) {
        mtx[i] = (int *) malloc(sizeof(int) * size);
    }

    return mtx;
}

void mtx_free(int **mtx, int size) {
    for (int i = 0; i < size; i += 1) {
       free(mtx[i]);
       mtx[i] = NULL;
    }

    free(mtx);
    mtx = NULL;
}

void populate(int **mtx, int size) {
    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            mtx[i][j] = (i * 10) + j;
        }
    }
}

void print(int **mtx, int size) {
    printf("------------------\n");
    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            printf("%02d\t", mtx[i][j]);
        }
        printf("\n");
    }
    printf("------------------\n");
}

int main (void) {
    int size = 10;
    int **mtx = allocate(size);
    print(mtx, size);
    populate(mtx, size);
    print(mtx, size);
    mtx_free(mtx, size);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int **mtx_allocate(int size) {
    int** mtx = (int **) calloc(size, sizeof(int *));

    for (int i = 0; i < size; i += 1) {
        mtx[i] = (int *) calloc(size, sizeof(int));
    }

    return mtx;
}

int **mtx_reallocate(int **mtx, int size) {
    mtx = (int **) realloc(mtx, sizeof(int *) * size);

    for (int i = 0; i < size; i += 1) {
        mtx[i] = (int *) realloc(mtx[i], sizeof(int) * size);
    }

    return mtx;
}

void mtx_populate(int **mtx, int size) {
    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            mtx[i][j] = (i * 10) + j;
        }
    }
}

void mtx_print(int **mtx, int size) {
    printf("------------------\n");
    for (int i = 0; i < size; i += 1) {
        for (int j = 0; j < size; j += 1) {
            printf("%02d\t", mtx[i][j]);
        }
        printf("\n");
    }
    printf("------------------\n");
}

void mtx_free(int ***mtx, int size) {
    int **inner_mtx = *mtx;
    for (int i = 0; i < size; i += 1) {
       free(inner_mtx[i]);
       inner_mtx[i] = NULL;
    }

    free(inner_mtx);
    *mtx = NULL;
}

int main (void) {

    // definindo o tamanho da matriz.
    int size = 5;

    // alocando a matriz.
    int **mtx = mtx_allocate(size);

    // imprime a matriz vazia.
    mtx_print(mtx, size);

    // popula a matriz.
    mtx_populate(mtx, size);

    // imprime a matriz populada.
    mtx_print(mtx, size);

    // aumenta o tamanho da matriz.
    size += 5;

    // realoca a matriz
    mtx = mtx_reallocate(mtx, size);

    //imprime matriz realocada.
    mtx_print(mtx, size);

    // repopula a matriz para preencher os espaços vazios.
    mtx_populate(mtx, size);

    // imprime a matriz repopulada.
    mtx_print(mtx, size);

    // libera a matriz.
    mtx_free(&mtx, size);

    // conferindo se mtx aponta para NULL
    printf("%p\n", mtx);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

int **mtx_allocate(int row, int col) {
    int** mtx = (int **) calloc(row, sizeof(int *));

    for (int i = 0; i < row; i += 1) {
        mtx[i] = (int *) calloc(col, sizeof(int));
    }

    return mtx;
}

void mtx_print(int **mtx, int row, int col) {
    printf("------------------\n");
    for (int i = 0; i < row; i += 1) {
        for (int j = 0; j < col; j += 1) {
            printf("%02d\t", mtx[i][j]);
        }
        printf("\n");
    }
    printf("------------------\n");
}

void mtx_free(int ***mtx, int row) {
    int **inner_mtx = *mtx;
    for (int i = 0; i < row; i += 1) {
       free(inner_mtx[i]);
       inner_mtx[i] = NULL;
    }

    free(inner_mtx);
    *mtx = NULL;
}

char *lcs(char *str1, char *str2, int len1, int len2) {
    int **lcs_mtx = mtx_allocate(len1 + 1, len2 + 1);

    for (int i = 0; i <= len1; i += 1)  {
        for (int j = 0; j <= len2; j += 1) {
            if (i == 0 || j == 0) {
                lcs_mtx[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                lcs_mtx[i][j] = lcs_mtx[i - 1][j - 1] + 1;
            } else {
                lcs_mtx[i][j] = max(lcs_mtx[i - 1][j], lcs_mtx[i][j - 1]);
            }
        }
    }

    int index = lcs_mtx[len1][len2];

    char *longest = (char *) calloc(index + 1, sizeof(char));
    longest[index] = '\0';

   int i = len1;
   int j = len2;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            longest[index - 1] = str1[i - 1];
            i -= 1;
            j -= 1;
            index -= 1;
        }
        else if (lcs_mtx[i - 1][j] > lcs_mtx[i][j - 1]) {
            i -= 1;
        } else {
            j -= 1;
        }
    }

    mtx_free(&lcs_mtx, len1 + 1);
    return longest;
}


int main() {
    char *x = "ATTCTTTAGCAGGCAGGCAGGTGGCAGGTGACGATGGGGATGGAAAAG";
    char *y = "ATACTTTAGCATGCGGGCAGGAGGCGAGACGATGTCGGTATGAATG";

    int m = strlen(x);
    int n = strlen(y);

    char *str = lcs(x, y, m, n);

    printf("%s\n", str);
}

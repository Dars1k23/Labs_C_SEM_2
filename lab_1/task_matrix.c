#include <stdio.h>
#include <stdlib.h>
#include "task_struct.h"

Matrix* create_matrix(int m) {
    Matrix* matr = malloc(sizeof(Matrix));
    if (!matr) return NULL;
    
    matr->m = m;                        
    matr->lines = malloc(m * sizeof(Line));
    if (!matr->lines) {
        free(matr);
        return NULL;
    }
    
    for (int i = 0; i < m; i++) {
        matr->lines[i].len = 0;          
        matr->lines[i].data = NULL;      
    }
    
    return matr;                         
}


void fill_matrix(Matrix *matr){
    for (int i = 0; i < matr->m; i++){
        printf("Длина строки: ");
        scanf("%d", &matr->lines[i].len);
        matr->lines[i].data = malloc(matr->lines[i].len * sizeof(int));
        for (int j = 0; j < matr->lines[i].len; j++){
            printf("Введите число %d: ", j + 1);
            scanf("%Lf", &matr->lines[i].data[j]);
        }
    }

}

void print_matrix(Matrix *matr){
    for (int i = 0; i < matr->m; i++){
        for (int j = 0; j < matr->lines[i].len; j++){
            printf("%Lf ", matr->lines[i].data[j]);
        }
        printf("\n");
    }
}

void free_matrix(Matrix *matr){
    for (int i = 0; i < matr->m; i++){
        free(matr->lines[i].data);
        matr->lines[i].data = NULL;
    }

    free(matr->lines);
    matr->lines = NULL;

    free(matr);
    matr = NULL;
}

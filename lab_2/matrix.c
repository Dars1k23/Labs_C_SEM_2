#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void fill_board(Matrix* board){
    int count = 1;
    for (int i = 0; i < board->m_len; i++){
        for (int j = 0; j < board->lines[i].len; j++){
            board->lines[i].data[j] = count;
            count++;
        }
    }
    board->lines[3].data[3] = 0;
}

void shufl_board(Matrix* board){
    for (int i = 0; i < 1000; i++){ //1тыс перестановок для перемешивания 
        int ex = -1, ey = -1;

        for (int y = 0; y < board->m_len; y++){ //находим координаты нуля
            for (int x = 0; x < board->lines[y].len; x++){
                if (board->lines[y].data[x] == 0){
                    ex = x;
                    ey = y;
                    goto found_zero;
                }
            }
        }    
        found_zero:;
        
        int dx[] = {-1, 1, 0, 0}; //вправо или влево
        int dy[] = {0, 0, -1, 1}; //вверж или вниз
        int dir = rand() % 4; //рандомное число от 0-4

        int nx = ex + dx[dir]; //новые координаты нуля по x
        int ny = ey + dy[dir]; //новы координаты нуля по y

        if (ny >= 0 && ny <= board->m_len && nx >= 0 && nx <= board->lines[ny].len){
            int tmp = board->lines[ny].data[nx]; //сохраняю переменную на место которой будет ноль
            board->lines[ny].data[nx] = board->lines[ey].data[ex]; //вставляю ноль на новую позию
            board->lines[ey].data[ex] = tmp; //вставляю значение из ячейки куда переместился ноль
        }
}

void print_board(Matrix* board){
    for (int i = 0; i < board->m_len; i++){
        printf("+---+---+---+---+")
        for (int j = 0; j < board->lines[i]; j++){
            printf("| ");
            printf("%d ", board->lines[i].data[j]);
        }
    }
}


Matrix *init_board(){
    Matrix* board = malloc(sizeof(Matrix)); //память под матрицу
    if (!board) return NULL; //проверка выделения памяти на матрицу
    board->m_len = 4; //присваиваю кол-во строк в матрице
    board->lines = malloc(board->m_len * sizeof(Lines)); //выделил память под массив строк матрицы
    if (!board->lines){
        free(board);
        return NULL; //проверка выделения памяти на массив строк матрицы
    }
    for (int i = 0; i < board->m_len; i++){ //в цикле прохожусь по строкам, присваиваю каждой строке длину и выделяю память
        board->lines[i].len = board->m_len;
        board->lines[i].data = malloc(board->lines[i].len * sizeof(int));
        if (!board->lines[i].data){ //проверка на выделения памяти на массив
            for (int j = 0; j < i; j++){
                free(board->lines[j].data);
            }
            return NULL;
        }    
    }    
    fill_board(board); //функция заполнения матрицы 
    shufl_board(board); //функция перемешивания элементов матрицы
    return board;
}







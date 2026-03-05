#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "struct.h"

Matrix *play(Matix* board, int nx, int ny){
    int ex = -1;
    int ey = -1;
    for (int i = 0l i < board->m_len; i++){ //нахожу координаты нуля
        for (int j = 0; j < board->lines[i].len; j++){
            if (board->lines[i].data[j] == 0){
                ey = i;
                ex = j;
            }
        }
    }

    int dx = ex + nx; //новые координаты по x
    int dy = ey + ny; //новые координаты по y
    
    if (dx <= 0 || dx > board->m_len || dy <= 0 || dy > board->m_len) return NULL;
    
    int tmp = board->lines[dy].data[dx]; //сохраняем переменную
    board->lines[dy].data[dx] = board->lines[ey].data[ex]; //на место сохраненной переменной вставляем ноль
    board->lines[ey].data[ex] = tmp; //вставляем на освободившееся метсто сохраненную переменную
    //НУЖНА ФУНКЦИЯ ДОБАВЛЕНИЯ ХОДОВ В СТЕК, ДЛЯ РЕАЛИЗАЦИИ ВОЗМОЖНОСТИ ВЕРНУТЬСЯ К ПРЕДЫДУЩЕМУ ХОДУ
    return board;
    
}

bool check_win(Matrix* board){
    int count = 1;
    for (int i = 0; i < board->m_len; i++){
        for (int j = 0; j < board->lines[i].len; j++){
            if (board->lines[i].data[j] == count || board->lines[i].data[j] == 0){
                count++;
            }
            else return false;
        }
    }    
    return true;
}

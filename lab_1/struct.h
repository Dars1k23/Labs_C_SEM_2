#ifndef STRUCT_H
#define STRUCT_H

typedef struct{
    int *data;
    int top;
    int size;
    int capacity;
} Stack;

typedef struct{
    int len;
    int *data;
} Line;

typedef struct{
    int m_len;
    Line *lines;
} Matrix;

#endif

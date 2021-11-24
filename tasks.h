#ifndef TASKS_H
#define TASKS_H

typedef struct Row
{
    int a;
    int b;
} Row;

typedef struct RowNode
{
    int index;
    const Row *row;
} RowNode;

// 升序：如果 left < right，返回 true
inline bool compare(Row left, Row right)
{
    if (left.a < right.a || (left.a == right.a && left.b < right.b))
        return true;
    else
        return false;
}

// 升序
inline bool compareB(Row left, Row right)
{
    return left.b < right.b;
}

// 升序
inline int compareB2(const void *left, const void *right)
{
    return ((Row *)left)->b - ((Row *)right)->b;
}

void task1(const Row *rows, int nrows);
void task2(const Row *rows, int nrows);
void task3(Row *rows, int nrows);
void task4(Row *rows, int nrows);

#endif
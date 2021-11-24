#include "tasks.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

long getTimeNs()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

Row *generateRows(int rows_num)
{
    Row *rows = new Row[rows_num];
    int div = (rows_num > 10000 ? rows_num : 10000);
    for (int i = 0; i < rows_num; i++)
    {
        rows[i].a = rand() % div / 100 * 100;
        rows[i].b = rand() % 500;
    }
    return rows;
}

int main(int argc, char **argv)
{
    int row_nums = 10000;
    time_t start;
    srand(time(0));

    {
        Row *rows = generateRows(row_nums);
        printf("==== task1 ====\n");
        start = getTimeNs();
        task1(rows, row_nums);
        printf("task1 takes %ld nano-seconds\n", getTimeNs() - start);
        free(rows);
    }

    row_nums = 1 * 10000 * 10000; // 1亿行
    {
        Row *rows = generateRows(row_nums);
        sort(rows, rows + row_nums, compare);
        printf("==== task2 ====\n");
        start = getTimeNs();
        task2(rows, row_nums);
        printf("task2 takes %ld nano-seconds\n", getTimeNs() - start);
        free(rows);
    }

    {
        Row *rows = generateRows(row_nums);
        sort(rows, rows + row_nums, compare);
        printf("==== task3 ====\n");
        start = getTimeNs();
        task3(rows, row_nums);
        printf("task3 takes %ld nano-seconds\n", getTimeNs() - start);
        free(rows);
    }

    {
        Row *rows = generateRows(row_nums);
        sort(rows, rows + row_nums, compare);
        printf("==== task4 ====\n");
        start = getTimeNs();
        task4(rows, row_nums);
        printf("task4 takes %ld nano-seconds\n", getTimeNs() - start);
        free(rows);
    }

    return 0;
}

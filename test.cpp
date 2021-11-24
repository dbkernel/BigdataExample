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
    int div = (rows_num > 100000 ? rows_num : 100000);
    for (int i = 0; i < rows_num; i++)
    {
        rows[i].a = rand() % div / 100 * 100;
        rows[i].b = rand() % 100;
    }
    return rows;
}

void runTask(enum TaskNum num, Row *rows, int row_nums)
{
    time_t start = getTimeNs();
    srand(time(0));
    printf("==== task%d ====\n", num);
    switch (num)
    {
    case TASK1:
        task1(rows, row_nums); // 不适合海量数据
        break;
    case TASK2:
        task2(rows, row_nums);
        break;
    case TASK3:
        task3(rows, row_nums);
        break;
    case TASK4:
        task4(rows, row_nums);
        break;
    default:
        break;
    }
    printf("task%d takes %ld nano-seconds\n", num, getTimeNs() - start);
}

int main(int argc, char **argv)
{
    int row_nums = 10000;

    {
        Row *rows = generateRows(row_nums);
        runTask(TASK1, rows, row_nums);
        free(rows);
    }

    row_nums = 1 * 10000 * 10000; // 1亿行
    {
        Row *rows = generateRows(row_nums);
        sort(rows, rows + row_nums, compare);
        runTask(TASK2, rows, row_nums);
        free(rows);
    }

    {
        Row *rows = generateRows(row_nums);
        sort(rows, rows + row_nums, compare);
        runTask(TASK3, rows, row_nums);
        free(rows);
    }

    {
        Row *rows = generateRows(row_nums);
        sort(rows, rows + row_nums, compare);
        runTask(TASK4, rows, row_nums);
        free(rows);
    }

    return 0;
}

#include "tasks.h"
#include "skiplist.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

/*!
* Task 1.
*
* Find out all the rows that sastify below conditions:
*
* ((b >= 10 && b < 50) &&
* (a == 1000 || a == 2000 || a == 3000))
*
* Print them to the terminal, one row per line, for example:
*
* 1000,20
* 1000,23
* 2000,16
*
* @param nrows The total number of rows.
* @param rows The rows, for example rows[0] is the first row.
*/
void task1(const Row *rows, int nrows)
{
    for (int i = 0; i < nrows; i++)
    {
        if ((rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000) && (rows[i].b >= 10 && rows[i].b < 50))
        {
            cout << rows[i].a << ", " << rows[i].b << endl;
        }
    }
}

// 使用二分查找的方式找到第一个大于等于 target 的行
int binarySearch(const Row *rows, int nrows, const Row target)
{
    if (rows == nullptr)
        return 0;

    int left = 0;
    int right = nrows - 1;
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        int res = compare(rows[mid], target);
        if (res)
            left = mid + 1;
        else
            right = mid; // 表明 mid >= target
    }
    return right;
}

/*
* Based on task 1, assume that the parameter rows has been sorted by (a,b).
*
* Input:
* Row sorted_rows[] =
* {
*     { 1000, 31 },
*     { 1000, 72 },
*     { 1500, 12 },
*     { 1500, 34 },
*     { 2000, 22 },
*     { 2000, 33 },
* };
*
* Output:
* 1000,31
* 2000,22
* 2000,33
*/
// 二分查找
void task2(const Row *rows, int nrows)
{
    for (int i = 1; i < 4; i++)
    {
        Row min = {i * 1000, 10}, max = {i * 1000, 50};
        int minIndex = binarySearch(rows, nrows, min);
        int maxIndex = binarySearch(rows, nrows, max);
        while (minIndex < maxIndex)
        {
            cout << rows[minIndex].a << ", " << rows[minIndex].b << endl;
            minIndex++;
        }
    }
}

/*
* Based on task 2, the printed matching rows are sorted by column b.
*
* Output:
* 2000,22
* 1000,31
* 2000,33
*/
void task3(Row *rows, int nrows)
{
    int len = 100;

    for (int i = 1; i < len; i++)
    {
        Row min = {i * 1000, 10}, max = {i * 1000, 50};
        // 使用二分查找确定边界
        int minIndex = binarySearch(rows, nrows, min);
        int maxIndex = binarySearch(rows, nrows, max);

        // 由于内存可以放下，按快速排序方式对 b 列排序后输出结果集
        sort(rows + minIndex, rows + maxIndex, compareB);
        while (minIndex < maxIndex)
        {
            cout << rows[minIndex].a << ", " << rows[minIndex].b << endl;
            minIndex++;
        }
    }
}

/*
* Based on task 3, assume that the match condition on column a is not just 1000,2000,3000,
* but expanded to 1000,2000,3000... , 98000, 99000.
*/
// 跳表
void task4(Row *rows, int nrows)
{
    int len = 100;
    int minIndexs[len], maxIndexs[len];

    skiplist *list = skiplistCreate(compareBForRowNode);

    for (int i = 1; i < len; i++)
    {
        Row min = {i * 1000, 10}, max = {i * 1000, 50};
        // 使用二分查找确定边界
        int minIndex = binarySearch(rows, nrows, min);
        int maxIndex = binarySearch(rows, nrows, max);
        minIndexs[i] = minIndex;
        maxIndexs[i] = maxIndex;
        if (minIndex < maxIndex)
        {
            RowNode node = {i, rows + minIndex};
            skiplistInsert(list, &node); // 插入后按照 B 列升序构建跳表
        }
    }

    while (skiplistLength(list) != 0)
    {
        RowNode *head = (RowNode *)skiplistPopHead(list);
        cout << head->row->a << ", " << head->row->b << endl;
        int minIndex = ++minIndexs[head->index]; // 最小边界后移
        int maxIndex = maxIndexs[head->index];
        if (minIndex < maxIndex)
        {
            RowNode node = {head->index, rows + minIndex};
            skiplistInsert(list, &node); // 插入后按照 B 列升序构建跳表
        }
    }

    skiplistFree(list);
}
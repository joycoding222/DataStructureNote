// 本章（排序算法）中，数据的存储方式为顺序表存储；(hint: 线性表包括顺序表和链表)
/*
插入排序：
在有序序列中插入元素；根据确定插入位置的方法可以分为：
直接插入排序，二分插入排序，希尔排序（缩小增量多遍插入排序）
直接插入排序：采用顺序查找法查找插入位置；
二分插入排序：采用二分法查找插入元素在有序序列中的位置；
希尔排序：采用多遍直接插入排序，第一轮间隔为5，第二轮间隔为3，第三轮间隔为1；
*/

#include <iostream>
using namespace std;

#define MaxSize 20

typedef int KeyType;

// 每项数据元素的结构
typedef struct
{
    KeyType key;
} RedType;

// 存储数据元素的顺序表
typedef struct
{
    int length;
    RedType r[MaxSize + 1]; // r[0]一般做哨兵或缓冲区
} SqList;

// 直接插入排序
void InsertSort(SqList &L)
{
    int i;                          // 要排序的元素下标
    int j;                          // 进行比较的元素的下标
    for (i = 2; i <= L.length; i++) // 从第二个元素开始排序(L->r[0]作为哨兵不计数，数据元素从下标1开始)
    {
        if (L.r[i].key < L.r[i - 1].key) // 是否需要插入有序序列
        {
            L.r[0] = L.r[i]; // 复制为哨兵
            for (j = i - 1; L.r[0].key < L.r[j].key; j--)
            {
                /*
                注意该循环不成立的条件：第一，待插入的元素大于比较的元素(第j个)，此时插入的位置为j+1;
                第二，待插入的元素等于比较的元素(j已经指向哨兵位置0)，此时在序列头j+1插入；
                */
                L.r[j + 1] = L.r[j]; // 后移到j+1位置
            } // 找到插入的位置j+1
            L.r[j + 1] = L.r[0];

            // 无哨兵(哨兵的作用：避免每次都要比较数组是否越界)
            // RedType curr = L->r[i]; // 需要排序的元素
            // for (j = i-1; j >= 0 && curr.key < L->r[j].key; j--)
            // {
            //     L->r[j+1] = L->r[j];
            // }
            // L->r[j+1] = curr;
        }
    }
}

// 二分插入排序
void BinaryInsertSort(SqList &L)
{
    int i, j;
    for (i = 2; i <= L.length; i++) // 从第二个元素开始插入有序序列
    {
        L.r[0] = L.r[i]; // 将要插入的元素存入哨兵位置
        int left = 1;    // left 和 right 分别指向有序序列的表头和表尾
        int right = i - 1;
        while (left <= right)
        {
            int middle = (left + right) / 2;
            if (L.r[0].key < L.r[middle].key)
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        } // right + 1为插入位置
        for (j = i - 1; j >= right + 1; j--)
        {
            L.r[j + 1] = L.r[j]; // 右移
        }
        L.r[j + 1] = L.r[0];
    }
}

// 希尔排序的第 n 趟直接插入排序
void ShellSort_n(SqList &L, int dk)
{
    // 对顺序表进行一趟增量为dk的插入排序
    int i; // 要排序的元素的下标
    int j; // 进行比较的元素的下标
    for (i = dk + 1; i <= L.length; i++)
    {
        if (L.r[i].key < L.r[i - dk].key)
        {
            L.r[0] = L.r[i];                                                 // 存入哨兵
            for (j = i - dk; j > 0 && (L.r[0].key < L.r[j].key); j = j - dk) // 为什么这里有哨兵的情况下仍需要比较j的值是否大于0？？？
            {
                L.r[j + dk] = L.r[j];
            } // 插入的位置为j+dk
            L.r[j + dk] = L.r[0];
        }
    }
}

// 希尔排序
void ShellSort(SqList &L, int delta_k[], int t)
{
    // delta_k[] 为增量序列，递减，最后一个元素为1
    // t 为增量序列长度
    // 按照增量序列 delta_k[k] 对顺序表 L 进行希尔排序
    for (int k = 0; k < t; k++)
    {
        ShellSort_n(L, delta_k[k]); // 一趟增量为 delta_k[k] 的直接插入排序
    }
}

// 打印元素
void output(SqList &L)
{
    for (int i = 1; i <= L.length; i++)
    {
        cout << L.r[i].key << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    SqList L;
    L.length = 13;
    L.r[0].key = 0;
    L.r[1].key = 81;
    L.r[2].key = 94;
    L.r[3].key = 11;
    L.r[4].key = 96;
    L.r[5].key = 12;
    L.r[6].key = 35;
    L.r[7].key = 17;
    L.r[8].key = 95;
    L.r[9].key = 28;
    L.r[10].key = 58;
    L.r[11].key = 41;
    L.r[12].key = 75;
    L.r[13].key = 15;

    output(L);

    // int delta_k[] = {5, 3, 1}; // 增量序列
    // int t = 3;                 // 增量序列长度
    // ShellSort(L, delta_k, t);
    // InsertSort(L);
    BinaryInsertSort(L);
    output(L);

    return 0;
}
/*
归并排序：将两个或两个以上有序序列归并成为一个有序序列；
*/
#include <iostream>
using namespace std;

#define MaxSize 20

typedef int KeyType;
typedef int elem;

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

// 打印元素
void output(SqList &L)
{
    for (int i = 1; i <= L.length; i++)
    {
        cout << L.r[i].key << " ";
    }
    cout << endl;
}

void output(int arr[], int length)
{
    for (int i = 0; i <= length - 1; i++) // 元素从下标0开始
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 归并排序--合并两个有序数组
void Merge(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;   // 左子数组起始索引
    int j = mid + 1;    // 右子数组起始索引
    int k = left;   // 临时数组起始索引

    // 比较左右子数组元素，并放入临时数组
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }

    // 处理剩余元素
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // 将合并结果复制回原数组
    for (int p = left; p <= right; p++)
    {
        arr[p] = temp[p];
    }
}

// 归并排序
void MergeSort(int arr[], int temp[], int left, int right)
{
    if (left >= right) return;  // 递归终止条件（子数组只剩一个元素）

    int mid = left + (right - left) / 2;    // 中间位置
    MergeSort(arr, temp, left, mid);    // 递归排序左半部分
    MergeSort(arr, temp, mid + 1, right);   // 递归排序右半部分
    // 合并两个有序子数组
    Merge(arr, temp, left, mid, right);
}

// 封装归并排序函数（方便调用）
void MergeSort(int arr[], int length)
{
    int *temp = new int[length];
    MergeSort(arr, temp, 0, length - 1);
    delete []temp;
}

int main(int argc, char *argv[])
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int length = sizeof(arr) / sizeof(arr[0]);  // 计算数组长度
    output(arr, length);

    MergeSort(arr, length);

    output(arr, length);

    return 0;
}
/*
交换排序：
冒泡排序：每趟不断将元素两两比较，对于n个元素，需要n-1趟冒泡排序（每趟增加一个有序元素）,
第m趟需要比较的次数j=n-m;
快速排序：首先任意选取一个元素作为中心（如第一个元素），比中心元素小的数据放在他前面，比中心元素大的数据
放在他后面，得到左右两个子表；对子表重新选择中心，并依次调整；直到每个子表只剩一个元素；
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

// 冒泡排序
void BubbleSort(SqList &L)
{
    int n = L.length;            // 数据元素总数n
    int m;                       // 第m趟排序，总共需要进行n-1趟排序
    int j;                       // 进行比较的元素
    for (m = 1; m <= n - 1; m++) // 第m趟排序
    {
        for (j = 1; j <= n - m; j++) // 第m趟排序需要进行n-m次比较
        {
            // 第0个位置作哨兵，不进行比较，j从1开始
            if (L.r[j].key > L.r[j + 1].key)
            {
                RedType temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
            }
        }
    }
}

// 冒泡排序的改进
void BubbleSort_improve(SqList &L)
{
    // 增加了 flag 作为是否发生了交换的标志，若第m趟排序未发生交换，则序列已经有序，后续排序无需进行
    int n = L.length; // 数据元素的个数
    int m;            // 第m趟排序
    int j;            // 进行比较的元素
    int flag = 1;     // flag 作为是否发生了交换的标志
    for (m = 1; m <= n - 1 && flag == 1; m++)
    {
        // 第m趟排序
        flag = 0;
        for (j = 1; j <= n - m; j++) // 第m趟排序需要进行n-m次比较
        {
            if (L.r[j].key > L.r[j + 1].key) // 需要进行交换
            {
                flag = 1; // 发生了交换
                RedType temp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = temp;
            }
        }
    }
}

// 快速排序找到中心点坐标
int Partition(SqList &L, int low, int high)
{
    L.r[0] = L.r[low]; // 将第一个元素作为中心点并搬运到哨兵结点
    int pivot_Key = L.r[low].key;
    while (low < high)
    {
        // 左侧(low)有空结点，将右侧小于pivot_Key的数据搬运至左侧
        while (low < high && L.r[high].key >= pivot_Key)
            high--;
        L.r[low] = L.r[high];

        // 右侧(high)有空结点，将左侧大于pivot_Key的数据搬运至右侧
        while (low < high && L.r[low].key <= pivot_Key)
            low++;
        L.r[high] = L.r[low];
    } // low, high 相等时退出循环，找到pivot在表中的下标

    int pivot = low;
    L.r[pivot] = L.r[0]; // 将pivot放回数组
    return pivot;
}

// 快速排序
void QuickSort(SqList &L, int low, int high)
{
    // low, high 分别指向排序区间的最左侧和最右侧
    if (low < high)
    {
        int pivot = Partition(L, low, high); // 查找pivot在数组中的下标
        QuickSort(L, low, pivot - 1);        // 前半段排序
        QuickSort(L, pivot + 1, high);       // 后半段排序
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

    // BubbleSort(L);
    // BubbleSort_improve(L);
    QuickSort(L, 1, L.length);
    output(L);

    return 0;
}
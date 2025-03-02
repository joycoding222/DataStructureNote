/*
选择排序：在待排序的元素中选择最大的或最小的放在其最终位置；
简单选择排序：从第一个元素开始，和后面的元素逐个比较直到找到最小的，并交换位置；重复以上步骤；
简单选择排序是不稳定的排序；
堆排序：对于小根堆，堆顶元素是序列的最小值，将其输出后，将其余n-1个元素调整成一个堆，继续输出堆顶元素，如此往复；
得到一个有序序列，这个过程称为堆排序；
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

void output(elem R[], int length)
{
    for (int i = 1; i <= length; i++) // 元素从下标1开始
    {
        cout << R[i] << " ";
    }
    cout << endl;
}

// 简单选择排序：从第一个元素开始，找到后续元素中最小的并交换
void SelectSort(SqList &L)
{
    for (int i = 1; i < L.length; i++) // 共需要length-1次排序（最后只剩一个元素，不需要排序）
    {
        int min_index = i;                      // 最小关键字的下标
        for (int j = i + 1; j <= L.length; j++) // 从当前元素i的下一个元素开始比较
        {
            if (L.r[j].key < L.r[min_index].key)
            {
                min_index = j; // 更新最小关键字下标
            }
        }
        if (min_index != i)
        {
            // 交换
            RedType temp = L.r[i];
            L.r[i] = L.r[min_index];
            L.r[min_index] = temp;
        }
    }
}

// 堆排序--堆的调整
void HeapAdjust(elem R[], int s, int m) // R[]:待排序序列； s:根结点元素下标； m:最后一个元素下标
{
    /*
    将以s为根的子树调整为大根堆：
    已知R[]中记录的关键字除了R[s]之外均满足堆的定义，HeapAdjust函数通过调整R[s]的关键字，
    使得R[]成为一个大根堆；
    */
    elem rc = R[s];                     // 保存待调整的根结点
    for (int j = 2 * s; j <= m; j *= 2) // 完全二叉树性质：根结点i，孩子结点2i, 2i+1
    {
        // 每一次循环向下调整一层
        if (j < m && R[j] < R[j + 1]) // 查找两个孩子结点中较大者的下标
        {
            j++;
        }
        // 若根结点大于两个孩子结点，无需调整
        if (rc >= R[j])
            break;
        // rc < R[j] 根结点小于孩子，需要调整
        R[s] = R[j]; // 将较大的孩子结点赋值给根结点
        s = j;       // 更新待调整的根结点
    }
    R[s] = rc; // 最终位置s插入调整前的根结点
}

// 堆排序--建立堆
// 单结点的二叉树是堆，因此，建立堆即从最后一个非叶子结点开始向前调整
void HeapBuild(elem R[], int length)
{
    for (int i = length / 2; i >= 1; i--)
    {
        HeapAdjust(R, i, length);
    }
}

// 堆排序
void HeapSort(elem R[], int length)
{
    // 建立堆
    HeapBuild(R, length);
    // 堆排序
    for (int i = length; i > 1; i--) // 对n-1个元素排序
    {
        // 将堆顶元素（最大值）放在最后一个
        // int temp = R[1];
        // R[1] = R[i];
        // R[i] = temp;
        swap(R[1], R[i]);
        HeapAdjust(R, 1, i - 1);
    }
}

int main(int argc, char *argv[])
{
    elem R[] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
    int length = 8;
    output(R, length);

    HeapSort(R, length);
    output(R, length);

    return 0;
}
/*
二分查找：
前提：数据有序排列
1.两个指针left & right 分别指向线性表的两端；
2.mid = (left + right) / 2; 若key < data[middle], 则right = middle - 1;
若Key > data[middle]; 则left = middle + 1;
3.若right < left, 查找失败；
*/
#include <iostream>

using namespace std;

#define KeyType int

// 查找表元素
typedef struct{
    KeyType key;
}ElemType;

// 查找表
typedef struct 
{
    ElemType *R;
    int length;
}SST;

// 构建顺序查找表
// 注意采用二分查找时的线性表必须顺序排列！！！！！！
void create_SST(SST * &ST)
{
    ST = new SST;
    ST->R = new ElemType[12];
    ST->length = 12;
    // 初始化
    int keys[] = {0, 5, 7, 13, 19, 21, 56, 64, 75, 80, 88, 92};
    for (int i = 0; i < ST->length; i++)
    {
        ST->R[i].key = keys[i];
    }
    // ST->R[0].key = 0;
    // ST->R[1].key = 5;
    // ST->R[2].key = 7;
    // ST->R[3].key = 13;
    // ST->R[4].key = 19;
    // ST->R[5].key = 21;
    // ST->R[6].key = 56;
    // ST->R[7].key = 64;
    // ST->R[8].key = 75;
    // ST->R[9].key = 80;
    // ST->R[10].key = 88;
    // ST->R[11].key = 92;
}

// 二分查找
int Search_binary(SST ST, KeyType key)
{
    int left = 0, right = ST.length-1; // 初始查找区间
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (ST.R[middle].key == key)
            return middle; // 查找成功
        else if (key < ST.R[middle].key)
            right = middle - 1; // 查找区间为前一半
        else
            left = middle + 1; // 查找区间为后一半
    }
    return -1; // 查找失败
}
// 二分查找Recursive
int Search_Binary(SST ST, KeyType key, int left, int right)
{
    if (left > right)
        return -1; // 查找失败
    int middle = (left + right) / 2;
    if (key == ST.R[middle].key)
        return middle;
    else if (key < ST.R[middle].key)
        return Search_Binary(ST, key, left, middle - 1);
    else
        return Search_Binary(ST, key, middle + 1, right);
}

int main(int argc, char *argv[])
{
    SST *ST;
    create_SST(ST);

    cout << Search_binary(*ST, 80) << endl;

    return 0;
}
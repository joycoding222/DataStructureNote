/*
顺序查找表：
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
void create_SST(SST * &ST)
{
    ST = new SST;
    ST->R = new ElemType[12];
    ST->length = 12;

    ST->R[0].key = 0;
    ST->R[1].key = 5;
    ST->R[2].key = 7;
    ST->R[3].key = 19;
    ST->R[4].key = 21;
    ST->R[5].key = 13;
    ST->R[6].key = 56;
    ST->R[7].key = 64;
    ST->R[8].key = 92;
    ST->R[9].key = 88;
    ST->R[10].key = 80;
    ST->R[11].key = 75;
}
// 顺序查找(元素存储从1到11)
// int search(SST ST, KeyType key)
// {
//     for (int i = 1; i <= ST.length; i++)
//     {
//         if (ST.R[i].key == key)
//         {
//             return i;
//         }
//     }
//     return 0;
// }

// int search(SST ST, KeyType key)
// {
//     int i = ST.length;
//     for ( ; ST.R[i].key != key; i--)
//     {
//         if (i <= 0) break;
//     }
//     if (i > 0)
//     {
//         return i;
//     }
//     else{
//         return 0;
//     }
// }
/*
前两种查找的问题：
每循环一次，需要进行两次比较：判断元素的key和待查找的key是否相等；下标i是否小于等于0；
因此可以做如下改进：
哨兵（监视哨）：把待查找的关键字key存入表头（第0个位置空着），从后往前逐个比较是否相等即可；
*/
// 设置监视哨的顺序查找(元素较多时查找时间大大缩短)
int search(SST ST, KeyType key)
{
    int i;
    ST.R[0].key = key;
    for (i = ST.length; ST.R[i].key != key; i--);   // 无循环体
    return i;
}

int main(int argc, char *argv[])
{
    SST *ST;
    create_SST(ST);

    cout << search(*ST, 5) << endl;

    delete[] ST->R;
    delete[] ST;

    return 0;
}
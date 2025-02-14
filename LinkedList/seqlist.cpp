#include <iostream>

using namespace std;

#define Maxsize 100
typedef int ElementType;

struct SeqList{
    ElementType data[Maxsize];
    int length;
};

// 顺序表初始化
void initList(SeqList *L)
{
    L->length = 0;
}

// 顺序表初始化
void initList(SeqList *L, ElementType a, ElementType b, ElementType c)
{
    L->length = 3;
    L->data[0] = a;
    L->data[1] = b;
    L->data[2] = c;
}

// 顺序表尾部插入元素
bool AddElement(SeqList *L, ElementType e)
{
    if (L->length >= Maxsize){
        cout << "顺序表已满" << endl;
        return 0;
    }
    L->data[L->length] = e;
    L->length++;
    return 1;
}

// 顺序表任意位置插入元素, posi 是物理上的位置
bool AddElement(SeqList *L, ElementType e, int posi)
{
    if (L->length >= Maxsize){
        cout << "顺序表已满" << endl;
        return 0;
    }
    if (posi <= L->length)
    {
        for (int i = L->length - 1; i >= posi - 1; i--)
        {
            L->data[i + 1] = L->data[i];
        }
        L->data[posi - 1] = e;
    }
    L->length++;
    return 1;
}

// 顺序表任意位置删除元素
bool DeleteElement(SeqList *L, int posi)
{
    if (posi < 1 || posi > L->length)
        cout << "Invalid Position" << endl;
    else{
        for (int i = posi - 1; i < L->length - 1; i++)
        {
            L->data[i] = L->data[i + 1];
        }
        L->length--;
    }
    return 1;
}

// 查找顺序表中的某个元素，并返回索引
int FindElement(SeqList *L, ElementType e)
{
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == e)
            return i + 1;
    }
    return 0;
}

// 输出顺序表元素
void output(SeqList *L)
{
    for (int i = 0; i<L->length; i++)
    {
        cout << L->data[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    SeqList L;
    initList(& L, 10, 20, 30);
    output(& L);
    AddElement(& L, 99, 3);
    output(& L);
    DeleteElement(& L, 1);
    output(& L);
    int index = FindElement(& L, 30);
    cout << index << endl;

    return 0;
}
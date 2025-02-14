#include <iostream>

using namespace std;

#define Maxsize 100
typedef int ElementType;

struct SeqList{
    /*
    注意：声明了 ElementType 类型的指针 data 但没有初始化，此时 data 指向随机地址，
    访问 data 的元素会出现 Segmentation fault 段错误
    */ 
    ElementType * data;
    int length;
};

// 顺序表初始化，基于动态内存分配，C语言
// SeqList* initList()
// {
//     SeqList *L = (SeqList *)malloc(sizeof(SeqList));
//     L->data = (ElementType *)malloc(sizeof(ElementType) * Maxsize);
//     L->length = 0;
//     return L;
// }

// 顺序表初始化，基于动态内存分配，C++
SeqList* initList()
{
    SeqList *L = new SeqList(); // 申请一个 SeqList 类型的对象
    L->data = new ElementType[Maxsize]{};
    L->length = 0;
    return L;
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
    SeqList *L = initList();
    output(L);

    AddElement(L, 10);
    AddElement(L, 20);
    AddElement(L, 30);
    AddElement(L, 99, 3);
    output(L);

    DeleteElement(L, 1);
    output(L);

    int index = FindElement(L, 30);
    cout << index << endl;

    delete[] L->data;
    delete[] L;
    
    return 0;
}
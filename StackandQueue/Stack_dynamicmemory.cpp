/*
栈的顺序结构，基于动态内存分配
*/

#include <iostream>

using namespace std;

#define MaxSize 100

typedef int ElementType;
struct Stack{
    ElementType *data;
    int top; // 栈顶指针
};

// 栈的初始化
Stack* initStack()
{
    Stack *s = new Stack;
    s->data = new ElementType[MaxSize];
    s->top = -1;
    return s;
}

// 判断栈是否为空
bool isEmpty(Stack *s)
{
    if (s->top == -1)
    {
        cout << "空栈" << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

// 进栈（压栈）push
void push(Stack *s, ElementType e)
{
    if (s->top >= MaxSize-1)
    {
        cout << "栈满" << endl;
    }
    else{
        s->top++;
        s->data[s->top] = e;
    }
}

// 出栈 pop
void pop(Stack *s, ElementType *e)
{
    if (s->top == -1)
    {
        cout << "空栈" << endl;
    }
    *e = s->data[s->top];
    s->top--;
}

// 获取栈顶元素
void getTop(Stack *s, ElementType *e)
{
    if (s->top == -1)
    {
        cout << "空栈" << endl;
    }
    *e = s->data[s->top];
}

int main(int argc, char *argv[])
{
    Stack *s = initStack();
    push(s, 10);
    push(s, 20);
    push(s, 30);
    ElementType e;
    pop(s, &e);
    cout << e << endl;

    getTop(s, &e);
    cout << e << endl;

    return 0;
}
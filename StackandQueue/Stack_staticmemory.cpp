/*
栈的顺序结构
*/

#include <iostream>

using namespace std;

#define MaxSize 100

typedef int ElementType;
struct Stack{
    ElementType data[MaxSize];
    int top;
};

// 栈的初始化
void initStack(Stack *s)
{
    s->top = -1;
}

// 判断栈是否为空
bool isEmpty(Stack *s)
{
    if (s->top == -1)
    {
        std::cout << "空栈" << endl;
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
        cout << "空栈，无法出栈" << endl;
    }
    else
    {
        *e = s->data[s->top];
        s->top--;
    }
}

// 获取栈顶元素
void getTop(Stack *s, ElementType *e)
{
    if (s->top == -1)
    {
        cout << "空栈，无法获取栈顶元素" << endl;
    }
    else
    {
        *e = s->data[s->top];
    }
}

int main(int argc, char *argv[])
{
    Stack s;
    initStack(&s);
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    ElementType e;
    pop(&s, &e);
    pop(&s, &e);
    pop(&s, &e);
    cout << e << endl;

    getTop(&s, &e);
    cout << e << endl;

    return 0;
}
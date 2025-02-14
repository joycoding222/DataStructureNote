/*
栈的链式实现:头节点即栈顶，尾节点即栈底；
压栈：单链表的头插法；
出栈：删除掉单链表头节点后的第一个节点；
*/
#include <iostream>

using namespace std;

typedef int ElementType;
struct Stack{
    ElementType data;
    Stack *next;
};

// 栈的初始化
Stack* initStack()
{
    Stack *s = new Stack;
    s->data = 0;
    s->next = NULL;
    return s;
}

// 判断栈是否为空
bool isEmpty(Stack *s)
{
    if (s->next == NULL)
    {
        cout << "空栈" << endl;
        return 1;
    }
    else{
        return 0;
    }
}

// 进栈（压栈）push，相当于单链表的头插法
void push(Stack *s, ElementType e)
{
    Stack *p = new Stack;
    p->next = s->next;
    s->next = p;
    p->data = e;
}

// 出栈 pop，即删除头节点后的第一个节点
void pop(Stack *s, ElementType *e)
{
    if (s->next != NULL)
    {
        *e = s->next->data;
        Stack *p = s->next;
        s->next = p->next;
        delete p;
    }
    else
    {
        cout << "空栈" << endl;
    }
}

// 获取栈顶元素
void getTop(Stack *s, ElementType *e)
{
    if (s->next != NULL)
    {
        *e = s->next->data;
    }
    else
    {
        cout << "空栈" << endl;
    }
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
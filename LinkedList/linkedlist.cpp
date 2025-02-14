/*
链表：用一组任意的存储单元存储线性表的数据元素，这个存储单元可以是连续的，也可以是不连续的。
为了表示每个数据元素与其后继数据元素的逻辑关系，对数据元素来说，除了其本身的信息之外，还需要存储一个
指示其后继的信息。
这两部分信息组成数据元素的存储映像，称为节点 Node。
*/
#include <iostream>

using namespace std;

typedef int ElementType;
struct Node
{
    ElementType data;
    Node *next;
};

// 单链表的初始化
Node *initlist()
{
    Node *node = new Node; // 动态申请 Node 内存
    node->data = 0;
    node->next = NULL;
    return node;
}

// 单链表插入数据：头插法，在头节点后插入，L 是指向头节点的指针
// 头插法一定要注意顺序！！！
void insertHead(Node *L, ElementType e)
{
    Node *p = initlist();
    p->next = L->next; // p 指向 L 后的节点
    L->next = p;
    p->data = e;
}

// 单链表插入数据：尾插法，在尾节点后插入
void insertTail(Node *L, ElementType e)
{
    Node *tail = L;
    while (tail->next != NULL) // 查找到 tail 是指向尾节点
    {
        tail = tail->next;
    }
    Node *newnode = initlist();// 创建新节点
    newnode->data = e;
    tail->next = newnode; // tail 指向新节点
    newnode->next = NULL;
}

// 单链表在指定位置 posi 插入数据，插入后的位置是 posi
void insertNode(Node *L, ElementType e, int posi)
{
    // 找到第 posi-1 节点
    Node *p = L;
    for (int i = 0; i < posi-1; i++)
    {
        p = p->next;
    }
    // 插入新节点，位置是 posi
    Node *newnode = initlist();
    newnode->next = p->next;
    p->next = newnode;
    newnode->data = e;
}

// 删除节点
void deleteNode(Node *L, int posi)
{
    // 找到第 posi 个节点的前驱节点 p
    Node *p = L;
    for (int i = 0; i < posi-1; i++)
    {
        p = p->next;
    }

    Node *delnode = initlist();
    delnode = p->next; // L 保存要删除的节点信息
    p->next = delnode->next;
    delete delnode;
}

// 获取单链表长度
int getlength(Node *L)
{
    Node *p = L;
    int len = 0;
    while (p->next != NULL) // 不包括头节点
    {
        p = p->next;
        len++;
    }
    return len;
}

// 释放链表
void freeList(Node *L)
{
    Node *current = L->next; // 指向第一个节点
    Node *nextnode = initlist();

    while (current != NULL)
    {
        nextnode = current->next;
        delete current;
        current = nextnode;
    }
    delete nextnode;
    L->next = NULL;
}

// 遍历
void listNode(Node *L)
{
    Node *p = L->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 打印链表数据(My realization)
void output(Node *L)
{
    cout << L->data << " ";
    if (L->next != NULL)
    {
        L = L->next; // L 从头节点指向下一个节点
        output(L);
    }
}

int main(int argc, char *argv[])
{
    Node *node1 = initlist();
    
    insertHead(node1, 10);
    insertHead(node1, 20);
    insertHead(node1, 30);
    listNode(node1);

    insertTail(node1, 10);
    insertTail(node1, 20);
    insertTail(node1, 30);
    listNode(node1);

    insertNode(node1, 25, 6);
    listNode(node1);

    deleteNode(node1, 6);
    listNode(node1);

    cout << getlength(node1) << endl;

    freeList(node1);
    cout << getlength(node1) << endl;
    delete node1;

    Node *node2 = initlist();
    insertTail(node2, 10);
    insertTail(node2, 20);
    insertTail(node2, 30);
    listNode(node2);
    delete node2;

    return 0;
}
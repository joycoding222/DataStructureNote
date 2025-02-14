/*
双向链表的基本操作
*/
#include <iostream>

using namespace std;

typedef int ElementType;
struct Node{
    ElementType data;
    Node *prev; // 指向直接前驱的指针
    Node *next; // 指向直接后继的指针
};

// 初始化节点
Node* initlist()
{
    Node *head = new Node;
    head->data = 0;
    head->prev = NULL;
    head->next = NULL;
    return head;
}

// 头插法
void insertHead(Node *head, ElementType e)
{
    Node *newNode = initlist();
    newNode->data = e;
    newNode->next = head->next;
    newNode->prev = head;
    if (head->next != NULL)
    {
        head->next->prev = newNode;
    }
    head->next = newNode; // 这一操作必须在 head->next->prev = newNode; 之后
}

// 返回链表的尾节点
Node* get_tail(Node *head)
{
    Node *tail = head;
    while (tail->next != NULL) // 查找到 tail 指向尾节点
    {
        tail = tail->next;
    }
    return tail;
}

// 尾插法
Node* insertTail(Node *tail, ElementType e)
{
    Node *newNode = initlist();
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = NULL;
    newNode->data = e;
    return newNode;
}

// 在指定位置插入数据
void insertNode(Node *head, ElementType e, int posi)
{
    // 查找 posi 节点的前置节点
    Node *p = head;
    for (int i = 0; i < posi-1; i++)
    {
        p = p->next;
    }

    Node *newNode = new Node;
    newNode->data = e;
    newNode->prev = p;
    newNode->next = p->next;
    p->next->prev = newNode; // 注意顺序
    p->next = newNode;
}

// 删除节点
void deleteNode(Node *head, int posi)
{
    // 查找 posi 节点的前置节点
    Node *p = head;
    for (int i = 0; i < posi-1; i++)
    {
        p = p->next;
    }

    Node *delNode = p->next; // delNode 保存要删除的节点信息
    p->next = delNode->next;
    delNode->next->prev = p;

    delete delNode;
}

// 遍历
void listNode(Node *head)
{
    Node *p = head->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    Node *node1 = initlist();

    insertHead(node1, 10);
    insertHead(node1, 20);
    insertHead(node1, 30);
    listNode(node1);

    Node *tail = get_tail(node1);
    tail = insertTail(tail, 10);
    tail = insertTail(tail, 20);
    tail = insertTail(tail, 30);
    listNode(node1);

    insertNode(node1, 25, 6);
    listNode(node1);

    deleteNode(node1, 6);
    listNode(node1);

    return 0;
}
/*
Question:删除单链表的中间节点
Solution:
快慢指针，快指针指向第一个节点，慢指针指向头节点，快指针走两步，慢指针走一步，当快指针的下一个为空时，
慢指针指向了中间节点的前置节点
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

// 删除中间节点(单链表长度为奇数)
void deleteMiddleNode(Node *head)
{
    Node *fastPtr = head->next;
    Node *slowPtr = head;
    while (fastPtr->next != NULL)
    {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    } // slowPtr 指向中间节点的前置节点,slowPtr->next 时此时要删除的中间节点
    Node *delNode = slowPtr->next;
    slowPtr->next = delNode->next;
    delete delNode;
}
// 删除中间节点(单链表长度为偶数)
// void deleteMiddleNode(Node *head)
// {
//     Node *fastPtr = head;
//     Node *slowPtr = head;
//     while (fastPtr->next != NULL)
//     {
//         fastPtr = fastPtr->next->next;
//         slowPtr = slowPtr->next;
//     } // slowPtr 指向中间节点的前置节点,slowPtr->next 时此时要删除的中间节点
//     Node *delNode = slowPtr->next;
//     slowPtr->next = delNode->next;
//     delete delNode;
// }


int main(int argc, char *argv[])
{
    Node *head = initlist();
    insertTail(head, 1);
    insertTail(head, 2);
    insertTail(head, 3);
    insertTail(head, 4);
    insertTail(head, 5);
    insertTail(head, 6);
    insertTail(head, 7);
    listNode(head);

    deleteMiddleNode(head);
    listNode(head);

    return 0;
}
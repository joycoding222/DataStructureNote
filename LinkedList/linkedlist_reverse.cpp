/*
Question:已知一单链表，要求反转链表
Solution:
声明三个指针：firstPtr,secondPtr,thirdPtr;分别指向空节点、第一个节点、第一个节点的下一个节点；
令secondPtr指向的节点指向空节点，然后三个指针同时向前移动一个节点，
此时secondPtr指向的节点指向空节点后的第一个节点，以此类推，直到secondPtr指向单链表末尾的空节点，
并将此时的空节点初始化为反转后链表的头节点
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

// 反转链表
// Node* reverse(Node *L)
// {
//     Node *firstPtr = L;
//     Node *secondPtr = firstPtr->next;
//     Node *thirdPtr = secondPtr->next;
//     secondPtr->next = NULL;
//     while (thirdPtr != NULL)
//     {
//         firstPtr = secondPtr;
//         secondPtr = thirdPtr;
//         thirdPtr = thirdPtr->next;
//         secondPtr->next = firstPtr;
//     } // thirdPtr 指向单链表的尾节点的下一个节点（空节点），反转后链表的头节点
//     thirdPtr= initlist();
//     thirdPtr->next = secondPtr;

//     return thirdPtr;
// }
Node *reverse(Node *head)
{
    Node *firstPtr = NULL;
    Node *secondPtr = head->next;
    Node *thirdPtr;
    while (secondPtr != NULL)
    {
        thirdPtr = secondPtr->next;
        secondPtr->next = firstPtr;
        firstPtr = secondPtr;
        secondPtr = thirdPtr;
    }
    Node *hd = initlist(); // hd 是反转后链表的头节点
    hd->next = firstPtr; // firstPtr 此时指向反转后链表的第一个节点
    return hd;
}

int main(int argc, char *argv[])
{
    Node *head = initlist();
    insertTail(head, 1);
    insertTail(head, 2);
    insertTail(head, 3);
    insertTail(head, 4);
    insertTail(head, 5);
    insertTail(head, 6);
    listNode(head);

    Node *reverse_linkedlist = reverse(head);
    listNode(reverse_linkedlist);

    return 0;
}
/*
Question:单链表应用2019
Solution:
1.找到中间节点，将链表从中间断开；
2.反转后半段链表；
3.将后半段链表依次插入前半段；
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
Node* reverse(Node *L)
{
    Node *firstPtr = L;
    Node *secondPtr = firstPtr->next;
    Node *thirdPtr = secondPtr->next;
    secondPtr->next = NULL;
    while (thirdPtr != NULL)
    {
        firstPtr = secondPtr;
        secondPtr = thirdPtr;
        thirdPtr = thirdPtr->next;
        secondPtr->next = firstPtr;
    } // thirdPtr 指向单链表的尾节点的下一个节点（空节点），反转后链表的头节点
    thirdPtr= initlist();
    thirdPtr->next = secondPtr;

    return thirdPtr;
}

// 寻找中间节点(单链表长度为偶数)，返回后半段链表的头节点
Node* findMiddleNode(Node *head)
{
    Node *fastPtr = head;
    Node *slowPtr = head;
    while (fastPtr->next != NULL)
    {
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    } // slowPtr 指向中间节点的前置节点,slowPtr->next 指向中间节点
    // head2 作为后半段链表的头节点
    Node *head2 = initlist();
    head2->next = slowPtr->next;
    slowPtr->next = NULL; // 截断前半段链表
    // 返回后半段链表的头节点
    return head2;
}

// 交叉插入，适用于两条链表的长度一致
Node* cutin(Node *head, Node *head2)
{
    Node *p1 = head->next;
    Node *p2 = p1;
    Node *q1 = head2->next;
    Node *q2 = q1;
    Node *newhead = initlist();
    newhead->next = p1;
    while (p2 != NULL)
    {
        p2 = p1->next;
        q2 = q1->next;
        p1->next = q1;
        q1->next = p2;
        p1 = p2;
        q1 = q2;        
    }
    // p2 q2 的作用是为了保存 p1->next 和 q1->next 的值
    return newhead;
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

    Node *head2 = findMiddleNode(head);
    listNode(head); // 前半段链表
    listNode(head2);// 后半段链表
    head2 = reverse(head2);
    listNode(head2);

    Node *head3 = cutin(head, head2);
    listNode(head3);

    return 0;
}
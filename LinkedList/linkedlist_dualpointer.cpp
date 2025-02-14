/*
Question:
单链表查找倒数第k个节点，如果成功输出节点的data并返回1；如果失败返回0；
Solution:
快慢双指针，快指针先走k步，即先向前移动k个节点，然后快慢指针一起移动，当快指针指向空时，
慢指针指向倒数第k个节点
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

// 使用双指针法获取单链表的倒数第 k 个元素
ElementType dualPointer(Node *L, int k)
{
    Node *fast = L->next;
    Node *slow = L->next;
    if (slow != NULL)
    {
        // fast 指针先走 k 步
        for (int i = 0; i < k; i++)
        {
            fast = fast->next;
        }
        // fast 和 slow 指针同时前进，fast 指针为空时，slow 指向倒数第k个节点
        while (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
        cout << "倒数第" << k << "个节点的值为:" << slow->data << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    Node * head = initlist();
    insertTail(head, 1);
    insertTail(head, 2);
    insertTail(head, 3);
    insertTail(head, 4);
    insertTail(head, 5);
    insertTail(head, 6);
    listNode(head);

    dualPointer(head, 3);

    return 0;
}
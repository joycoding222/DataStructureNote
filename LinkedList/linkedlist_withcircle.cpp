/*
Question1:判断链表是否有环
Solution:
快慢指针相遇说明有
Question2:找到环的入口
Solution:
1.首先使用快慢指针判断是否有环；
2.若有环，对环中的节点计数：fast(slow)从重合位置出发，下一次相等时即走了一圈，环的节点数为count；
3.快慢指针指向链表的头节点，快指针先走 count 步，然后快慢指针同时出发，相遇的节点即环的入口；
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

// 构造循环链表1 2 3 4 5 6 7 8 3 4 ...
Node* create_circularlinkedlist()
{
    Node *head = initlist();
    insertTail(head, 1);
    insertTail(head, 2);
    insertTail(head, 3);
    insertTail(head, 4);
    insertTail(head, 5);
    insertTail(head, 6);
    insertTail(head, 7);
    insertTail(head, 8);
    Node *tail = head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    } // tail 是尾节点

    Node *circleNode = head;
    for (int i = 0; i < 3; i++)
        circleNode = circleNode->next; // circleNode 是环的入口
    // 尾节点指向环的入口
    tail->next = circleNode;

    Node *p = circleNode->next;
    while (p != circleNode)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;

    return head;
}

// 判断链表是否有环
bool isCycle(Node *head)
{
    Node *fast = head;
    Node *slow = head;
    while (fast != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
            return true;
    }
    return false;
}

// 找到环的入口
Node *findEntrance(Node *head)
{
    Node *fast = head;
    Node *slow = head;

    while (fast != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {   // 有环
            Node *p = slow->next;
            int count = 1; // 环的节点计数
            while (p != slow)
            {
                p = p->next;
                count++;
            }
            // 快慢指针指向头节点
            fast = head;
            slow = head;
            // 快指针先走 count 步
            for (int i = 0; i < count; i++)
            {
                fast = fast->next;
            }
            // 快慢指针再次相遇的节点是环的入口
            while (fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }

            cout << slow->data << endl;
            return slow;
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    Node *head = create_circularlinkedlist();
    cout << isCycle(head) << endl;
    findEntrance(head);
    return 0;
}
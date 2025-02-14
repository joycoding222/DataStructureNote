/*
example3:
删除绝对值相同的节点
Solution:
用空间换时间，用一个数组记录所有节点的每个值出现的情况，出现记为1，否则为0；
当某个节点的值已经出现过时（数组对应元素为1），删除该节点；
当某个节点的值第一次出现时，将对应数组元素设为1
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

// 遍历，并输出最大值
ElementType returnMaxNode(Node *L)
{
    Node *p = L->next;
    ElementType max_abs = 0;
    // 判断是否为空链表
    if (p != NULL)
    {
        max_abs = abs(p->data);
    }
    else
    {
        return 0;
    }

    while (p != NULL)
    {
        ElementType max_cur = abs(p->data);
        if (max_abs < max_cur)
        {
            max_abs = max_cur;
        }
        p = p->next;
    }
    return max_abs;
}

// 删除绝对值相同的节点
void removeNode(Node *L)
{
    // 动态分配数组并初始化为0
    ElementType *record = new ElementType[returnMaxNode(L) + 1]{};
    Node *p = L;
    while (p->next != NULL) // p->next 是操作的节点
    {
        int index = abs(p->next->data);

        // 如果已经记录了该节点的值，则删除该节点（不需要单独移动指针）
        if (record[index] == 1)
        {
            Node *delNode = p->next;
            p->next = delNode->next;
            delete delNode;
        }
        else
        {
            record[index] = 1;
            p = p->next;
        }
    }
    delete []record;
}

int main(int argc, char *argv[])
{
    Node * head = initlist();
    insertTail(head, 21);
    insertTail(head, -15);
    insertTail(head, 15);
    insertTail(head, 7);
    insertTail(head, 15);
    listNode(head);
    cout << returnMaxNode(head) << endl;

    removeNode(head);
    listNode(head);

    return 0;
}
/*
队列的链式结构:
队列是一种先进先出的线性表，从队尾入队，从队头出队，采用单链表结构时，
表尾相当于队尾，数据从队尾入队，采用尾插法；
表头相当于队头，数据从队头出队；
*/
#include <iostream>

using namespace std;

typedef int ElementType;

struct QueueNode{
    ElementType data;
    QueueNode *next;
};

struct Queue{
    QueueNode *front;
    QueueNode *rear;
};

// 队列初始化
Queue* initQueue()
{
    Queue *q = new Queue;
    QueueNode *node = new QueueNode;
    node->data = 0;
    node->next = NULL;
    q->front = node;
    q->rear = node;
    return q;
}

// 判断队列是否为空
bool isEmpty(Queue *q)
{
    if (q->front == q->rear)
    {
        cout << "空队列" << endl;
        return 1;
    }
    else{
        return 0;
    }
}

// 入队，单链表的尾插法，认为头节点是队头位置，尾节点是队尾位置
void InQueue(Queue *q, ElementType e)
{
    QueueNode *newnode = new QueueNode;
    newnode->data = e;
    newnode->next = NULL;
    q->rear->next = newnode;
    q->rear = newnode;
}

// 出队，队头位置是链表的头节点一边，即释放掉头节点后的第一个节点
ElementType OutQueue(Queue *q)
{
    if (isEmpty(q))
    {
        cout << "空队列，无法出队" << endl;
        return -1;
    }
    QueueNode *delNode = q->front->next; // q->front 相当于单链表的头节点
    q->front->next = delNode->next;
    if (q->rear == delNode) // 如果队列尾指针指向被删除的节点（即队列除头节点只有一个节点）
    {
        q->rear = q->front;
    }
    ElementType delData = delNode->data;
    delete delNode;
    return delData;
}

// 获取队头元素
ElementType getHead(Queue *q)
{
    if (isEmpty(q))
    {
        cout << "空队列" << endl;
        return -1;
    }
    return q->front->next->data;
}

// 遍历
void listQueue(Queue *q)
{
    QueueNode *current = q->front->next;
    if (current == NULL)
    {
        cout << "空队列" << endl;
        return;
    }
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    Queue *q = initQueue();
    InQueue(q, 10);
    InQueue(q, 20);
    InQueue(q, 30);
    InQueue(q, 40);
    InQueue(q, 50);
    listQueue(q);

    cout << OutQueue(q) << endl;
    cout << OutQueue(q) << endl;

    cout << getHead(q) << endl;

    return 0;
}
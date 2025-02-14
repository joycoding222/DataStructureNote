/*
循环队列的实现
队列满：(q->rear + 1) % MaxSize == q->front
入队后的队尾：(q->rear + 1) % MaxSize
出队后的队头：(q->front + 1) % MaxSize
*/
#include <iostream>

using namespace std;

#define MaxSize 10

typedef int ElementType;

/* 动态分配内存 */
struct Queue{
    ElementType *data;
    int front;
    int rear;
};

Queue* initQueue()
{
    Queue *q = new Queue;
    q->data = new ElementType[MaxSize];
    q->front = 0;
    q->rear = 0;
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

// 出队
ElementType OutQueue(Queue *q)
{
    if (q->front == q->rear)
    {
        cout << "空队列" << endl;
        return 0;
    }
    else{
        ElementType e = q->data[q->front];
        q->front = (q->front + 1) % MaxSize;
        return e;
    }
}

// 入队，循环队列的入队操作是将 q->rear 改成： (q->rear + 1) % MaxSize
void InQueue(Queue *q, ElementType e)
{
    if ((q->rear + 1) % MaxSize == q->front) // 队列满
    {
        cout << "队列满" << endl;
    }
    else{
        q->data[q->rear] = e;
        q->rear = (q->rear + 1) % MaxSize;
    }
}

// 获取队头数据
void getHead(Queue *q, ElementType *e)
{
    if (q->front == q->rear)
    {
        cout << "空队列" << endl;
    }
    else
    {
        *e = q->data[q->front];
    }
}

// 遍历
void listQueue(Queue *q)
{
    int front = q->front;
    int rear = q->rear;
    if (front == rear)
    {
        cout << "空队列" << endl;
    }
    else{
        while (front != rear)
        {
            cout << q->data[front] << " ";
            front = (front + 1) % MaxSize;
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    Queue *q = initQueue();
    listQueue(q);

    InQueue(q, 10);
    InQueue(q, 20);
    InQueue(q, 30);
    InQueue(q, 40);
    InQueue(q, 50);
    listQueue(q);

    cout << OutQueue(q) << endl;
    cout << OutQueue(q) << endl;
    listQueue(q);

    InQueue(q, 60);
    listQueue(q);

    return 0;
}
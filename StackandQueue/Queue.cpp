/*
队列的顺序结构
*/
#include <iostream>

using namespace std;

#define MaxSize 5

typedef int ElementType;

/* 动态分配内存 */
// struct Queue{
//     ElementType *data;
//     int front;
//     int rear;
// };

// Queue* initQueue()
// {
//     Queue *q = new Queue;
//     q->data = new ElementType[MaxSize];
//     q->front = 0;
//     q->rear = 0;
//     return q;
// }

// 静态存储的队列中，rear 当作数组下标
struct Queue{
    ElementType data[MaxSize];
    int front; // 队头，删除端
    int rear;  // 队尾，插入端
};

// 队列的初始化
void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
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
        q->front++;
        return e;
    }
}

// 入队
void InQueue(Queue *q, ElementType e)
{
    // 队尾有空位
    if (q->rear < MaxSize)
    {
        q->data[q->rear] = e;
        q->rear++;
    }
    else // 队尾无空位
    {
        // 队头有空位
        if (q->front > 0)
        {
            // 调整队列
            int step = q->front;
            for (int i = step; i < q->rear; i++)
            {
                q->data[i - step] = q->data[i];
                cout << q->data[i - step] << "(已调整)";
            }
            cout << endl;
            q->front = 0;
            q->rear -= step;
            // 调正队列后入队
            q->data[q->rear] = e;
            q->rear++;
        }
        else // 队头无空位
        {
            cout << "队列满" << endl;
        }
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
            front++;
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    Queue q;
    initQueue(&q);
    listQueue(&q);

    InQueue(&q, 10);
    InQueue(&q, 20);
    InQueue(&q, 30);
    InQueue(&q, 40);
    InQueue(&q, 50);
    listQueue(&q);

    cout << OutQueue(&q) << endl;
    cout << OutQueue(&q) << endl;
    listQueue(&q);

    // ElementType e;
    // getHead(&q, &e);
    // cout << e << endl;

    InQueue(&q, 60);
    listQueue(&q);

    return 0;
}
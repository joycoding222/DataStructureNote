/*
二叉树的层序遍历：
1.二叉树根结点入队；
2.如果队列不为空，对队列元素计数；
3.当队列元素大于0时，队头元素出队列，并打印结点内容；
3.如果出队的元素有左孩子，左孩子入队；如果有右孩子，右孩子入队；
4.重复步骤3，判断队列元素是否大于0，直到队列元素等于0；然后二叉树的深度加1；
5.重复步骤2，直到队列为空；
*/
#include <iostream>

using namespace std;

typedef char ElementType;

struct TreeNode
{
    ElementType data;
    TreeNode *leftchild;
    TreeNode *rightchild;
};

typedef TreeNode* BinaryTree;

struct QueueNode{
    TreeNode *Tree;
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

    // node->Tree->data = 0;
    // node->Tree->leftchild = NULL;
    // node->Tree->rightchild = NULL;
    node->Tree = NULL; // 这里不太理解，为什么注释掉的是野指针？？？
    node->next = NULL;
    // 上面的代码可以简化：
    // q->front = q->rear = new QueueNode{NULL, NULL};

    q->front = node;
    q->rear = node;

    return q;
}

// 判断队列是否为空
bool isEmpty(Queue *q)
{
    if (q->rear == q->front)
    {
        return true;
    }
    return false;
}

// 入队
void InQueue(Queue *q, TreeNode *e)
{
    QueueNode *newnode = new QueueNode;
    newnode->Tree = e; // 树的结点入队
    newnode->next = NULL;
    q->rear->next = newnode;
    q->rear = newnode;
}

// 出队
void OutQueue(Queue *q, TreeNode **e)
{
    if (isEmpty(q))
    {
        cout << "空队列，无法出队" << endl;
        return;
    }
    QueueNode *delnode = q->front->next;// q->front 是单链表的头节点
    q->front->next = delnode->next;

    (*e) = delnode->Tree; // 出队的元素

    if (q->rear == delnode)
    {
        q->rear = q->front;
    }
    delete delnode;
}

// 确定队列中元素个数
int QueueSize(Queue *q)
{
    if (q->front == q->rear)
    {
        return 0;
    }
    int size = 0;
    QueueNode *curr = q->front;
    while (curr != q->rear)
    {
        curr = curr->next;
        size++;
    }
    return size;
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
        cout << current->Tree->data << " ";
        current = current->next;
    }
    cout << endl;
}


// 创建二叉树
void createBinaryTree(BinaryTree *T, const char *str, int &idx)
{
    ElementType ch = str[idx++];
    if (ch == '#')
    {
        (*T) = NULL;
    }
    else
    {
        // 前序遍历的顺序造树，需要注意的是：造树的顺序和给定的遍历的顺序应一致
        *T = new TreeNode;
        (*T)->data = ch;
        createBinaryTree(&(*T)->leftchild, str, idx);
        createBinaryTree(&(*T)->rightchild, str, idx);
    }
}

// 前序遍历
void preOrder(BinaryTree T)
{
    if (T == NULL)
    {
        return;
    }
    cout << T->data << " ";
    preOrder(T->leftchild);
    preOrder(T->rightchild);
}

// 层序遍历
void LevelOrder(BinaryTree T)
{
    int Depth = 0; // 二叉树的深度
    TreeNode *root = T;
    Queue *q = initQueue(); // 创建队列
    InQueue(q, root);       // 树的根结点入队

    while (!isEmpty(q))
    {
        int count = QueueSize(q); // 对当前队列中的元素进行计数
        while (count > 0)
        {
            TreeNode *curr; // curr 是队头元素，记录出队元素
            OutQueue(q, &curr);
            cout << curr->data << " ";
            if (curr->leftchild != NULL)
            {
                InQueue(q, curr->leftchild);
            }
            if (curr->rightchild != NULL)
            {
                InQueue(q, curr->rightchild);
            }
            count--; // count 只对第一次入队的元素计数！！！
        }
        Depth ++;
    }
    cout << endl;
    cout << "Depth: " << Depth << endl;
}

int main(int argc, char *argv[])
{
    int idx = 0;
    const char * str = "ABDH#K###E##CFI###G#J##";

    BinaryTree T;
    createBinaryTree(&T, str, idx);

    preOrder(T);
    cout << endl;

    LevelOrder(T);

    return 0;    
}
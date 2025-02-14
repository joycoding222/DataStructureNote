/*
线索二叉树：利用叶子结点的空余空间记录在指定遍历顺序下的前驱后继；
左孩子放前驱；右孩子放后继
*/
#include <iostream>

using namespace std;

typedef char ElementType;

struct ThreadNode
{
    ElementType data;
    ThreadNode *leftchild;
    ThreadNode *rightchild;
    /*
    Ltag 为0表示 leftchild 指向该结点的左孩子；
    Ltag 为1表示 leftchild 指向该结点的前驱(指定遍历顺序)；
    Rtag 为0表示 rightchild 指向该结点的右孩子；
    Rtag 为1表示 rightchild 指向该结点的后继(指定遍历顺序);
    总结： 0表示结点，1表示线索
    */
    int Ltag;
    int Rtag;
};

typedef ThreadNode* ThreadTree;

// 前序遍历
void preOrder(ThreadNode *T)
{
    if (T == NULL)
    {
        return;
    }
    cout << T->data << " ";
    preOrder(T->leftchild);
    preOrder(T->rightchild);
}

// 创建二叉树
void createThreadTree(ThreadTree *T, const char *str, int &idx)
{
    ElementType ch = str[idx++];
    if (ch == '#')
    {
        (*T) = NULL;
    }
    else
    {
        // 前序遍历的顺序造树，需要注意的是：造树的顺序和给定的遍历的顺序应一致
        *T = new ThreadNode;
        (*T)->data = ch;
        createThreadTree(&(*T)->leftchild, str, idx);
        if ((*T)->leftchild != NULL)
        {
            (*T)->Ltag = 0; // 0 表示指向结点
        }
        createThreadTree(&(*T)->rightchild, str, idx);
        if ((*T)->rightchild != NULL)
        {
            (*T)->Rtag = 0;
        }
    }
}

// 线索化
void threading(ThreadTree T, ThreadNode *& prev)
{
    if (T == NULL)
    {
        return;
    }
    else
    {
        threading(T->leftchild, prev);

        if (T->leftchild == NULL)
        {
            // 添加前驱线索
            T->Ltag = 1;
            T->leftchild = prev;
        }
        if (prev->rightchild == NULL)
        {
            // 添加后继线索
            prev->Rtag = 1;
            prev->rightchild = T;
        }
        // 更新prev
        prev = T;

        threading(T->rightchild, prev);
    }
    // 叶子结点的左线索在叶子结点作为T时添加；右线索在叶子结点作为prev时添加；
}

// 二叉树中序遍历线索化
void inOrederThreading(ThreadTree *head, ThreadTree T, ThreadNode * &prev)
{
    (*head) = new ThreadNode;
    (*head)->Ltag = 0;
    (*head)->Rtag = 1;
    // 遍历结果的最后一个结点暂时未知，故指向自身
    (*head)->rightchild = (*head);

    if (T == NULL)
    {
        (*head)->leftchild = (*head);
    }
    else
    {
        // 头结点的leftchild指向二叉树的根
        (*head)->leftchild = T;
        prev = (*head);

        // 线索化
        threading(T, prev);

        // 最后一个结点线索化
        prev->rightchild = (*head);
        prev->Rtag = 1;

        // 头结点的rightchild指向遍历的最后一个结点
        (*head)->rightchild = prev;
    }
}

// 基于线索遍历
void inOrder(ThreadNode *T)
{
    // T 是头指针
    ThreadNode *curr = T;
    curr = T->leftchild; // 找到根结点

    while (curr != T)
    {
        // 如果有左孩子，一直向下挖
        while (curr->Ltag == 0)
        {
            curr = curr->leftchild;
        }
        cout << curr->data << " ";

        // 根据线索转到后继
        while (curr->Rtag == 1 && curr->rightchild != T)
        {
            curr = curr->rightchild;
            cout << curr->data << " ";
        }
        curr = curr->rightchild;
    }
    cout << endl;    
}

int main(int argc, char *argv[])
{
    int idx = 0;
    const char *str = "ABDH##I##EJ###CF##G##";

    ThreadTree T;
    ThreadNode *head;
    ThreadNode *prev;
    // 创建二叉树
    createThreadTree(&T, str, idx);

    // 线索化,为啥是&head??
    inOrederThreading(&head, T, prev);

    // 基于线索遍历
    inOrder(head);

    return 0;
}
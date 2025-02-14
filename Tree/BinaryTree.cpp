/*
二叉树的链式结构：
由于顺序结构的二叉树可能比较浪费空间，因此采用链式结构
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

// 构建二叉树(我的实现：手动插入结点)
TreeNode* buildTree(ElementType x)
{
    TreeNode *T = new TreeNode;
    T->data = x;
    T->leftchild = NULL;
    T->rightchild = NULL;
    return T;
}

// 二叉树左插入
TreeNode* buildLeft(TreeNode *T, ElementType x)
{
    // 向根结点T的左侧插入结点L
    TreeNode *L = new TreeNode;
    L->data = x;
    L->leftchild = NULL;
    L->rightchild = NULL;
    T->leftchild = L;
    return L;
}

// 二叉树右插入
TreeNode* buildRight(TreeNode *T, ElementType x)
{
    // 向根结点的右侧插入结点R
    TreeNode *R = new TreeNode;
    R->data = x;
    R->leftchild = NULL;
    R->rightchild = NULL;
    T->rightchild = R; 
    return R;   
}

// 二叉树的遍历--前序遍历
// A B D H K E C F I G J
void preOrder(TreeNode* T)
{
    if (T == NULL)
    {
        // cout << "NULL" << " ";
        return;
    }
    cout << T->data << " ";
    preOrder(T->leftchild);
    preOrder(T->rightchild);
}

// 二叉树的遍历--中序遍历
// H K D B E A I F C G J
void inOreder(TreeNode* T)
{
    if (T == NULL)
    {
        return;
    }
    inOreder(T->leftchild);
    cout << T->data << " ";
    inOreder(T->rightchild);
}

// 二叉树的遍历--后序遍历
// K H D E B I F J G C A
void postOreder(TreeNode* T)
{
    if (T == NULL)
    {
        return;
    }
    postOreder(T->leftchild);
    postOreder(T->rightchild);
    cout << T->data << " ";
}

// 构建二叉树（按照视频中前序遍历的方法）
void createTree(BinaryTree *T, const char *str, int & idx) // 传递指针的指针
{
    /*
    为什么该函数的参数是指针的指针：
    cpp中默认参数传递是值传递，即pass by value，当直接传递指针，子函数内部实际上是传递指针的复制，
    在子函数中修改它并不会影响外部指针的值。因此，如果希望通过子函数修改指针的值，
    需要传递指针的指针，或指针的引用
    */
    ElementType ch;
    ch = str[idx++];
    if (ch == '#')
    {
        *T = NULL; // *T是TreeNode类型的指针
    }
    else{
        *T = new TreeNode;
        (*T)->data = ch;
        createTree(&(*T)->leftchild, str, idx);
        createTree(&(*T)->rightchild, str, idx);
    }
}

void createTree(TreeNode *&T, const char *str, int & idx) // 传递指针的引用
{
    ElementType ch;
    ch = str[idx++];
    if (ch == '#')
    {
        T = NULL; // *T是TreeNode类型的指针
    }
    else{
        T = new TreeNode;
        T->data = ch;
        createTree(T->leftchild, str, idx);
        createTree(T->rightchild, str, idx);
    }
}

int main(int argc, char *argv[])
{
    // 构建二叉树
    // TreeNode *T = buildTree('A');
    // TreeNode *L21 = buildLeft(T, 'B');
    // TreeNode *R21 = buildRight(T, 'C');
    // TreeNode *L31 = buildLeft(L21, 'D');
    // TreeNode *R31 = buildRight(L21, 'E');
    // TreeNode *L32 = buildLeft(R21, 'F');
    // TreeNode *R32 = buildRight(R21, 'G');
    // TreeNode *L41 = buildLeft(L31, 'H');
    // TreeNode *L42 = buildLeft(L32, 'I');
    // TreeNode *R41 = buildRight(R32, 'J');
    // TreeNode *R51 = buildRight(L41, 'K');

    int idx = 0;
    const char *str = "ABDH#K###E##CFI###G#J##";

    BinaryTree T;
    createTree(T, str, idx);

    preOrder(T);
    cout << endl;
    inOreder(T);
    cout << endl;
    postOreder(T);
    cout << endl;

    return 0;
}
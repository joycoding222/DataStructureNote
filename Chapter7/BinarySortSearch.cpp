/*
二叉排序树：
二叉排序树是空树或非空树，当二叉排序树为非空树时，需要满足一下条件：
1.若其左子树非空，则左子树上所有结点的值均小于根结点；
2.若其右子树非空，则右子树上所有结点的值均大于等于根结点；
2.其左子树右子树分别各为一棵二叉排序树；
*/

#include <iostream>

using namespace std;

typedef int KeyType;

struct ElementType{
    KeyType key;
};
struct TreeNode
{
    ElementType data;
    TreeNode *leftchild;
    TreeNode *rightchild;
};

typedef TreeNode* Tree;

// 查找
TreeNode *BinarySortSearch(TreeNode *root, KeyType key)
{
    if (root == NULL || key == root->data.key) // 返回空指针或查找到的结点
    {
        return root;
    }
    if (key < root->data.key)
    {
        return BinarySortSearch(root->leftchild, key);
    }
    else
    {
        return BinarySortSearch(root->rightchild, key);
    }
}

// 生成
TreeNode *BinarySortAdd(TreeNode *root, KeyType key)
{
    if (root == NULL)
    {
        TreeNode *node = new TreeNode{{key}, NULL, NULL};
        return node;
    }
    if (key < root->data.key)
    {
        root->leftchild = BinarySortAdd(root->leftchild, key);
    }
    else if (key > root->data.key)
    {
        root->rightchild = BinarySortAdd(root->rightchild, key);
    }
    // key 和顶点值相等，不插入
    return root;
}

// 中序遍历
void inOrder(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->leftchild);
    cout << root->data.key << " ";
    inOrder(root->rightchild);
}

int main(int argc, char *argv[])
{
    TreeNode *root = NULL;
    root = BinarySortAdd(root, 42);
    root = BinarySortAdd(root, 24);
    root = BinarySortAdd(root, 12);
    root = BinarySortAdd(root, 37);
    root = BinarySortAdd(root, 55);

    inOrder(root);

    return 0;
}
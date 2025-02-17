/*
图的最小生成树 Minimum Spanning Tree
*/
#include <iostream>
#include <climits> // 使用 INT_MAX 表示无穷

using namespace std;

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 10

struct Matrix_Graph
{
    VertexType vertex[MAXSIZE];     // 保存顶点
    EdgeType arc[MAXSIZE][MAXSIZE]; // 保存边
    int vertex_num;
    int edge_num;
};

// 记录被访问过的顶点
int visited[MAXSIZE];
int queue[MAXSIZE]; // BFS用的队列数组
int front = 0;      // 队头指针
int rear = 0;       // 队尾指针

// 创建图
void create_graph(Matrix_Graph *G)
{
    G->vertex_num = 9;
    G->edge_num = 15;
    G->vertex[0] = 'A';
    G->vertex[1] = 'B';
    G->vertex[2] = 'C';
    G->vertex[3] = 'D';
    G->vertex[4] = 'E';
    G->vertex[5] = 'F';
    G->vertex[6] = 'G';
    G->vertex[7] = 'H';
    G->vertex[8] = 'I';

    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (i == j)
            {
                G->arc[i][j] = 0;
            }
            else
            {
                G->arc[i][j] = INT_MAX;
            }
        }
    }
    // 邻接矩阵
    G->arc[0][1] = G->arc[1][0] = 10; // AB
    G->arc[0][5] = G->arc[5][0] = 11; // AF

    G->arc[1][2] = G->arc[2][1] = 18; // BC
    G->arc[1][6] = G->arc[6][1] = 16; // BG
    G->arc[1][8] = G->arc[8][1] = 12; // BI

    G->arc[2][3] = G->arc[3][2] = 22; // CD
    G->arc[2][8] = G->arc[8][2] = 8;  // CI

    G->arc[3][4] = G->arc[4][3] = 20; // DE
    G->arc[3][6] = G->arc[6][3] = 24; // DG
    G->arc[3][7] = G->arc[7][3] = 16; // DH
    G->arc[3][8] = G->arc[8][3] = 21; // DI

    G->arc[4][5] = G->arc[5][4] = 26; // EF
    G->arc[4][7] = G->arc[7][4] = 7;  // EH

    G->arc[5][6] = G->arc[6][5] = 17; // FG

    G->arc[6][7] = G->arc[7][6] = 19; // GH
};

// Prime 最小生成树
void Prime(Matrix_Graph *G)
{
    int weight[MAXSIZE]; // 候选边，0表示已经访问过，非0表示候选边的权值
    int parent[MAXSIZE]; // 值表示出发点，下标表示到达点

    // 寻找结点0的路径
    for (int i = 0; i < G->vertex_num; i++)
    {
        // 把出发点所有路径的权重放入候选中
        weight[i] = G->arc[0][i]; // weight 等于0表示已经加入生成树
        parent[i] = 0;            // 记录每个顶点是由哪个父节点加入生成树的
    }

    for (int i = 1; i < G->vertex_num; i++) // 生成n-1条边
    {
        int min = INT_MAX;
        int j = 0;
        int current = 0;

        // 找到权重最小的边并连接
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (weight[j] != 0 && weight[j] < min)
            {
                min = weight[j];
                current = j;
            }
        } // current 是找到的下一个加入生成树的结点

        // 输出边：父结点->当前结点
        cout << G->vertex[parent[current]] << G->vertex[current] << " ";

        weight[current] = 0; // 表示 current 已加入生成树

        // 找到新的结点并连接
        for (j = 0; j < G->vertex_num; j++)
        {
            if (weight[j] != 0 && G->arc[current][j] < weight[j])
            {
                weight[j] = G->arc[current][j]; // 加入新的候选
                parent[j] = current;            // 更新父节点
            }
        }
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    Matrix_Graph G;
    create_graph(&G);

    Prime(&G);

    cout << INT_MAX << endl;
    return 0;
}
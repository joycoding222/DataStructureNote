/*
图的最小生成树 Minimum Spanning Tree:
Prime 算法、 Kruskal 算法
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

struct Edge{
    int begin;
    int end;
    int weight;
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
    int weight[MAXSIZE]; // 候选边，0表示该结点已经加入生成树，非0表示候选边的权值
    int parent[MAXSIZE]; // 下标index表示子节点，parent[index]表示父节点

    // 初始化所有顶点到起点 A 的权值和父节点
    for (int i = 0; i < G->vertex_num; i++)
    {
        // 把出发点所有路径的权重放入候选中
        weight[i] = G->arc[0][i]; // weight 等于0表示已经加入生成树
        parent[i] = 0;            // 记录每个顶点是由哪个父节点加入生成树的，暂时将所有结点的父节点初始化为A
    }

    weight[0] = 0; // 结点 A 已加入最小生成树

    for (int i = 1; i < G->vertex_num; i++) // 生成n-1条边，n即图中顶点的数量
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

        // 更新邻接结点的权值和父节点
        for (j = 0; j < G->vertex_num; j++)
        {
            if (weight[j] != 0 && G->arc[current][j] < weight[j])
            {
                weight[j] = G->arc[current][j]; // 更新更小的权值
                parent[j] = current;            // 更新父节点为 current
            }
        }
    }
    cout << endl;
    /*
    Prime 算法总结：
    1.weight数组表示当前可供选择的结点，0表示已加入生成树，INT_MAX表示与生成树中的结点无连线，
    其余数值表示权重；
    2.parent数组记录结点之间的连线:parent[index]表示父节点，Index表示子节点；
    3.循环条件：生成树的n-1条边；
    */
}

// 交换权值不同的两条边
void swap(Edge* edge, int i, int j)
{
    Edge temp = edge[i];
    edge[i] = edge[j];
    edge[j] = temp;
}

// 边的权值升序排序
void sortEdge(Edge* edge, int edge_num)
{
    for (int i = 0; i < edge_num; i++)
    {
        for (int j = i+1; j < edge_num; j++)
        {
            if (edge[i].weight > edge[j].weight)
            {
                swap(edge, i, j);
            }
        }
    }
}

// find 查找根结点
int find(int* parent, int i)
{
    // deepseek 修改后：
    if (parent[i] < 0)
    {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
    // 课程中：
    // while ( parent[i] > 0)
    // {
    //     i = parent[i];
    // }
    // return i;    
}

// Kruskal 最小生成树
void Kruskal(Matrix_Graph G)
{
    Edge edge[G.edge_num]; // 保存图的所有边
    int k = 0; // edge 的索引

    // 初始化图的边构成的数组（仅邻接矩阵的上三角部分）
    for(int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i+1; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] < INT_MAX)
            {
                edge[k].weight = G.arc[i][j];
                edge[k].begin = i;
                edge[k].end = j;
                k++;
            }
        }
    }

    // 边的权值升序排序
    sortEdge(edge, G.edge_num);
    
    for (int i = 0; i < G.edge_num; i++)
    {
        cout << G.vertex[edge[i].begin] << G.vertex[edge[i].end] << " " << edge[i].weight << endl;
    }

    // 初始化结点的父节点
    int parent[MAXSIZE];
    for (int i = 0; i < G.vertex_num; i++)
    {
        parent[i] = -1;
    }

    // 生成树
    int root_begin, root_end;
    for (int i = 0; i < G.edge_num; i++)    // 生成n条边
    {
        /* 实际上最小生成树只需要G.vertex_num-1条边，因此可以声明变量edge_count，提前终止循环*/
        root_begin = find(parent, edge[i].begin);
        root_end = find(parent, edge[i].end);

        if (root_begin != root_end) // 保证无环路
        {
            cout << G.vertex[edge[i].begin] << G.vertex[edge[i].end] << " ";
            parent[root_begin] = root_end;
        }
    }
    /*
    Kruskal 算法总结：
    1.和 Prime 不同，Kruskal 根据边的权值大小进行排序，将权重从小到大的边依次加入生成树；
    2.parent[index]表示父节点，index 表示子节点；但与 Prime 不同，在寻找 index 父节点时可能出现
    parent[index] 已经保存了其他结点的情况，此时需要令 index = parent[index] 继续寻找更上一层的
    父节点；
    */
}

int main(int argc, char *argv[])
{
    Matrix_Graph G;
    create_graph(&G);

    Prime(&G);

    Kruskal(G);

    return 0;
}
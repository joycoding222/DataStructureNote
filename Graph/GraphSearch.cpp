/*
图的深度优先遍历：DFS
图的广度优先遍历：BFS
*/
#include <iostream>

using namespace std;

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 10

struct Matrix_Graph
{
    VertexType vertex[MAXSIZE]; // 保存顶点
    EdgeType arc[MAXSIZE][MAXSIZE]; // 保存边
    int vertex_num;
    int edge_num;
};

// 记录被访问过的顶点
int visited[MAXSIZE];
int queue[MAXSIZE]; // BFS用的队列数组
int front = 0;  // 队头指针
int rear = 0;   // 队尾指针

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
            G->arc[i][j] = 0;
        }
    }
    // 邻接矩阵的上半部分
    G->arc[0][1] = 1; // AB
    G->arc[0][5] = 1; // AF

    G->arc[1][2] = 1; // BC
    G->arc[1][6] = 1; // BG
    G->arc[1][8] = 1; // BI

    G->arc[2][8] = 1; // CI
    G->arc[2][3] = 1; // CD

    G->arc[3][4] = 1; // DE
    G->arc[3][6] = 1; // DG
    G->arc[3][7] = 1; // DH
    G->arc[3][8] = 1; // DI

    G->arc[4][5] = 1; // EF
    G->arc[4][7] = 1; // EH

    G->arc[5][6] = 1; // FG

    G->arc[6][7] = 1; // GH

    // 邻接矩阵下半部分
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
};

// 初始化访问标记
void initVisited(Matrix_Graph G)
{
    // 0表示未访问， 1表示已访问
    for (int i = 0; i < G.vertex_num; i++)
    {
        visited[i] = 0;
    }
}

// 深度优先遍历
void DFS(Matrix_Graph G, int start)
{
    // start 表示图的入口顶点在数组中的下标

    visited[start] = 1; // 记录已经访问的顶点

    cout << G.vertex[start] << " ";

    for (int j = 0; j < G.vertex_num; j++)
    {
        // 如果与当前结点有连线，并且未访问过
        if (G.arc[start][j] == 1 && visited[j] == 0)
        {
            DFS(G, j);
        }
    }
}

// 广度优先遍历
void BFS(Matrix_Graph G, int start)
{
    // 重置访问标记
    initVisited(G);
    front = 0;
    rear = 0;

    visited[start] = 1;  // 标记为已访问
    queue[rear] = start; // 入队
    rear++;

    while (front != rear) // 队列非空
    {
        int current = queue[front]; // 转到出队元素的那一层
        front++;                    // 队头元素出队
        cout << G.vertex[current] << " ";

        for (int j = 0; j < G.vertex_num; j++)
        {
            if (G.arc[current][j] == 1 && visited[j] == 0)
            {
                visited[j] = 1;
                queue[rear] = j;
                rear++;
            }
        }
    }
    /*
    总结：
    1.首先重置访问标记，队列指针；
    2.然后图的起点 start 入队，标记访问；
    3.当队列不为空，队头出队，记录出队元素，输出出队元素；
    4.遍历出队元素的邻接结点，如果有连线并且未被访问，则入队，并标记访问；
    5.重复步骤3；
    */
}

int main (int argc, char *argv[])
{
    Matrix_Graph G;
    create_graph(&G);
    
    // 重置访问标记
    initVisited(G);

    // 深度优先遍历
    DFS(G, 0); // 0 是图的入口顶点A的数组下标
    cout << endl;

    // 广度优先遍历(函数内部重置访问标记visited)
    BFS(G, 0);  // debug因为未重置visited数组导致没有输出...
    cout << endl;

    return 0;
}
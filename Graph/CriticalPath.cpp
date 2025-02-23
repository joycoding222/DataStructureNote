/*
关键路径：
在一个表示工程的带权有向图中，用顶点表示事件，用有向边表示活动，用边上的权值表示活动的时间，
这种有向图的边表示活动的网，叫做AOE(Activity on edge network)
最早发生时间：每一条路径发生时间的最大值；
最晚发生时间：每一条路径发生时间的最小值；
*/
#include <iostream>
#include <climits> // INT_MAX 表示无穷

using namespace std;

typedef int VertexType;
typedef int EdgeType;

#define MAXSIZE 100

// 邻接矩阵
struct Matrix_Graph
{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int edge_num;
    int vertex_num;
};

// 邻接表每个表的表头之外的结点
struct edgeNode
{
    int edge_vex;   // 邻接顶点索引
    edgeNode *next; // 指向下一个邻接顶点
    int weight;     // 权重(关键路径only)
};

// 邻接表每个表的表头
struct VertexNode
{
    int in;          // 入度
    VertexType data; // 顶点
    edgeNode *head;  // 邻接链表表头
};

// 表示所有顶点构成的一维数组
typedef VertexNode Adjacency_list[MAXSIZE];
/*
Adj_list 是 VertexNode[MAXSIZE] 的别名；
等价写法：
typedef VertexNode (Adj_list)[MAXSIZE];
*/

// 邻接表
struct Adj_Graph
{
    Adjacency_list adj_list; // VertexNode adjacency_list[MAXSIZE]
    int edge_num;
    int vertex_num;
};

typedef Adj_Graph *Adj_List_Graph;

// 创建邻接矩阵
void create_graph(Matrix_Graph *G)
{
    G->vertex_num = 10;
    G->edge_num = 13;

    // 初始化顶点数组
    for (int i = 0; i < G->vertex_num; i++)
    {
        G->vertex[i] = i;
    }

    // 初始化邻接矩阵
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
    G->arc[0][1] = 3;
    G->arc[0][2] = 4;
    G->arc[1][3] = 5;
    G->arc[1][4] = 6;
    G->arc[2][3] = 8;
    G->arc[2][5] = 7;
    G->arc[3][4] = 3;
    G->arc[4][6] = 9;
    G->arc[4][7] = 4;
    G->arc[5][7] = 6;
    G->arc[6][9] = 2;
    G->arc[7][8] = 5;
    G->arc[8][9] = 3;
}

// 创建邻接表
void create_adjacency_graph(Matrix_Graph G, Adj_List_Graph *ALG)
{
    (*ALG) = new Adj_Graph;
    (*ALG)->vertex_num = G.vertex_num;
    (*ALG)->edge_num = G.edge_num;

    // 初始化邻接表
    for (int i = 0; i < G.vertex_num; i++)
    {
        (*ALG)->adj_list[i].data = G.vertex[i];
        (*ALG)->adj_list[i].in = 0;
        (*ALG)->adj_list[i].head = NULL;
    }

    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] != 0 && G.arc[i][j] < INT_MAX)
            {
                edgeNode *e = new edgeNode;
                e->edge_vex = j;
                e->weight = G.arc[i][j];
                // 头插法
                e->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = e;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
}

// 关键路径
void Critial_path(Adj_List_Graph ALG)
{
    int top = -1;
    int stack[MAXSIZE];

    int top2 = -1;
    int stack2[MAXSIZE];

    int ETV[MAXSIZE]; // 最早到达时间
    int LTV[MAXSIZE]; // 最晚到达时间

    // 初始化ETV
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        ETV[i] = 0;
    }
    // 入度等于0的顶点入栈
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        if (ALG->adj_list[i].in == 0)
        {
            top++;
            stack[top] = i;
        }
    }

    while (top != -1)
    {
        // 栈顶出栈
        int cur = stack[top];
        top--; // 简化:int cur = stack[top--];
        cout << "V" << ALG->adj_list[cur].data << " ";
        // 压入stack2
        top2++;
        stack2[top2] = cur; // 简化:stack[++top2] = cur;

        edgeNode *e = ALG->adj_list[cur].head;

        while (e != NULL)
        {
            int k = e->edge_vex;
            ALG->adj_list[k].in--;

            if (ALG->adj_list[k].in == 0)
            {
                top++;
                stack[top] = k;
            }

            if (ETV[cur] + e->weight > ETV[k])
            {
                ETV[k] = ETV[cur] + e->weight;
            }

            e = e->next;
        }
    }
    cout << endl;
    // 输出ETV
    cout << "ETV: ";
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        cout << ETV[i] << " ";
    }
    cout << endl;
    // 初始化LTV
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        LTV[i] = ETV[ALG->vertex_num - 1]; // 初始化为最大值
    }
    // 更新LTV
    while (top2 != -1)
    {
        int cur = stack2[top2]; // 栈顶元素出栈
        top2--;

        edgeNode *e = ALG->adj_list[cur].head;

        while (e != NULL)
        {
            int k = e->edge_vex;

            if (LTV[k] - e->weight < LTV[cur])
            {
                LTV[cur] = LTV[k] - e->weight;
            }
            e = e->next;
        }
    }
    // 输出LTV
    cout << "LTV: ";
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        cout << LTV[i] << " ";
    }
    cout << endl;
    // 输出关键路径
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        if (ETV[i] == LTV[i])
        {
            cout << "V" << i << " ";
        }
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    Matrix_Graph G;
    create_graph(&G);

    Adj_List_Graph ALG;
    create_adjacency_graph(G, &ALG);

    Critial_path(ALG);

    return 0;
}
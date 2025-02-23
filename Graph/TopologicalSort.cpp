/*
拓扑排序：
1.寻找有向图中入度为0的顶点，入栈；
2.栈顶元素出栈，寻找有没有新的入度为0的顶点，若有，入栈；若无，栈顶元素出栈；
3.重复步骤1；
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
struct edgeNode{
    int edge_vex;
    edgeNode *next;
    int weight; // 权重(关键路径only)
};

// 邻接表每个表的表头
struct VertexNode{
    int in; // 入度
    VertexType data;
    edgeNode *head;
};

// 表示所有顶点构成的一维数组
typedef VertexNode Adjacency_list[MAXSIZE];  
/*
Adj_list 是 VertexNode[MAXSIZE] 的别名；
等价写法：
typedef VertexNode (Adj_list)[MAXSIZE];
*/ 

// 邻接表
struct Adj_Graph{
    Adjacency_list adj_list; // VertexNode adjacency_list[MAXSIZE]
    int edge_num;
    int vertex_num;
};

typedef Adj_Graph* Adj_List_Graph;

// 栈
int top = -1;
int stack[MAXSIZE];

// 入栈
void push(int e)
{
    if (top >= MAXSIZE)
    {
        cout << "栈满" << endl;
        return;
    }
    top++;
    stack[top] = e;
}

// 出栈
int pop()
{
    if (top == -1)
    {
        cout << "空栈" << endl;
        return -1;
    }
    int cur = top;
    top--;
    return stack[cur];
}

// 判断栈是否为空
bool isEmpty()
{
    if (top == -1)
    {
        return 1;
    }
    else{
        return 0;
    }
}

// 创建图
void create_graph(Matrix_Graph *G)
{
    G->vertex_num = 14;
    G->edge_num = 20;
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
            G->arc[i][j] = 0;
        }
    }
    // 创建邻接矩阵
    G->arc[0][4] = 1;
    G->arc[0][5] = 1;
    G->arc[0][11] = 1;
    G->arc[1][2] = 1;
    G->arc[1][4] = 1;
    G->arc[1][8] = 1;
    G->arc[2][5] = 1;
    G->arc[2][6] = 1;
    G->arc[2][9] = 1;
    G->arc[3][2] = 1;
    G->arc[3][13] = 1;
    G->arc[4][7] = 1;
    G->arc[5][8] = 1;
    G->arc[5][12] = 1;
    G->arc[6][5] = 1;
    G->arc[8][7] = 1;
    G->arc[9][10] = 1;
    G->arc[9][11] = 1;
    G->arc[10][13] = 1;
    G->arc[12][9] = 1;
}

// 由邻接矩阵创建邻接表
void create_adj_graph(Matrix_Graph G, Adj_List_Graph *ALG) // ALG:邻接表指针的指针
{
    edgeNode *e;

    (*ALG) = new Adj_Graph;
    (*ALG)->edge_num = G.edge_num;
    (*ALG)->vertex_num = G.vertex_num;

    // 初始化邻接表
    for (int i = 0; i < G.vertex_num; i++)
    {
        (*ALG)->adj_list[i].in = 0;
        (*ALG)->adj_list[i].data = G.vertex[i];
        (*ALG)->adj_list[i].head = NULL;
    }

    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] == 1)
            {
                e = new edgeNode;
                e->edge_vex = j;
                // 头插法
                e->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = e;
                (*ALG)->adj_list[j].in++;   // 注意是给第j个顶点的入度+1
            }
        }
    }
}

// 拓扑排序
void topological_sort(Adj_List_Graph ALG)
{
    // Adj_Graph* ALG, 即指向邻接表的指针

    // 查找入度为0的顶点入栈
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        if (ALG->adj_list[i].in == 0)
        {
            push(i); // 顶点的下标入栈
        }
    }

    // 
    while (!isEmpty())
    {
        int cur = pop();
        cout << "V" << ALG->adj_list[cur].data << " ";

        edgeNode *e = ALG->adj_list[cur].head;
        while (e != NULL)
        {            
            int k = e->edge_vex;
            ALG->adj_list[k].in--;

            if (ALG->adj_list[k].in == 0)
            {
                push(k);
            }

            e = e->next;
        }
    }
}

int main(int argc, char *argv[])
{
    Matrix_Graph G;
    create_graph(&G);

    Adj_List_Graph ALG;
    create_adj_graph(G, &ALG);

    topological_sort(ALG);
    cout << endl;

    return 0;
}
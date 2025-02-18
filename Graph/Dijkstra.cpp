/*
最短路径 Dijkstra 算法：输出源点到图中其他所有顶点的最短路径
1.首先将图的顶点分为两部分：已找到最短路径的顶点集合S，未找到最短路径的顶点集合T，初始S集合内只有源点；
2.寻找从S出发，到达其他顶点的最短路径（只关注直达路径），若没有直达路径，则距离记为无穷大；
3.对当前找到的路径进行排序，将路径最短的结点加入到集合S（即已经找到到达该结点的最短路径）；
4.重复步骤2；直到所有顶点加入S；

Floyd 算法：通过添加中转点，寻找任意两点之间的最短路径，可以输出任意源点出发的最小路径；
思路类似于递归，首先找到起点和终点之间的最短路径，然后添加中转点，比较是否路径更短；若更短，更新最短路径的值；

举例：查找v0到v3的最短路径，首先找到中转点v1,然后再查找v1到v3的最短路径，找到中转点v2,
再查找v2到v3的最短路径，找到v4,再查找v4到v3的最短路径，无更短的中转点；于是找到了v0到v3的最短路径；

**困惑** 
为什么三层for循环中间结点在最外层？？？
*/
#include <iostream>
#include <climits> // 使用 INT_MAX 表示无穷

using namespace std;

typedef int VertexType;
typedef int EdgeType;

#define MAXSIZE 10
#define MAXEDGE 20

struct Matrix_Graph
{
    VertexType vertex[MAXSIZE];     // 保存顶点
    EdgeType arc[MAXSIZE][MAXSIZE]; // 保存边
    int vertex_num;
    int edge_num;
};

// 创建图
void create_graph(Matrix_Graph *G)
{
    G->vertex_num = 9;
    G->edge_num = 16;

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
            else{
                G->arc[i][j] = INT_MAX;
            }
        }
    }
    G->arc[0][1] = 1;
    G->arc[0][2] = 5;
    G->arc[1][2] = 3;
    G->arc[1][3] = 7;
    G->arc[1][4] = 5;
    G->arc[2][4] = 1;
    G->arc[2][5] = 7;
    G->arc[3][4] = 2;
    G->arc[3][6] = 3;
    G->arc[4][5] = 3;
    G->arc[4][6] = 6;
    G->arc[4][7] = 9;
    G->arc[5][7] = 5;
    G->arc[6][7] = 2;
    G->arc[6][8] = 7;
    G->arc[7][8] = 4;
    for (int i = 0; i < G->vertex_num; i++) // 邻接矩阵下三角
    {
        for (int j = i+1; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }

    // 打印邻接矩阵
    for (int i = 0; i < G->vertex_num; i++){
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (G->arc[i][j] < INT_MAX)
            {
                cout << G->arc[i][j] << " ";
                if (j == 8) cout << endl;
            }
            else{
                cout << "#" << " ";
                if (j == 8) cout << endl;
            }
        }
    }

};

// 选择下一个加入已找到最短路径集合S的顶点
int choose(int *distance, int *found, int vertex_num)
{
    int min_weight = INT_MAX;
    int min_posi = -1;

    for (int i = 0; i < vertex_num; i++)
    {
        // 如果顶点未被访问，且权重最小
        if (found[i] == 0 && distance[i] < min_weight)
        {
            min_weight = distance[i];
            min_posi = i;
        }
    }
    return min_posi;
}

// Dijkstra：寻找源点begin到达其余各个顶点的最短路径
void Dijkstra(Matrix_Graph G, int begin)
{
    int found[G.vertex_num];   // 记录顶点是否被访问：1 0
    int path[G.vertex_num]; // 记录离顶点index最近的顶点path[index]
    int distance[G.vertex_num]; // 记录v0到其他顶点的路径长度

    // 初始化数组
    for (int i = 0; i < G.vertex_num; i++)
    {
        found[i] = 0;   // 所有顶点未访问
        path[i] = -1;
        distance[i] = G.arc[begin][i];
    }

    // 处理入口顶点begin 
    found[begin] = 1;
    distance[begin] = 0;

    // 寻找源点begin到各个顶点的最短路径
    for (int i = 1; i < G.vertex_num; i++)
    {
        int next = choose(distance, found, G.vertex_num); // v1
        found[next] = 1; // 标记为已访问
        for (int j = 0; j < G.vertex_num; j++)
        {
            if (found[j] == 0 && G.arc[next][j] < INT_MAX) // 未访问过且边存在
            {
                if (distance[next] + G.arc[next][j] < distance[j])
                {
                    distance[j] = distance[next] + G.arc[next][j];
                    path[j] = next; // 距离顶点j最近的顶点是path[j] = next
                }
            }
        }
    }

    // 输出源点到其他各个顶点的最短路径和权值
    for (int i = 1; i < G.vertex_num; i++)
    {
        int current = i; // current 是正在输出最短路径的顶点
        cout << "Distance to v" << current << ": " << distance[current] << ", path:";
        cout << "v" << current << "--";

        while (path[current] != -1)
        {
            cout << "v" << path[current] << "--";
            current = path[current];
        }
        cout << "v0" << endl;
    }

}

// Floyd 算法
void Floyd(Matrix_Graph G)
{
    int distance[MAXSIZE][MAXSIZE]; // 记录某两个顶点之间距离
    int path[MAXSIZE][MAXSIZE]; // 记录某两个顶点之间经过了哪个顶点

    // 初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            distance[i][j] = G.arc[i][j];
            path[i][j] = j;
        }
    }
    
    // 更新 distance & path
    for (int i = 0; i < G.vertex_num; i++) // 中间顶点
    {
        for (int j = 0; j < G.vertex_num; j++)  // 起点
        {
            for (int k = 0; k < G.vertex_num; k++)  // 终点
            {
                if (distance[j][k] > distance[j][i] + distance[i][k] && distance[j][i] < INT_MAX && distance[i][k] < INT_MAX)
                {
                    distance[j][k] = distance[j][i] + distance[i][k];
                    path[j][k] = path[j][i]; // 记录中间结点i
                }
            }
        }
    }

    // 输出 distance 
    cout << "distance[][]:" << endl;
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            cout << distance[i][j] << " ";
            if (j == 8) cout << endl;
        }
    }

    // 输出 path
    cout << "path[][]:" << endl;
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            cout << path[i][j] << " ";
            if (j == 8)
                cout << endl;
        }
    }

    // 输出最短路径
    int k;  // 中间结点
    for (int i = 0; i < G.vertex_num; i++)  // 起点
    {
        for (int j = i+1; j < G.vertex_num; j++)    // 终点
        {
            // 输出距离
            cout << "Distance from v" << i << " to v" << j << ": " << distance[i][j];

            // // 输出路径：视频版
            // cout << ", path: v" << i << "--"; // 起点
            // k = path[i][j];
            // while (k != j)
            // {
            //     cout << "v" << k << "--";   // 中间结点
            //     k = path[k][j];
            // }
            // cout << "v" << j << endl;   // 终点

            // 输出路径：deepseek优化
            int current = i;
            cout << ", path: v" << current;
            while (current != j)
            {
                current = path[current][j];
                cout << "--" << "v" << current;
            }
            cout << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    Matrix_Graph G;
    create_graph(&G);

    cout << "Dijkstra: " << endl;
    Dijkstra(G, 0);

    cout << "Floyd: " << endl;
    Floyd(G);

    return 0;
}
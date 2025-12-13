#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <iostream>
#include <climits>
#include <functional>
#include <queue>
#include <stack>
#include <cstring>
#include <string>

const int INF = INT_MAX;

typedef struct EdgeNode {
    int adjVex; // 邻接点的索引
    int weight; // 权重
    EdgeNode* next; 
} EdgeNode;

typedef struct VertexNode {
    int data;
    EdgeNode* firstEdge;
} VertexNode;

typedef struct DirectedGraph {
    VertexNode* vertices;
    int vertexNum;
    int edgeNum;
} DirectedGraph;

// 将邻接矩阵表示的有向图 graph 转换为邻接表存储的有向图 g
void generateDirectedGraph(DirectedGraph& g, int vertexNum, int edgeNum, int** graph) {
    g.vertexNum = vertexNum;
    g.edgeNum = edgeNum;
    g.vertices = new VertexNode[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        g.vertices[i].data = i;
        g.vertices[i].firstEdge = nullptr;
    }
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (graph[i][j] != INF) {   // 如果存在边通向节点 j
                EdgeNode* edge = new EdgeNode;
                edge->adjVex = j;
                edge->weight = graph[i][j];
                edge->next = g.vertices[i].firstEdge;
                g.vertices[i].firstEdge = edge;
            }
        }
    }
}

int* sort(DirectedGraph* g) {
    // 创建入度序列
    int* inDegree = new int[g->vertexNum];
    // 初始化入度序列
    for (int i = 0; i < g->vertexNum; i++) {
        inDegree[i] = 0;
        EdgeNode* edge = g->vertices[i].firstEdge;
        while (edge != nullptr) {
            inDegree[edge->adjVex]++;
            edge = edge->next;
        }
    }
    // 拓扑排序
    // 将所有入度为 0 的顶点入队
    std::queue<int> q;
    for (int i = 0; i < g->vertexNum; i++) {
        if (inDegree[i] == 0) q.push(i);
    }
    // 然后开始遍历
    int index = 0;
    int* tpOrder = new int[g->vertexNum];

    while (!q.empty()) {
        // 先取出对手元素
        int v = q.front();
        q.pop();
        // 然后遍历该顶点的所有邻接点
        tpOrder[index] = v;
        index++;

        EdgeNode* edge = g->vertices[v].firstEdge;
        while (edge != nullptr) {
            // 如果发现有人入度变成 0 了，就入队
            inDegree[edge->adjVex]--;
            if (inDegree[edge->adjVex] == 0) {
                q.push(edge->adjVex);
            }
            edge = edge->next;
        }
        
    }
    // 最后析构入度序列
    delete[] inDegree;
    return tpOrder;
}

// 求有向无环图的最长路径
std::vector<int>* longestPath(DirectedGraph* g) {
    // 先拓扑排序
    int* tpOrder = sort(g);
    // 初始化数组
    int* dist = new int[g->vertexNum];  // dist[i]表示以i为终点的最长路径长度
    int* prec = new int[g->vertexNum];  // prec[i]表示到达i的最长路径的前驱节点
    for (int i = 0; i < g->vertexNum; i++) {
        dist[i] = 0; // 所有节点的最长路径长度初始化为0
        prec[i] = -1; // 初始化前驱节点为-1
    }

    // 对于拓扑排序后的每个节点，我们只需要按照顺序更新每个人的邻接点的信息就可以，因为排在前面的人可能会影响排在后面的人的最长路径和前驱节点，但是排在后面的人不可能影响前面的人的最长路径和相关节点，因此只需要按照拓扑排序后的顺序一次处理就可以得到正确的最长路径
    for (int i = 0; i < g->vertexNum; i++) {
        int u = tpOrder[i];

        EdgeNode* edge = g->vertices[u].firstEdge;
        while (edge != nullptr) {
            int v = edge->adjVex;
            int weight = edge->weight;
            if (dist[u] + weight > dist[v]) {
                dist[v] = dist[u] + weight;
                prec[v] = u;
            }
            edge = edge->next;
        }
    }
    // 此时已经获取了最长路径的所有信息，只需找到终点然后一步一步向前回溯即可
    int maxDist = 0;    // 最长路径长度
    int end = -1;   // 最长路径终点
    // 获取最长路径的长度和终点
    for (int i = 0; i < g->vertexNum; i++) {
        if (dist[i] > maxDist) {
            maxDist = dist[i];
            end = i;
        }
    }

    // 回溯
    std::stack<int> path;
    int current = end;
    while (current != -1) {
        path.push(current);
        current = prec[current];
    }
    
    std::vector<int>* longestPath = new std::vector<int>();
    // 把路径输出到longestPath中
    while (!path.empty()) {
        longestPath->push_back(path.top());
        path.pop();
    }

    // 析构一下
    delete[] tpOrder;
    delete[] dist;
    delete[] prec;

    // 输出结果
    return longestPath;
}

// 将有向图表示的四则运算表达式转换为逆波兰表达式
// 需要对对应的有向图进行后序遍历就可以得到逆波兰表达式
std::string toRPN(DirectedGraph* g) {
    std::string rpn = "";
    
    // 进行后序遍历
    // 输入当前节点 index, 返回这整个子树带来的表达式串
    std::function<std::string(int cur)> dfs = [&](int cur) -> std::string {
        std::string rpn = "";   // 首先创建一个空串
        // 先加上左子树的
        if (g->vertices[cur].firstEdge != nullptr) {
            rpn = rpn + dfs(g->vertices[cur].firstEdge->adjVex);
            // 再加上右子树的
            if (g->vertices[cur].firstEdge->next != nullptr) {
                rpn = rpn + dfs(g->vertices[cur].firstEdge->next->adjVex);
            }
        }
        // 最后加上自己的字符
        rpn = rpn + std::string(1, (char)g->vertices[cur].data);

        return rpn;
    };

    int* sortResult = sort(g);
    int root = sortResult[0];
    delete[] sortResult;  // 释放内存
    rpn = dfs(root);
    return rpn;
}

#endif // DIRECTEDGRAPH_H
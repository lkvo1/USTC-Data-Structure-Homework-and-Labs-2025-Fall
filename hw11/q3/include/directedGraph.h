#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <iostream>
#include <climits>
#include <functional>
#include <queue>

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

// 使用 DFS 寻找 v 到 u 是否存在路径
bool pathExists_dfs(DirectedGraph* g, int v, int u) {
    // 创建并初始化访问序列
    bool* visited = new bool[g->vertexNum];
    for (int i = 0; i < g->vertexNum; i++) {
        visited[i] = false;
    }
    // 使用lambda函数
    std::function<bool(int)> dfs = [&](int cur) {
        // 找到了直接返回
        if (cur == u) {
            return true;
        }
        // 标记当前节点为已访问
        visited[cur] = true;

        EdgeNode* edge = g->vertices[cur].firstEdge;
        // 遍历当前节点所有边指向的节点
        while (edge != nullptr) {
            if (!visited[edge->adjVex]) {
                return dfs(edge->adjVex);   // 如果当前边指向的节点还没有访问过，则进去搜索一下
            }
            edge = edge->next;  // 搜索完当前边之后，切换到下一个边
        }
        return false;
    };

    // 析构释放内存
    bool res = dfs(v);
    delete[] visited;
    return res;
}

bool pathExists_bfs(DirectedGraph* g, int v, int u) {
    bool* visited = new bool[g->vertexNum];
    for (int i = 0; i < g->vertexNum; i++) {
        visited[i] = false;
    }

    std::queue<int> q;
    q.push(v);
    visited[v] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        // 如果找到了，那么直接返回
        if (cur == u) {
            delete[] visited;   // 析构释放内存
            return true;
        }
        // 否则遍历所有的边
        EdgeNode* edge = g->vertices[cur].firstEdge;
        while (edge != nullptr) {
            if (!visited[edge->adjVex]) {   // 如果还没有访问的话加入访问序列
                q.push(edge->adjVex);
                visited[edge->adjVex] = true;
            }
            edge = edge->next;
        }
    }
    
    // 析构释放内存
    delete[] visited;
    return false;
}

bool hasSimplePathOfLengthK(DirectedGraph* g, int v, int u, int k) {
    // 初始化访问序列
    bool* visited = new bool[g->vertexNum];
    for (int i = 0; i < g->vertexNum; i++) {
        visited[i] = false;
    }
    // 定义深度优先搜索函数
    std::function<bool(int, int)> dfs = [&](int cur, int len) {
        // 设定边界条件的返回
        if (len > k) return false;
        if (len == k && cur == u) return true;

        visited[cur] = true;
        EdgeNode* edge = g->vertices[cur].firstEdge;
        // 遍历当前节点所有邻居节点是否能到达目的地
        while (edge != nullptr) {
            if (!visited[edge->adjVex]) {
                if (dfs(edge->adjVex, len + 1)) {
                    visited[cur] = false;
                    return true;
                }
            }
            edge = edge->next;
        }
        visited[cur]  = false;
        return false;
    };

    // 获取判断结果并析构释放内存
    bool res = dfs(v, 0);
    delete[] visited;
    return res;
}

#endif // DIRECTEDGRAPH_H
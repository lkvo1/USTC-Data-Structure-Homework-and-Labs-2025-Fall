#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <iostream>
#include <climits>
#include <functional>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>

const int INF = INT_MAX;

// 边节点
typedef struct EdgeNode {
    int adjVex; // 邻接点的索引
    int weight; // 权重
    int roadType; // 道路类型： 1 人行道 2 车行 3 混合道路
    int sceneryLevel; // 景点等级 1 - 10
    std::string direction; // 方向
    EdgeNode* next; 
} EdgeNode;

// 点节点
typedef struct VertexNode {
    int data;
    EdgeNode* firstEdge;
} VertexNode;

typedef struct DirectedGraph {
    VertexNode* vertices;
    int vertexNum;
    int edgeNum;
} DirectedGraph;

// 析构图
void freeGraph(DirectedGraph& g) {
    if (g.vertices != nullptr) {
        for (int i = 0; i < g.vertexNum; i++) {
            EdgeNode* p = g.vertices[i].firstEdge;
            while (p != nullptr) {
                EdgeNode* temp = p;
                p = p->next;
                delete temp;
            }
        }
        delete[] g.vertices;
        g.vertices = nullptr;
    }
}

// 将邻接矩阵表示的有向图 graph 转换为邻接表存储的有向图 g
void generateDirectedGraph(DirectedGraph& g, int vertexNum, int** graph, int** typeMat = nullptr, int** sceneMat = nullptr, std::string** dirMat = nullptr) {
    g.vertexNum = vertexNum;
    g.edgeNum = 0;
    g.vertices = new VertexNode[vertexNum];
    // 初始化顶点
    for (int i = 0; i < vertexNum; i++) {
        g.vertices[i].data = i;
        g.vertices[i].firstEdge = nullptr;
    }
    // 构造各个路径
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (graph[i][j] != INF) {   // 如果存在边通向节点 j
                EdgeNode* edge = new EdgeNode;
                edge->adjVex = j;
                edge->weight = graph[i][j];
                
                // 设置扩展值，如果有矩阵的话，如果没有默认赋值为 3 或 5
                edge->roadType = (typeMat) ? typeMat[i][j] : 3; 
                edge->sceneryLevel = (sceneMat) ? sceneMat[i][j] : 5;
                edge->direction = (dirMat) ? dirMat[i][j] : "";

                edge->next = g.vertices[i].firstEdge;
                g.vertices[i].firstEdge = edge;
                g.edgeNum++;
            }
        }
    }
}

// Dijkstra 求最短路径
// filterType 过滤类型，如果选择 0 表示不过滤，选择 1 表示只允许人行，选择 2 表示只允许车行
void dijkstra(DirectedGraph* g, int startV, int* dist, int* path, int filterType = 0) {
    bool* visited = new bool[g->vertexNum];
    // 初始化每个顶点的距离和路径
    for (int i = 0; i < g->vertexNum; i++) {
        dist[i] = INF;
        path[i] = -1;
        visited[i] = false;
    }
    dist[startV] = 0;
    // 主循环
    for (int i = 0; i < g->vertexNum; i++) {
        // 每次找到未访问的顶点中距离最小的顶点，如果找不到的话直接跳出
        int u = -1;
        int minWeight = INF;
        for (int j = 0; j < g->vertexNum; j++) {
            if (!visited[j] && dist[j] < minWeight) {
                u = j;
                minWeight = dist[j];
            }
        }
        // 如果找不到未访问的顶点，跳出循环
        if (u == -1) break;
        visited[u] = true;

        // 对于节点 u , 考虑其所有邻接点 v
        EdgeNode* e = g->vertices[u].firstEdge;
        while (e != nullptr) {
            int v = e->adjVex;
            
            // 道路过滤，如果发现道路类型不对就直接跳出
            bool typeOK = true;
            if (filterType == 1 && e->roadType == 2) typeOK = false;
            if (filterType == 2 && e->roadType == 1) typeOK = false;
            
            // 如果道路类型正确，并且没有访问过，并且 u 不是无穷大距离，并且
            if (typeOK && !visited[v] && dist[u] != INF && dist[u] + e->weight < dist[v]) {
                dist[v] = dist[u] + e->weight;
                path[v] = u;
            }
            e = e->next;
        }
    }
    delete[] visited;
}

// 辅助函数 DFS 找所有路径
void dfsAllPaths(DirectedGraph* g, int u, int d, bool* visited, std::vector<int>& path, std::vector<std::vector<int>>& allPaths) {
    visited[u] = true;
    path.push_back(u);
    if (u == d) {
        allPaths.push_back(path);
    } else {
        EdgeNode* p = g->vertices[u].firstEdge;
        while (p) {
            if (!visited[p->adjVex]) {
                dfsAllPaths(g, p->adjVex, d, visited, path, allPaths);
            }
            p = p->next;
        }
    }
    path.pop_back();
    visited[u] = false;
}

// 获取两点间所有路径
std::vector<std::vector<int>> getAllPaths(DirectedGraph* g, int start, int end) {
    std::vector<std::vector<int>> allPaths;
    std::vector<int> path;
    bool* visited = new bool[g->vertexNum];

    for(int i = 0; i < g->vertexNum; i++) visited[i] = false;
    
    dfsAllPaths(g, start, end, visited, path, allPaths);
    
    delete[] visited;
    return allPaths;
}

#endif // DIRECTEDGRAPH_H

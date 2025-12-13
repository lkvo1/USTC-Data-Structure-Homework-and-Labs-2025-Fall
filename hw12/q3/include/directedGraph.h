#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <iostream>
#include <climits>
#include <functional>
#include <queue>
#include <stack>

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

void sort(DirectedGraph* g) {
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
    std::cout << "Topological Order: ";
    for (int i = 0; i < g->vertexNum; i++) {
        std::cout << tpOrder[i] << " ";
    }
    std::cout << std::endl;
}

#endif // DIRECTEDGRAPH_H
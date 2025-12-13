#include "directedGraph.h"
#include <iostream>

int main() {
    const int N = 4;
    int** graph = new int*[N];
    for (int i = 0; i < N; ++i) {
        graph[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            graph[i][j] = INF;
        }
    }
    // 构造有向图0->1, 1->2, 3->2, 0->3
    graph[0][1] = 1;
    graph[1][2] = 1;
    graph[3][2] = 1;
    graph[0][3] = 5;

    DirectedGraph g;
    generateDirectedGraph(g, N, 4, graph);

    std::vector<int>* path = longestPath(&g);
    std::cout << "Longest Path: ";
    for (int vex : *path) {
        std::cout << vex << "->";
    }
    std::cout << std::endl;
    return 0;
}
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
    // 构造有向图0->1, 1->2, 2->3, 0->3
    graph[0][1] = 1;
    graph[1][2] = 1;
    graph[2][3] = 1;
    graph[0][3] = 5;

    DirectedGraph g;
    generateDirectedGraph(g, N, 4, graph);

    std::cout << "0->3: " << (hasSimplePathOfLengthK(&g, 0, 3, 1) ? "Yes" : "No") << std::endl;
    std::cout << "1->0: " << (hasSimplePathOfLengthK(&g, 1, 0, 2) ? "Yes" : "No") << std::endl;
    std::cout << "1->3: " << (hasSimplePathOfLengthK(&g, 1, 3, 2) ? "Yes" : "No") << std::endl;
    std::cout << "2->0: " << (hasSimplePathOfLengthK(&g, 2, 0, 1) ? "Yes" : "No") << std::endl;
    std::cout << "2->3: " << (hasSimplePathOfLengthK(&g, 2, 3, 1) ? "Yes" : "No") << std::endl;
    return 0;
}
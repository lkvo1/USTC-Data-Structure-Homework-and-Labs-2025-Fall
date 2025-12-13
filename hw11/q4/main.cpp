#include "directedGraph.h"
#include <iostream>

int main() {
    const int N = 7;
    int graphData[7][7] = {
        {INF, 1, 1, 1, INF, INF, INF},
        {1, INF, INF, INF, 1, INF, INF},
        {1, INF, INF, INF, INF, 1, INF},
        {1, INF, INF, INF, INF, INF, 1},
        {INF, 1, INF, INF, INF, 1, INF},
        {INF, INF, 1, INF, 1, INF, 1},
        {INF, INF, INF, 1, INF, 1, INF}
    };
    int** graph = new int*[7];
    for (int i = 0; i < 7; ++i) {
        graph[i] = new int[7];
        for (int j = 0; j < 7; ++j) {
            graph[i][j] = graphData[i][j];
        }
    }

    DirectedGraph g;
    generateDirectedGraph(g, N, 7, graph);

    std::cout << "0: " << (hasHamiltonPath_dfs(&g, 0) ? "Yes" : "No") << std::endl;
    std::cout << "1: " << (hasHamiltonPath_dfs(&g, 1) ? "Yes" : "No") << std::endl;
    std::cout << "2: " << (hasHamiltonPath_dfs(&g, 2) ? "Yes" : "No") << std::endl;
    std::cout << "3: " << (hasHamiltonPath_dfs(&g, 3) ? "Yes" : "No") << std::endl;
    return 0;
}
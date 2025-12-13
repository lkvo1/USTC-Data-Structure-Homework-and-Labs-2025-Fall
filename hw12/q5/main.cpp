#include <iostream>
#include "include/directedGraph.h"

int main() {
    // a+b*c
    DirectedGraph g;
    g.vertexNum = 5;
    g.edgeNum = 4;
    g.vertices = new VertexNode[5];
    for (int i = 0; i < 5; ++i) {
        g.vertices[i].data = (i == 0 ? '+' : (i == 1 ? 'a' : (i == 2 ? '*' : (i == 3 ? 'b' : 'c'))));
        g.vertices[i].firstEdge = nullptr;
    }

    EdgeNode* e01 = new EdgeNode{1, 0, nullptr};
    EdgeNode* e02 = new EdgeNode{2, 0, nullptr};
    EdgeNode* e23 = new EdgeNode{3, 0, nullptr};
    EdgeNode* e24 = new EdgeNode{4, 0, nullptr};
    e23->next = e24;
    e01->next = e02;
    g.vertices[2].firstEdge = e23;
    g.vertices[0].firstEdge = e01;

    std::string rpn = toRPN(&g);
    std::cout << "RPN: " << rpn << std::endl;
    
    return 0;
}
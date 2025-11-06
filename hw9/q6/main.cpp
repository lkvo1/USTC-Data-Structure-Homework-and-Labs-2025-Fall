#include <iostream>
#include "tree.h"

int main() {
    TreeNode* root = createNode('A');
    TreeNode* nodeB = createNode('B');
    TreeNode* nodeC = createNode('C');
    TreeNode* nodeD = createNode('D');
    TreeNode* nodeE = createNode('E');
    TreeNode* nodeF = createNode('F');
    TreeNode* nodeG = createNode('G');
    
    addChild(root, nodeB);
    addChild(root, nodeC);
    addChild(root, nodeD);
    addChild(nodeB, nodeE);
    addChild(nodeD, nodeF);
    addChild(nodeD, nodeG);
    
    std::cout << "Recessed Table:" << std::endl;
    printRecessedTable(root);

    return 0;
}

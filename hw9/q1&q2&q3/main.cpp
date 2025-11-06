#include "binaryTree.h"

int main() {
    // 创建二叉树
    TreeNode* src = new TreeNode(10);
    src->left = new TreeNode(5);
    src->right = new TreeNode(15);
    src->left->left = new TreeNode(3);
    src->left->right = new TreeNode(7);
    src->right->right = new TreeNode(20);

    // 创建目标树的根节点
    TreeNode* dst = new TreeNode(0);

    dst = nonrecursiveCopyTree(src);
    std::cout << "Original Tree Level Order: " << std::endl;

    levelOrderPrintTree(src);
    std::cout << "Copy Tree Level Order: " << std::endl;

    levelOrderPrintTree(dst);
    std::cout << infixToRPN("a + b * c - d / e") << std::endl;

    dst = infixToArithmeticTree("(a + b) * c - d / e");
    std::cout << "Arithmetic Tree Level Order: " << std::endl;
    levelOrderPrintArithmeticTree(dst);

    std::cout << "Arithmetic Tree to Infix: " << std::endl;
    std::cout << arithmeticTreeToInfix(dst) << std::endl;

    calcDescNum(src);
    std::cout << "Calculate DescNum for Tree src." << std::endl;
    levelOrderPrintTreeWithDescNum(src);
    return 0;
}
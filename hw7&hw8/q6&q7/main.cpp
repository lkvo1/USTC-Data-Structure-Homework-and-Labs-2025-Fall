#include "binaryTree.h"

int main() {
    // 创建二叉树
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->right = new TreeNode(20);

    // 测试删除指定值子树
    std::cout << "Preorder before deletion: ";
    preorderPrintTree(root);
    std::cout << "\nLevel before deletion: ";
    levelOrderPrintTree(root);

    deleteChildTreesWithSpecifiedValue(root, 5);
    std::cout << "\nPreorder after deletion: ";
    preorderPrintTree(root); 
    std::cout << "\nLevel order after deletion: ";
    levelOrderPrintTree(root);
}
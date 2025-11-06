#include "inorderThreadedBinaryTree.h"

int main() {
    // 创建二叉树
    TreeNode* src = new TreeNode(10);
    src->left = new TreeNode(5);
    src->right = new TreeNode(15);
    src->left->left = new TreeNode(3);
    src->left->right = new TreeNode(7);
    src->right->left = new TreeNode(12);
    src->left->right->left = new TreeNode(20); // 给 7 加上左子树， 测试 p 插到 x 的右子树情况

    TreeNode* childTree = new TreeNode(4);
    childTree->left = new TreeNode(2);
    childTree->left->right = new TreeNode(6);
    childTree->left->left = new TreeNode(1);

    // 中序线索化
    inorderThreadAuto(src);
    inorderThreadAuto(childTree);
    // 使用线索中序遍历并打印
    std::cout << "Original tree: ";
    printTreeUsingThread(src);
    std::cout << std::endl;
    std::cout << "Original child tree: ";
    printTreeUsingThread(childTree);
    std::cout << std::endl;

    // 将子树插入到src的左子节点位置
    insertChildTree(src->left->right, childTree);

    // 打印插入后的树
    std::cout << "Tree src after child tree being inserted: ";
    printTreeUsingThread(src);
    std::cout << std::endl;

    return 0;
}
#include "binaryTree.h"

int main() {
    int preorder[] = {1, 2, 4, 5, 3, 6};
    int inorder[] = {4, 2, 5, 1, 6, 3};
    int size = sizeof(preorder) / sizeof(preorder[0]);
    TreeNode* root = getTreeFromInorderAndPreorderArray(inorder, preorder, size);
    levelOrderPrintTree(root);
    return 0;
}
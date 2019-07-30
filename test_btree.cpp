#include "playground/btree.hpp"

using namespace btree;

int main() {
    TreeNode *root = generateRandomTree();
    printTreeV(root);
}

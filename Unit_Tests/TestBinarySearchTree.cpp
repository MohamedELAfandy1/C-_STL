#include <iostream>
#include "../BinarySearchTree.cpp"
using namespace std;

void testInsertAndFind() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    bool ok = (bst.find(10) != NULL && bst.find(5) != NULL && bst.find(15) != NULL);

    if (ok) cout << "[PASS] testInsertAndFind\n";
    else    cout << "[FAIL] testInsertAndFind\n";
}

void testDeleteLeafNode() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.deleteNode(5);

    bool ok = (bst.find(5) == NULL && bst.find(10) != NULL && bst.find(15) != NULL);

    if (ok) cout << "[PASS] testDeleteLeafNode\n";
    else    cout << "[FAIL] testDeleteLeafNode\n";
}

void testDeleteNodeWithOneChild() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(3); // child of 5

    bst.deleteNode(5);
    bool ok = (bst.find(5) == NULL && bst.find(3) != NULL);

    if (ok) cout << "[PASS] testDeleteNodeWithOneChild\n";
    else    cout << "[FAIL] testDeleteNodeWithOneChild\n";
}

void testDeleteNodeWithTwoChildren() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(12);
    bst.insert(18);

    bst.deleteNode(10);

    bool ok = (bst.find(10) == NULL && bst.find(5) != NULL && bst.find(15) != NULL);

    if (ok) cout << "[PASS] testDeleteNodeWithTwoChildren\n";
    else    cout << "[FAIL] testDeleteNodeWithTwoChildren\n";
}

void testBalance() {
    BinarySearchTree<int> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    int before = bst.height();
    bst.balance();
    int after = bst.height();

    bool ok = (after < before);

    if (ok) cout << "[PASS] testBalance\n";
    else    cout << "[FAIL] testBalance\n";
}

void testDuplicateWithCounter() {
    BinarySearchTree<int> bst(2); // allow duplication with count
    bst.insert(4);
    bst.insert(4);
    bst.insert(4);

    TreeNode<int>* node = bst.find(4);
    bool ok = (node != NULL && node->count == 3);

    if (ok) cout << "[PASS] testDuplicateWithCounter\n";
    else    cout << "[FAIL] testDuplicateWithCounter\n";
}

void testDisallowDuplicate() {
    BinarySearchTree<int> bst(1); // disallow duplicates
    bst.insert(10);
    bst.insert(10); // should be ignored
    int before = bst.getNumOfNodes();

    bst.insert(20);
    int after = bst.getNumOfNodes();

    bool ok = (before + 1 == after);

    if (ok) cout << "[PASS] testDisallowDuplicate\n";
    else    cout << "[FAIL] testDisallowDuplicate\n";
}

int main() {
    testInsertAndFind();
    testDeleteLeafNode();
    testDeleteNodeWithOneChild();
    testDeleteNodeWithTwoChildren();
    testBalance();
    testDuplicateWithCounter();
    testDisallowDuplicate();

    cout << "All BinarySearchTree tests finished\n";
    return 0;
}

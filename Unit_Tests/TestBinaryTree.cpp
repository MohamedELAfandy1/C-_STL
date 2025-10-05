#include <iostream>
#include <stdexcept>
#include "../BinaryTree.cpp"   
using namespace std;

void testInsertAndPrint() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    cout << "Expected: 10 20 30\nGot:      ";
    tree.print();
    cout << endl;
}

void testFind() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    bool ok = (tree.find(20) != NULL && tree.find(99) == NULL);

    if (ok) cout << "[PASS] testFind\n";
    else    cout << "[FAIL] testFind\n";
}

void testUpdate() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.update(20, 25);

    bool ok = (tree.find(25) != NULL && tree.find(20) == NULL);

    if (ok) cout << "[PASS] testUpdate\n";
    else    cout << "[FAIL] testUpdate\n";
}

void testDelete() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);

    tree.deleteNode(20);

    bool ok = (tree.find(20) == NULL && tree.getNumOfNodes() == 3);

    if (ok) cout << "[PASS] testDelete\n";
    else    cout << "[FAIL] testDelete\n";
}

void testTraversals() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    cout << "PreOrder   (Expected: 10 20 30): ";
    tree.preOrderTraverse();

    cout << "InOrder    (Expected: 20 10 30): ";
    tree.inOrderTraverse();

    cout << "PostOrder  (Expected: 20 30 10): ";
    tree.postOrderTraverse();
}

void testHeight() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);

    bool ok = (tree.height() == 3);

    if (ok) cout << "[PASS] testHeight\n";
    else    cout << "[FAIL] testHeight\n";
}

int main() {
    testInsertAndPrint();
    testFind();
    testUpdate();
    testDelete();
    testTraversals();
    testHeight();

    cout << "All BinaryTree tests finished\n";
    return 0;
}

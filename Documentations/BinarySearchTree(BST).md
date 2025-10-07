# Binary Search Tree (BST) Documentation

## Overview

This project provides a generic **Binary Search Tree (BST)** implementation in C++.  
It includes:

- `Queue<T>`: a dynamic queue used in tree traversal and insertion.
- `BinaryTree<T>`: a general binary tree with basic operations.
- `BinarySearchTree<T>`: inherits from `BinaryTree<T>` with BST-specific operations.
- `TreeNode<T>`: represents nodes in the tree.
- `NodeAndParent<T>`: helper class used in BST node deletion and searching.

---

## Classes

### `Queue<T>`

A generic dynamic queue used for BFS traversal and other operations.

**Key Functions:**

- `enqueue(T value)` → Adds an element at the end.
- `dequeue()` → Removes and returns the front element.
- `isEmpty()` → Checks if queue is empty.

---

### `TreeNode<T>`

Represents a single node in a tree.

**Members:**

- `T data` → Node value.
- `TreeNode<T>* left` → Pointer to left child.
- `TreeNode<T>* right` → Pointer to right child.
- `int count` → Stores count for duplicate nodes (used in BST).

**Functions:**

- `TreeNode(T _data)` → Constructor.
- `updateCount(int val)` → Updates the count by `val`.

---

### `NodeAndParent<T>`

Stores a node and its parent for BST operations.

**Members:**

- `TreeNode<T>* node` → Target node.
- `TreeNode<T>* parent` → Parent node.
- `bool left` → True if node is left child of parent.

**Functions:**

- `print()` → Prints node and parent info.

---

### `BinaryTree<T>`

Generic binary tree implementation.

**Key Functions:**

- `print()` → Prints tree values level-order.
- `getNumOfNodes()` → Returns total nodes.
- `height()` → Returns height of the tree.
- `preOrderTraverse()`, `inOrderTraverse()`, `postOrderTraverse()` → Traversal functions.
- `printTree()` → Prints a visual tree structure.

**Private Helpers:**

- `heightHelper(TreeNode<T>* node)` → Computes height recursively.
- `preOrderTraverseHelper`, `inOrderTraverseHelper`, `postOrderTraverseHelper` → Traversal helpers.
- `printTree(TreeNode<T>* node, string prefix, bool isLeft)` → Recursive tree printing.

---

### `BinarySearchTree<T>`

Extends `BinaryTree<T>` with BST functionality.

**Members:**

- `int dublicationMethod` → 0 = allow duplicates, 1 = no duplicates, 2 = add counter.

**Key Functions:**

- `insert(T _data)` → Inserts node in BST order considering duplicates.
- `find(T _data)` → Finds node by value using BST search.
- `findNodeAndParent(T _data)` → Finds node and its parent.
- `deleteNode(T _data)` → Deletes node considering BST rules and duplicates.
- `balance()` → Balances BST by converting to sorted array and rebuilding.
  
**Private Helpers:**

- `inOrderToArrayHelper(T* arr, TreeNode<T>* node, int& i)` → Fills array in-order.
- `recursiveBalance(int start, int end, T* arr)` → Builds balanced tree recursively.

------------------------------------------------------------------------

## Unit Testing

Unit tests validate the following BST operations:

- Insert nodes in BST order and print the tree.
- Find existing and non-existing values.
- Update a node value.
- Delete a node considering BST rules and duplicates.
- Traversals: Pre-order, In-order, Post-order.
- Tree height calculation.
- Balance the BST and verify structure.

---

## Example Usage

```cpp
BinarySearchTree<int> bst(2); // 2 = use counter for duplicates
bst.insert(10);
bst.insert(20);
bst.insert(30);
bst.insert(20); // Duplicate with counter
bst.printTree();  // Visual tree structure

TreeNode<int>* found = bst.find(20);
if (found) found->data = 25; // Update node value

bst.deleteNode(10);
bst.inOrderTraverse(); // Example traversal: 20 25 30
bst.balance();         // Balance the BST
bst.printTree();       // Print balanced tree
```
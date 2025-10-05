# BinaryTree and Queue Implementation

## Overview

This project implements a **generic Binary Tree** in C++.\
The Binary Tree supports basic operations such as insertion, searching,
updating, deletion, and traversals.\
The Queue is used internally for level-order traversal and node
management in the Binary Tree.

------------------------------------------------------------------------
## BinaryTree

### Node Structure:

Each node is represented by the `TreeNode` class:

``` cpp
template <class T>
class TreeNode {
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
};
```

### Features:

-   **insert(value):** Adds a new node in level order.
-   **find(value):** Searches for a node with the given value.
-   **update(oldValue, newValue):** Updates the value of a node.
-   **deleteNode(value):** Deletes a node by replacing its data with the
    last node's data.
-   **print():** Prints nodes in level-order.
-   **Traversals:**
    -   Pre-order
    -   In-order
    -   Post-order
-   **height():** Returns the height of the tree.
-   **getNumOfNodes():** Returns the total number of nodes.

------------------------------------------------------------------------

## Unit Testing

Unit tests validate the following operations: - Insert and print - Find
existing and non-existing values - Update a node value - Delete a node -
Traversals (Pre-order, In-order, Post-order) - Tree height

------------------------------------------------------------------------

## Example Usage

``` cpp
BinaryTree<int> tree;
tree.insert(10);
tree.insert(20);
tree.insert(30);
tree.print();  // Output: 10 20 30
tree.update(20, 25);
tree.deleteNode(10);
tree.inOrderTraverse(); // Example traversal
```

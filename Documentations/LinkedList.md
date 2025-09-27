# LinkedList<T> Documentation

## Overview

This is a generic **singly linked list** implementation in C++ that supports:

- Node insertion and deletion at various positions with nodes as parameters or data.
- Shallow copy and deep copy mechanisms.
- Reference counting (`refCount`) for safe memory management.
- Iterators for traversal.
- Automatic cleanup via destructor.

The list nodes (`LinkedListNode<T>`) **must be allocated on the heap using `new`**, to ensure safe memory management across copies.

---

## Classes

### `LinkedListNode<T>`

Represents a single node in the list.

**Members:**

- `T data`: the value stored in the node.
- `LinkedListNode<T> *next`: pointer to the next node.

**Constructor:**

```cpp
LinkedListNode(T _data, LinkedListNode<T> *ptr = NULL);
```

- `_data`: the value to store.
- `ptr`: pointer to next node (default `NULL`).

---

### `LinkedListIterator<T>`

A simple iterator for traversing the linked list.

**Members:**

- `LinkedListNode<T> *currentNode`: the node currently pointed to.

**Constructor:**

```cpp
LinkedListIterator(LinkedListNode<T> *_current = NULL);
```

**Methods:**

- `LinkedListIterator<T>& next()`  
  Moves iterator to the next node and returns reference.

---

### `LinkedList<T>`

Main class representing the linked list.

**Members:**

- `LinkedListNode<T> *head`: pointer to first node.
- `LinkedListNode<T> *tail`: pointer to last node.
- `int *length`: reference number of nodes in the list.
- `int *refCount`: reference counter for shallow copies.

---

## Core Methods

### Constructors

- `LinkedList()` → Creates an empty list.
- `LinkedList(const LinkedList<T> &other)` → **Deep Copy Constructor**. Copies all nodes into a new list.

### Destructor

- `~LinkedList()`  
  Deletes all nodes when reference count reaches 0.

---

## Copy Mechanisms

### Deep Copy

- **Copy Constructor:**

  ```cpp
  LinkedList(const LinkedList<T> &other);
  ```

  Creates a new list with its own nodes.

- **Assignment Operator:**

  ```cpp
  LinkedList<T>& operator=(const LinkedList<T> &other);
  ```

  Clears existing nodes, then copies from `other`.

- **Explicit Deep Copy Function:**
  ```cpp
  LinkedList<T> copy();
  ```
  Returns a completely new list with duplicated nodes.

### Shallow Copy

- **Explicit Shallow Copy Function:**
  ```cpp
  LinkedList<T> shallowCopy();
  ```
  Creates a new list object sharing the same nodes. Increases `refCount`.

NOTE: When shallow copy is used, both lists share the same nodes. Deleting nodes from one affects the other.

---

## Node Operations

### Insertion

- `void insertLast(T data)`  
  Appends a new node with `data` at the end.

- `void insertLast(LinkedListNode<T> *newNode)`  
  Appends an existing node allocated on heap.  
  `newNode` must be created with `new`.

- `void insertAfter(T nodeValue, T value, int skip = 0)`  
  Inserts after the `skip`-th occurrence of `nodeValue`.

- `void insertAfter(LinkedListNode<T> *&n, T value)`  
  Inserts after node `n` if it exists in the list.

- `void insertBefore(T nodeValue, T value, int skip = 0)`  
  Inserts before the `skip`-th occurrence of `nodeValue`.

- `void insertBefore(LinkedListNode<T> *node, T value)`  
  Inserts before node `node`.

### Deletion

- `void deletePointer(T nodeValue, int skip = 0)`  
  Deletes the `skip`-th occurrence of `nodeValue`.

- `void deletePointer(LinkedListNode<T> *node)`  
  Deletes a node by address.

---

## Search & Utilities

- `LinkedListNode<T>* find(T nodeValue, int skip = 0)`  
  Finds the `skip`-th occurrence of `nodeValue`.

- `LinkedListNode<T>* findParent(T nodeValue, int skip = 0)`  
  Finds the parent of the target node.

- `LinkedListNode<T>* findParentByAddress(LinkedListNode<T> *node)`  
  Finds the parent node of `node`.

- `LinkedListNode<T>* findByAddress(LinkedListNode<T> *node)`  
  Finds node by address.

- `LinkedListIterator<T> begin()`  
  Returns iterator starting at head.

- `void printList()`  
  Prints all elements in order.

- `T front() const` → Returns head data.
- `T back() const` → Returns tail data.
- `bool isEmpty() const` → Checks if empty.
- `int getLength() const` → Returns number of nodes.

---

## Future Enhancements

### Known Issue

When using **shallow copy**, both the original list and the shallow copy share the same nodes in memory.  
This means:

- Any modification to the **internal nodes** is reflected in both lists (expected behavior).
- However, if the **head** or **tail** node is deleted or modified in the original list,  
  the shallow copy may still point to a **dangling node** (memory that has already been freed).
- This can cause **undefined behavior**, such as crashes during `printList()` or corruption when inserting new elements.

### Proposed Solutions

**Use Smart Pointers (`std::shared_ptr`)**  
 Replace raw pointers (`LinkedListNode<T>*`) with smart pointers.  
 This ensures that nodes are only deleted when no list references them.

---

## Example Usage

```cpp
LinkedList<int> l1;
l1.insertLast(10);
l1.insertLast(20);

LinkedList<int> l2 = l1.copy();   // Deep copy
LinkedList<int> l3 = l1.shallowCopy(); // Shallow copy

l1.printList();  // 10 20
l2.printList();  // 10 20
l3.printList();  // 10 20
```

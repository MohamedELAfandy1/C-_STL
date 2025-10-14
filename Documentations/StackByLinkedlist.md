# Stack (Implemented by LinkedList)

## Overview

This project implements a **generic stack** data structure in C++ using a **linked list**.  
The stack supports fundamental operations like pushing, popping, peeking, checking if empty, and printing elements.

It is implemented as a **template class**, allowing it to work with any data type (e.g., `int`, `float`, `string`, etc.).

---

## Class Definition

### **Template Declaration**

```cpp
template<class T>
class Stack
```

### **Private Members**

| Member                | Type                  | Description                                |
| --------------------- | --------------------- | ------------------------------------------ |
| `LinkedList<T>* list` | Pointer to LinkedList | Stores stack elements                      |
| `int length`          | Integer               | Tracks the number of elements in the stack |

---

## Public Methods

### **Constructor**

```cpp
Stack();
```

Initializes the stack with a new empty linked list and sets `length = 0`.

---

### **void push(T value)**

Adds a new element to the top of the stack.

- **Parameters:** `value` of type `T`.

---

### **T pop()**

Removes and returns the top element of the stack.  
Throws a `runtime_error` if the stack is empty.

---

### **T Peek()**

Returns the element at the top of the stack **without removing it**.  
Throws a `runtime_error` if the stack is empty.

---

### **bool isEmpty()**

Checks whether the stack contains any elements.

---

### **void print()**

Prints all elements of the stack from **top to bottom**.

---

### **Destructor**

```cpp
~Stack();
```

Deallocates memory used by the linked list to prevent memory leaks.

---

## Unit Testing

Example test file: `StackLinkedListTest.cpp`

Each function checks a specific stack operation and prints `[PASS]` or `[FAIL]`.

### **Sample Test Cases**

```cpp
void testPushPop();
void testPeek();
void testEmptyStackOps();
```

---

## Example Usage

```cpp
#include "StackByLinkedList.cpp"
#include <iostream>
using namespace std;

int main() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.print(); // Output: 30 20 10
    cout << "Top Element: " << stack.Peek() << endl;
    cout << "Popped: " << stack.pop() << endl;
    stack.print();

    return 0;
}
```

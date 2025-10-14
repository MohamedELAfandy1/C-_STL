# Heap Implementation

## Overview

This project implements a **generic Heap** in C++ (both Min-Heap and Max-Heap).  
The Heap supports essential operations such as insertion, deletion (pop), top element retrieval, resizing, clearing, and visualization through console output.

------------------------------------------------------------------------

## Heap

### Internal Structure:

Each heap is represented by the `Heap` template class:

```cpp
template <class T>
class Heap {
public:
    T* arr;
    int initialSize;
    int size;
    bool minHeap;
};
```

### Features:

- **insert(value):**  
  Adds a new element to the heap while maintaining heap properties.

- **pop():**  
  Removes and returns the root element (minimum or maximum depending on heap type).

- **peek():**  
  Returns the top (root) element without removing it.

- **resize():**  
  Doubles the array size dynamically when the heap is full.

- **clear():**  
  Empties the heap without deallocating memory.

- **getSize():**  
  Returns the current number of elements in the heap.

- **isEmpty():**  
  Checks whether the heap is empty.

- **printArray():**  
  Displays all elements in array order.

- **draw():**  
  Prints a tree-like visual representation of the heap.

------------------------------------------------------------------------

## Unit Testing

Unit tests validate the following operations:

- Insert multiple elements and check heap order
- Pop elements and verify heap property after removal
- Peek to check the top element without modifying the heap
- Clear the heap and ensure it's empty
- Validate resizing behavior
- Test both Min-Heap and Max-Heap configurations

------------------------------------------------------------------------

## Example Usage

```cpp
#include <iostream>
#include "heap.cpp"
using namespace std;

int main() {
    Heap<int> h1(false); // Max-Heap
    h1.insert(10);
    h1.insert(20);
    h1.insert(5);
    h1.printArray(); // Output: [ 20, 10, 5 ]
    cout << "Top: " << h1.peek() << endl; // Output: 20
    h1.pop();
    h1.printArray(); // After removal
    return 0;
}
```

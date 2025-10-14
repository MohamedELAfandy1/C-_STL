# Priority Queue Implementation

## Overview

This project implements a **generic Priority Queue** in C++ using a heap-based structure.  
The Priority Queue supports both **Min-Priority** and **Max-Priority** configurations.  
It provides efficient insertion, removal, and retrieval of elements based on their priority.

------------------------------------------------------------------------

## PriorityQueue

### Internal Structure:

Each priority queue is represented by the `PriorityQueue` template class:

```cpp
template <class T>
class PriorityQueue {
public:
    KeyValuePair<T>* arr;
    int initialSize;
    int size;
    bool minHeap;
};
```

### Supporting Structure:

Each element in the queue is represented by a key–value pair:

```cpp
template <class T>
class KeyValuePair {
    int priority;
    T value;
};
```

### Features:

- **enqueue(priority, value):**  
  Adds a new element to the queue based on its priority while maintaining heap order.  
  (Smaller priority value = higher priority in Min-Heap)

- **dequeue():**  
  Removes and returns the element with the highest (or lowest) priority depending on configuration.

- **peek():**  
  Returns the top-priority element without removing it.

- **resize():**  
  Dynamically doubles the array size when capacity is reached.

- **clear():**  
  Empties the queue without deallocating memory.

- **getSize():**  
  Returns the number of elements currently in the queue.

- **isEmpty():**  
  Checks whether the queue contains any elements.

- **printArray():**  
  Displays all elements with their priorities in array order.

- **draw():**  
  Prints a tree-like structure showing the heap layout of the priority queue.

------------------------------------------------------------------------

## Unit Testing

Unit tests validate the following operations:

- Enqueue multiple elements and ensure correct heap structure  
- Dequeue elements in correct priority order  
- Peek without modifying the queue  
- Clear the queue and verify it becomes empty  
- Check resizing when capacity exceeds initial limit  
- Verify both **Min-Priority** and **Max-Priority** modes  

------------------------------------------------------------------------

## Example Usage

```cpp
#include <iostream>
#include "priority_queue.cpp"
using namespace std;

int main() {
    PriorityQueue<int> pq(false); // Max-Priority Queue

    pq.enqueue(5, 24);
    pq.enqueue(3, 16);
    pq.enqueue(1, 20);

    pq.printArray();  // Output: [ 24 [5], 16 [3], 20 [1] ] (heap order)
    cout << "Top: " << pq.peek().getValue() << endl; // Output: 24

    auto removed = pq.dequeue();
    cout << "Dequeued: " << removed.getValue() << " [" << removed.getPriority() << "]\n";

    pq.printArray();
    return 0;
}
```

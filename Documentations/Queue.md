# Queue Implementations Documentation

## 1️⃣ Queue using Array

### Overview
- Elements are stored in a dynamic array.
- When the array becomes full, `resize()` doubles the capacity and copies elements to a larger array.
- Two pointers are used:
  - `zeroIndex` → points to the front element.
  - `topIndex` → points to the rear element.

### Core Operations
- `enqueue(value)` → add an element at the end of the queue.
- `dequeue()` → remove and return the first element.
- `peek()` → return the first element without removing it.
- `isEmpty()` → check if the queue is empty.
- `getSize()` → return the number of elements.
- `resize()` → double the capacity and copy elements.
- `print()` → display all elements in the queue.

### Time Complexity
- `enqueue`: **O(1)** average, **O(n)** in case of resize.
- `dequeue`: **O(1)**.
- `peek`: **O(1)**.
- `isEmpty`: **O(1)**.
- `getSize`: **O(1)**.

---

## 2️⃣ Queue using Linked List

### Overveiew
- Elements are stored as linked nodes (each node contains `data` and a pointer `next`).
- The queue maintains:
  - `head` → first element (front).
  - `tail` → last element (rear).
- Adding (`enqueue`) at the end is **O(1)**.
- Removing (`dequeue`) from the front is **O(1)**.

### Core Operations
- `enqueue(value)` → add an element at the end of the queue.
- `dequeue()` → remove and return the first element.
- `peek()` → return the first element without removing it.
- `isEmpty()` → check if the queue is empty.
- `getSize()` → return the number of elements.
- `print()` → display all elements in the queue.

### Time Complexity
- `enqueue`: **O(1)**.
- `dequeue`: **O(1)**.
- `peek`: **O(1)**.
- `isEmpty`: **O(1)**.
- `getSize`: **O(1)**.

---

## 3️⃣ Unit Tests

Unit tests are created to validate both Array Queue and LinkedList Queue implementations.

### Array Queue Tests
- **testEnqueueDequeue** → checks if elements follow FIFO order during enqueue and dequeue.
- **testPeek** → ensures `peek` returns the correct element without removal.
- **testEdgeCases** → validates exception handling when dequeuing from an empty queue.
- **testResize** → verifies that the queue resizes automatically when capacity is exceeded.

### LinkedList Queue Tests
- **testEnqueueDequeue** → checks ordering of enqueue and dequeue.
- **testPeek** → validates that `peek` returns the correct front element.
- **testEdgeCases** → validates exception handling when dequeuing from an empty queue.

Each test prints:
- `[PASS]` → if the test succeeds.
- `[FAIL]` → if the test fails.

---

## Conclusion
- **Array Queue** is suitable for simple applications with a small or predictable data size.
- **LinkedList Queue** is better for applications with highly dynamic or large data sizes.
- Having **unit tests** guarantees correctness and makes the implementation easier to maintain and extend.

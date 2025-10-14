# Stack (Implemented by Array)

## Overview
This project implements a **generic stack** data structure in C++ using a **dynamic array**.  
The stack supports fundamental operations like pushing, popping, peeking, resizing, and printing elements.

It is implemented as a **template class**, allowing it to work with any data type (e.g., `int`, `float`, `string`, etc.).

---

## Class Definition

### **Template Declaration**
```cpp
template<class T>
class Stack
```

### **Private Members**
| Member | Type | Description |
|---------|------|-------------|
| `T* arr` | Dynamic array | Stores stack elements |
| `int capacity` | Integer | Maximum current capacity of the stack |
| `int topIndex` | Integer | Index of the top element (starts at -1) |

---

## Public Methods

### **Constructor**
```cpp
Stack(int initialCapacity = 10);
```
Initializes the stack with a specific capacity (default = 10).  
Allocates dynamic memory for the array and sets `topIndex = -1`.

---

### **void resize()**
Doubles the stack’s capacity when it becomes full.  
Copies old elements into a newly allocated array.

---

### **void push(T value)**
Adds a new element to the top of the stack.  
If the stack is full, it automatically resizes before inserting.

---

### **T pop()**
Removes and returns the top element of the stack.  
Throws a `runtime_error` if the stack is empty.

---

### **T peek()**
Returns the element at the top of the stack **without removing it**.  
Throws a `runtime_error` if the stack is empty.

---

### **bool isEmpty()**
Checks whether the stack contains any elements.

---

### **int getSize()**
Returns the number of elements currently stored in the stack.

---

### **void print()**
Prints all elements of the stack from **top to bottom**.

---

### **Destructor**
```cpp
~Stack();
```
Deallocates dynamic memory used by the stack array to prevent memory leaks.

---

##  Unit Testing

Example test file: `StackTest.cpp`

Each function checks a specific stack operation and prints `[PASS]` or `[FAIL]`.

### **Sample Test Cases**
```cpp
void testPushPop();
void testPeek();
void testResize();
void testEmptyStackOps();
```

**Example Run:**
```
[PASS] testPushPop
[PASS] testPeek
[PASS] testResize
[PASS] testEmptyStackOps
All Stack tests finished
```

---

##  Example Usage
```cpp
#include "Stack.cpp"
#include <iostream>
using namespace std;

int main() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.print(); // Output: 30 20 10
    cout << "Top Element: " << stack.peek() << endl;
    cout << "Popped: " << stack.pop() << endl;
    stack.print();

    return 0;
}
```

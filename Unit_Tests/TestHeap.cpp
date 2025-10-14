#include <iostream>
#include <stdexcept>
#include "../Heap.cpp" 
using namespace std;

void testInsertAndPrint() {
    Heap<int> h(false); // Max Heap
    h.insert(10);
    h.insert(20);
    h.insert(5);

    cout << "Expected (MaxHeap order in array): [ 20, 10, 5 ] or similar heap order\nGot: ";
    h.printArray();
    cout << endl;
}

void testPeek() {
    Heap<int> h(true); // Min Heap
    h.insert(10);
    h.insert(3);
    h.insert(8);

    bool ok = (h.peek() == 3);

    if (ok) cout << "[PASS] testPeek\n";
    else    cout << "[FAIL] testPeek\n";
}

void testPop() {
    Heap<int> h(false); // Max Heap
    h.insert(10);
    h.insert(20);
    h.insert(5);

    int popped = h.pop(); // should remove 20
    bool ok = (popped == 20 && h.peek() <= 10);

    if (ok) cout << "[PASS] testPop\n";
    else    cout << "[FAIL] testPop\n";
}

void testResize() {
    Heap<int> h(false); // Max Heap
    for (int i = 0; i < 20; i++) {
        h.insert(i);
    }

    bool ok = (h.getSize() == 20);
    if (ok) cout << "[PASS] testResize\n";
    else    cout << "[FAIL] testResize\n";
}

void testClear() {
    Heap<int> h(true);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.clear();

    bool ok = (h.isEmpty() && h.getSize() == 0);

    if (ok) cout << "[PASS] testClear\n";
    else    cout << "[FAIL] testClear\n";
}

void testIsEmpty() {
    Heap<int> h(true);
    bool ok1 = h.isEmpty();

    h.insert(10);
    bool ok2 = !h.isEmpty();

    if (ok1 && ok2) cout << "[PASS] testIsEmpty\n";
    else            cout << "[FAIL] testIsEmpty\n";
}

void testGetSize() {
    Heap<int> h(false);
    h.insert(1);
    h.insert(2);
    h.insert(3);

    bool ok = (h.getSize() == 3);

    if (ok) cout << "[PASS] testGetSize\n";
    else    cout << "[FAIL] testGetSize\n";
}

int main() {
    cout << "Running Heap Unit Tests...\n\n";

    testInsertAndPrint();
    testPeek();
    testPop();
    testResize();
    testClear();
    testIsEmpty();
    testGetSize();

    cout << "\nAll Heap tests finished.\n";
    return 0;
}

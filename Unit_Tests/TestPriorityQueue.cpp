#include <iostream>
#include <stdexcept>
#include "../PriorityQueue.cpp"   
using namespace std;

void testEnqueueAndPrint() {
    PriorityQueue<int> q(false); // MaxHeap
    q.enqueue(5, 10);
    q.enqueue(10, 20);
    q.enqueue(3, 5);

    cout << "Expected (max priority on top): 10 or 20\nGot: ";
    q.printArray();
    cout << endl;
}

void testPeek() {
    PriorityQueue<int> q(true); // MinHeap
    q.enqueue(5, 100);
    q.enqueue(2, 50);
    q.enqueue(8, 150);

    bool ok = (q.peek().getPriority() == 2);
    if (ok) cout << "[PASS] testPeek\n";
    else    cout << "[FAIL] testPeek\n";
}

void testDequeue() {
    PriorityQueue<int> q(false); // MaxHeap
    q.enqueue(3, 10);
    q.enqueue(5, 20);
    q.enqueue(1, 5);

    KeyValuePair<int> dq = q.dequeue(); // should remove (5,20)
    bool ok = (dq.getPriority() == 5 && q.getSize() == 2);
    if (ok) cout << "[PASS] testDequeue\n";
    else    cout << "[FAIL] testDequeue\n";
}

void testResize() {
    PriorityQueue<int> q(false);
    for (int i = 0; i < 20; i++)
        q.enqueue(i, i * 10);

    bool ok = (q.getSize() == 20);
    if (ok) cout << "[PASS] testResize\n";
    else    cout << "[FAIL] testResize\n";
}

void testClear() {
    PriorityQueue<int> q(true);
    q.enqueue(1, 10);
    q.enqueue(2, 20);
    q.clear();

    bool ok = (q.isEmpty() && q.getSize() == 0);
    if (ok) cout << "[PASS] testClear\n";
    else    cout << "[FAIL] testClear\n";
}

void testIsEmpty() {
    PriorityQueue<int> q(true);
    bool ok1 = q.isEmpty();

    q.enqueue(2, 100);
    bool ok2 = !q.isEmpty();

    if (ok1 && ok2) cout << "[PASS] testIsEmpty\n";
    else            cout << "[FAIL] testIsEmpty\n";
}

void testGetSize() {
    PriorityQueue<int> q(false);
    q.enqueue(1, 10);
    q.enqueue(2, 20);
    q.enqueue(3, 30);

    bool ok = (q.getSize() == 3);
    if (ok) cout << "[PASS] testGetSize\n";
    else    cout << "[FAIL] testGetSize\n";
}

int main() {
    cout << "Running PriorityQueue Unit Tests...\n\n";

    testEnqueueAndPrint();
    testPeek();
    testDequeue();
    testResize();
    testClear();
    testIsEmpty();
    testGetSize();

    cout << "\nAll PriorityQueue tests finished.\n";
    return 0;
}

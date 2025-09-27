#include <iostream>
#include <stdexcept>
#include "../QueueByArray.cpp"  
using namespace std;

void testEnqueueDequeue() {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    bool ok = (q.dequeue() == 10 && q.dequeue() == 20 && q.dequeue() == 30 && q.isEmpty());

    if (ok) cout << "[PASS] testEnqueueDequeue\n";
    else    cout << "[FAIL] testEnqueueDequeue\n";
}

void testPeek() {
    Queue<int> q;
    q.enqueue(5);
    q.enqueue(15);

    bool ok = (q.peek() == 5 && q.getSize() == 2);

    if (ok) cout << "[PASS] testPeek\n";
    else    cout << "[FAIL] testPeek\n";
}

void testResize() {
    Queue<int> q;
    for (int i = 1; i <= 20; i++) q.enqueue(i);

    bool ok = (q.getSize() == 20 && q.peek() == 1);

    if (ok) cout << "[PASS] testResize\n";
    else    cout << "[FAIL] testResize\n";
}

void testEmptyQueueOps() {
    Queue<int> q;
    bool ok = false;
    try {
        q.dequeue();
    }
    catch (runtime_error& e) {
        ok = true;
    }

    if (ok && q.isEmpty()) cout << "[PASS] testEmptyQueueOps\n";
    else                   cout << "[FAIL] testEmptyQueueOps\n";
}

int main() {
    testEnqueueDequeue();
    testPeek();
    testResize();
    testEmptyQueueOps();

    cout << "All Array Queue tests finished\n";
    return 0;
}

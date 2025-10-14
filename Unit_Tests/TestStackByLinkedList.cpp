#include <iostream>
#include <stdexcept>
#include "../StackByLinkedList.cpp"     
using namespace std;

void testPushPop() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    bool ok = (s.pop() == 30 && s.pop() == 20 && s.pop() == 10 && s.isEmpty());

    if (ok) cout << "[PASS] testPushPop\n";
    else    cout << "[FAIL] testPushPop\n";
}

void testPeek() {
    Stack<int> s;
    s.push(5);
    s.push(15);

    bool ok = (s.Peek() == 15 && !s.isEmpty());

    if (ok) cout << "[PASS] testPeek\n";
    else    cout << "[FAIL] testPeek\n";
}

void testEmptyStackOps() {
    Stack<int> s;
    bool ok = false;
    try {
        s.pop();
    }
    catch (runtime_error& e) {
        ok = true;
    }

    if (ok && s.isEmpty()) cout << "[PASS] testEmptyStackOps\n";
    else                   cout << "[FAIL] testEmptyStackOps\n";
}


int main() {
    testPushPop();
    testPeek();
    testEmptyStackOps();
    
    cout << "All tests finished\n";
    return 0;
}

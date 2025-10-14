#include <iostream>
#include <stdexcept>
#include "../StackByArray.cpp"   
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

    bool ok = (s.peek() == 15 && s.getSize() == 2);

    if (ok) cout << "[PASS] testPeek\n";
    else    cout << "[FAIL] testPeek\n";
}

void testResize() {
    Stack<int> s;
    for (int i = 1; i <= 20; i++) s.push(i);

    bool ok = (s.getSize() == 20 && s.peek() == 20);

    if (ok) cout << "[PASS] testResize\n";
    else    cout << "[FAIL] testResize\n";
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
    testResize();
    testEmptyStackOps();

    cout << "All Stack tests finished\n";
    return 0;
}

#include <iostream>
#include <stdexcept>
#include "../Dictionary.cpp"  
using namespace std;

void testInsertAndFind() {
    Dictionary<string, int> dict;
    dict.set("one", 1);
    dict.set("two", 2);

    bool ok = (dict.get("one") == 1 && dict.get("two") == 2);

    if (ok) cout << "[PASS] testInsertAndFind\n";
    else    cout << "[FAIL] testInsertAndFind\n";
}

void testUpdateValue() {
    Dictionary<string, int> dict;
    dict.set("one", 1);
    dict.set("one", 100);

    bool ok = (dict.get("one") == 100);

    if (ok) cout << "[PASS] testUpdateValue\n";
    else    cout << "[FAIL] testUpdateValue\n";
}

void testRemove() {
    Dictionary<string, int> dict;
    dict.set("one", 1);
    dict.set("two", 2);

    dict.remove("one");

    bool ok = false;
    try {
        dict.get("one");
    }
    catch (runtime_error& e) {
        ok = true;
    }

    if (ok && dict.get("two") == 2) cout << "[PASS] testRemove\n";
    else                             cout << "[FAIL] testRemove\n";
}

void testNotFound() {
    Dictionary<string, int> dict;
    dict.set("one", 1);

    bool ok = false;
    try {
        dict.get("two");
    }
    catch (runtime_error& e) {
        ok = true;
    }

    if (ok) cout << "[PASS] testNotFound\n";
    else    cout << "[FAIL] testNotFound\n";
}

void testResize() {
    Dictionary<int, int> dict(2);
    for (int i = 1; i <= 20; i++) {
        dict.set(i, i * 10);
    }

    bool ok = (dict.get(1) == 10 && dict.get(20) == 200);

    if (ok) cout << "[PASS] testResize\n";
    else    cout << "[FAIL] testResize\n";
}

int main() {
    testInsertAndFind();
    testUpdateValue();
    testRemove();
    testNotFound();
    testResize();

    cout << "All Dictionary tests finished\n";
    return 0;
}

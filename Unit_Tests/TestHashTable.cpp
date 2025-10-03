#include <iostream>
#include "../HashTable.cpp" 
using namespace std;

void testInsertAndFind() {
    HashTable<string, int> ht;
    ht.set("one", 1);
    ht.set("two", 2);

    bool ok = (ht.get("one") == 1 && ht.get("two") == 2);

    if (ok) cout << "[PASS] testInsertAndFind\n";
    else    cout << "[FAIL] testInsertAndFind\n";
}

void testUpdateValue() {
    HashTable<string, int> ht;
    ht.set("one", 1);
    ht.set("one", 100);

    bool ok = (ht.get("one") == 100);

    if (ok) cout << "[PASS] testUpdateValue\n";
    else    cout << "[FAIL] testUpdateValue\n";
}

void testRemove() {
    HashTable<string, int> ht;
    ht.set("one", 1);
    ht.set("two", 2);

    ht.remove("one");

    bool ok = (ht.get("one") == 0) && (ht.get("two") == 2);

    if (ok) cout << "[PASS] testRemove\n";
    else    cout << "[FAIL] testRemove\n";
}

void testNotFound() {
    HashTable<string, int> ht;
    ht.set("one", 1);

    bool ok = (ht.get("two") == 0);

    if (ok) cout << "[PASS] testNotFound\n";
    else    cout << "[FAIL] testNotFound\n";
}

void testResize() {
    HashTable<int, int> ht(2); 
    for (int i = 1; i <= 20; i++) {
        ht.set(i, i * 10);
    }

    bool ok = (ht.get(1) == 10 && ht.get(20) == 200);

    if (ok) cout << "[PASS] testResize\n";
    else    cout << "[FAIL] testResize\n";
}

int main() {
    testInsertAndFind();
    testUpdateValue();
    testRemove();
    testNotFound();
    testResize();

    cout << "All HashTable tests finished\n";
    return 0;
}


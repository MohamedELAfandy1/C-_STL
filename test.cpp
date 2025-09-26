#include <iostream>
#include "LinkedList.cpp"

using namespace std;

void testInsertLast() {
    LinkedList<int> list;
    list.insertLast(10);
    list.insertLast(20);
    list.insertLast(30);

    if (list.front() == 10 && list.back() == 30 && list.getLength() == 3)
        cout << "[PASS] testInsertLast\n";
    else
        cout << "[FAIL] testInsertLast\n";
}

void testInsertBeforeAfter() {
    LinkedList<int> list;
    list.insertLast(1);
    list.insertLast(2);
    list.insertLast(3);

    list.insertAfter(1, 4); // after head
    list.insertBefore(3, 5); // before tail
    list.insertAfter(2, 6); // middle
    list.insertBefore(1, 7); // before head

    int expected[] = { 7,1,4,2,6,5,3 };
    LinkedListIterator<int> itr = list.begin();
    bool ok = true;
    for (int i = 0; i < 7; i++) {
        if (!itr.currentNode || itr.currentNode->data != expected[i]) { ok = false; break; }
        itr.next();
    }

    if (ok && list.getLength() == 7)
        cout << "[PASS] testInsertBeforeAfter\n";
    else
        cout << "[FAIL] testInsertBeforeAfter\n";
}

void testDeletePointer() {
    LinkedList<int> list;
    list.insertLast(1);
    list.insertLast(2);
    list.insertLast(3);
    list.insertLast(2); // duplicate
    list.deletePointer(1); // delete head
    list.deletePointer(3); // delete tail
    list.deletePointer(2); // delete first 2
    list.deletePointer(2); // delete second 2

    if (list.isEmpty())
        cout << "[PASS] testDeletePointer\n";
    else
        cout << "[FAIL] testDeletePointer\n";
}

void testShallowDeepCopy() {
    LinkedList<int> list;
    list.insertLast(5);
    list.insertLast(15);

    LinkedList<int> shallow = list.shallowCopy();
    LinkedList<int> deep = list.copy();
    
    list.deletePointer(5);
    
    if (shallow.getLength() == 1 && deep.getLength() == 2)
        cout << "[PASS] testShallowDeepCopy\n";
    else
        cout << "[FAIL] testShallowDeepCopy\n";
}

void testFindFunctions() {
    LinkedList<int> list;
    list.insertLast(10);
    list.insertLast(20);
    list.insertLast(30);

    auto n2 = list.find(20);
    auto parent = list.findParent(20);
    auto byAddr = list.findByAddress(n2);

    if (n2 && n2->data == 20 && parent && parent->data == 10 && byAddr == n2)
        cout << "[PASS] testFindFunctions\n";
    else
        cout << "[FAIL] testFindFunctions\n";
}

void testEdgeCases() {
    LinkedList<int> list;

    // delete from empty
    list.deletePointer(1);

    // insertBefore/After in empty
    list.insertBefore(1, 100);
    list.insertAfter(1, 100);

    // shallow/deep copy empty
    LinkedList<int> copy1 = list.shallowCopy();
    LinkedList<int> copy2 = list.copy();

    if (copy1.isEmpty() && copy2.isEmpty())
        cout << "[PASS] testEdgeCases\n";
    else
        cout << "[FAIL] testEdgeCases\n";
}

int main() {
   testInsertLast();
   testInsertBeforeAfter();
   testDeletePointer();
   testShallowDeepCopy();
   testFindFunctions();
   testEdgeCases();

   cout << "All tests finished\n";
   return 0;
}

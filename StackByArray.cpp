#include <iostream>
using namespace std;

template<class T>
class Stack {
    T* arr;
    int capacity;
    int topIndex;
    //length = topIndex + 1;

public:
    Stack(int initialCapacity = 10) {
        arr = new T[initialCapacity];
        capacity = initialCapacity;
        topIndex = -1;
    }

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {  
            newArr[i] = arr[i];
        }
        //std:copy(arr, arr + topIndex + 1, newArr);
        
        delete[] arr;
        arr = newArr;
    }

    void push(T value) {
        if (topIndex + 1 == capacity) {
            resize();
        }
        arr[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
		T temp = arr[topIndex];
        arr[topIndex] = T();
        --topIndex;
        return temp;
    }

    T peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return arr[topIndex];
    }

    bool isEmpty() {
        return topIndex == -1;
    }
    int getSize() {
        return topIndex+1;
    }

    void print() {
        for (int i = topIndex; i >= 0; --i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~Stack() {
        delete[] arr;
    }
};

//int main() {
//    Stack<int> stack;
//    stack.push(10);
//    stack.push(20);
//    stack.push(30);
//    stack.print();
//	cout << "Stack Size: " << stack.getSize() << endl;
//    cout << "Top Element: " << stack.peek() << endl;
//    cout << "Popped Element: " << stack.pop() << endl;
//    cout << "Stack Size: " << stack.getSize() << endl;
//    stack.print();
//    return 0;
//}

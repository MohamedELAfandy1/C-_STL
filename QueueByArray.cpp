#include <iostream>
using namespace std;

template<class T>
class Queue {
    T* arr;
    int capacity;
    int topIndex;
	int zeroIndex;
    //length = topIndex + 1;

public:
    Queue(int initialCapacity = 10) {
        arr = new T[initialCapacity];
        capacity = initialCapacity;
        topIndex = -1;
        zeroIndex = 0;
    }

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
		int size = this->getSize();
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[zeroIndex+i];
        }
        //std:copy(arr, arr + topIndex + 1, newArr);

        delete[] arr;
        arr = newArr;

        topIndex = size - 1;
        zeroIndex = 0;

    }

    void enqueue(T value) {
        if (topIndex + 1 == capacity) {
            resize();
        }
        arr[++topIndex] = value;
    }

    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        T temp = arr[zeroIndex];
        arr[zeroIndex] = T();
        ++zeroIndex;
        return temp;
    }

    T peek() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return arr[zeroIndex];
    }

    bool isEmpty() {
        return zeroIndex > topIndex;
    }
    int getSize() {
        if (isEmpty()) return 0;
        return topIndex - zeroIndex + 1;
    }

    void print() {
        for (int i = zeroIndex; i <= topIndex; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~Queue() {
        delete[] arr;
    }
};

//int main() {
//        Queue<int> queue;
//    cout << "IS EMPTY: " << queue.isEmpty() << endl;
//    queue.enqueue(10);
//    queue.enqueue(20);
//    queue.enqueue(30);
//    queue.print();
//    cout << "Front Element: " << queue.peek() << endl;
//    cout << "Dequeued Element: " << queue.dequeue() << endl;
//    queue.print();
//	return 0;
//}


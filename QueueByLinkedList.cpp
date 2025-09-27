#include <iostream>
#include "LinkedList.cpp"

using namespace std;

template<class T>
class Queue {
	LinkedList<T>* dataList;
	int size;
public:
	Queue() {
		dataList = new LinkedList<T>();
		size = 0;
	}
	void enqueue(T value) {
		dataList->insertLast(value);
		++size;
	}
	T dequeue(){
		if (this->isEmpty()) {
			throw runtime_error("Queue is empty");
		}
		T temp = dataList->front();
		dataList->deleteFirst();
		--size;
		return temp;
	}

	T peek() {
		if (this->isEmpty()) {
			throw runtime_error("Queue is empty");
		}
		return dataList->front();
	}

	bool isEmpty() {
		return this->size == 0;
	}

	int getSize() {
		return this->size;
	}

	void print() {
		dataList->printList();
	}
	~Queue() {
		delete dataList;
	}

};


//int main(){
//	Queue<int> queue;
//	cout <<"IS EMPTY: " << queue.isEmpty() << endl;
//	queue.enqueue(10);
//	queue.enqueue(20);
//	queue.enqueue(30);
//	cout << "IS EMPTY: " << queue.isEmpty() << endl;
//
//	queue.print();
//	cout << "Front Element: " << queue.peek() << endl;
//	cout << "Dequeued Element: " << queue.dequeue() << endl;
//	queue.print();
//	cout << "-----\n";
//
//	cout << queue.isEmpty()<<endl;
//	while(!queue.isEmpty()) {
//		cout << "Peeked Element: " << queue.peek() << endl;
//		cout << "Dequeued Element: " << queue.dequeue() << endl;
//		cout << "Size: " << queue.getSize() << endl;
//		queue.print();
//		cout << endl;
//	}
//
//	return 0;
//}

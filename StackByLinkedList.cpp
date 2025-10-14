#include <iostream>
#include "LinkedList.cpp"

using namespace std;
template<class T>
class Stack {
	LinkedList<T>* list;
	int length;
	public:
		Stack() {
			list = new LinkedList<T>();
			length = 0;
		}
		void push(T value) {
			list->insertFirst(value);
			++length;
		}
		T pop(){
			if (list->isEmpty()) {
				throw runtime_error("Stack is empty");
			}
			T value = list->front();
			list->deleteFirst();
			--length;
			return value;
		}
		T Peek(){
			if (list->isEmpty()) {
				throw runtime_error("Stack is empty");
			}
			return  list->front();
		}
		bool isEmpty() {
			return this->length == 0;
		}
		void print() {
			list->printList();
		}
		~Stack() {
			delete list;
		}

};


//int main() {
//	Stack<int> stack;
//	stack.push(10);
//	stack.push(20);
//	stack.push(30);
//	stack.print();
//	cout << "Top Element: " << stack.Peek() << endl;
//	cout << "Popped Element: " << stack.pop() << endl;
//	stack.print();
//	return 0;
//}


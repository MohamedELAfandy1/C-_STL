#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
class KeyValuePair{
 	int priority;
 	T value;
 	public:
	KeyValuePair() : priority(), value() {} 
 	KeyValuePair(int _priority, T _value): priority(_priority),value(_value){}
 	
 	int getPriority() const {return priority;}
 	T getValue() const {return value;}
 	void print (){
 		cout<<"dequeued "<<value<<" [ "<<priority<<" ] "<<endl;
	 }
};

template <class T>
class PriorityQueue
{
public:
    KeyValuePair<T> *arr;
    int initialSize;
    int size;
    bool minHeap;

    PriorityQueue(bool _min = true, int _initialSize = 8)
    {
        arr = new     KeyValuePair<T>[_initialSize];
        minHeap = _min;
        size = 0;
        initialSize = _initialSize;
    }

    void resize()
    {
        int newSize = initialSize * 2;
        KeyValuePair<T>*newArr = new KeyValuePair<T>[newSize];
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        initialSize = newSize;
    }

    void enqueue(int p,T _data)
    {
        if (size >= initialSize)
        {
            resize();
        }
        int i = size;
		 KeyValuePair<T> newPair(p, _data);
       arr[i] = newPair;
        ++size;
        int parent = floor((i - 1) / 2);
        if (minHeap)
        {
            if (i > 0)
            {
                while (i > 0 && arr[i].getPriority() < arr[parent].getPriority())
                {
                    swap(arr[i], arr[parent]);
                    i = parent;
                    parent = floor((i - 1) / 2);
                }
            }
        }
        else
        {
            if (i > 0)
            {
                while (arr[i].getPriority() > arr[parent].getPriority())
                {
                    swap(arr[i], arr[parent]);
                    i = parent;
                    parent = floor((i - 1) / 2);
                }
            }
        }
    }

    KeyValuePair<T> dequeue()
    {
        if (size == 0)
            throw runtime_error("Heap is empty");

        int i = 0;
        KeyValuePair<T>  dequeued = arr[i];
        arr[i] = arr[size - 1];
        --size;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int target = i;

            if (minHeap)
            {
                if (left < size && arr[left].getPriority() < arr[target].getPriority())
                    target = left;
                if (right < size && arr[right].getPriority() < arr[target].getPriority())
                    target = right;
            }
            else
            {
                if (left < size && arr[left].getPriority() > arr[target].getPriority())
                    target = left;
                if (right < size && arr[right].getPriority() > arr[target].getPriority())
                    target = right;
            }

            if (target != i)
            {
                swap(arr[i], arr[target]);
                i = target;
            }
            else
                break;
        }

        return dequeued;
    }

    KeyValuePair<T> peek() const
    {
        if (size == 0)
            throw runtime_error("Heap is empty");
        return arr[0];
    }

    void clear()
    {
        size = 0;
    }

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    void printArray()
    {
        cout << "[ ";
        for (int i = 0; i < size; i++)
        {
            cout << arr[i].getValue() <<"  ["<<arr[i].getPriority()<<" ] ";
            if (i != size - 1)
                cout << ", ";
        }
        cout << " ]" << endl;
    }

    void draw()
    {
        if (size == 0)
        {
            cout << "Heap is empty.\n";
            return;
        }
        int k = 0;
        int numOfLevels = floor(log2(size)) + 1;
        cout << "priniting:\n\n";
        for (int i = 0; i < numOfLevels; i++)
        {
            cout << string(pow(2, numOfLevels - 1 - i), ' ');
            for (int j = 0; j < pow(2,i); j++)
            {
                if (k == size)
                    break;
				cout << arr[k].getValue() <<"["<<arr[k].getPriority()<<"]"<< string(pow(2, numOfLevels - i) - 1, ' ');
            	++k;

            }
            cout << endl;
        }
    }	
    ~PriorityQueue() {
    delete[] arr;
}

};

 int main()
 {
    PriorityQueue<int> queue(false);
	queue.enqueue(5, 24);
	queue.enqueue(5, 32);
	queue.enqueue(3, 16);
	queue.enqueue(3, 45);
	queue.enqueue(1, 20);
	queue.enqueue(1, 53);
	queue.enqueue(2, 14);
	queue.enqueue(2, 27);

	queue.printArray();
	queue.draw();

	while(!queue.isEmpty()){
		KeyValuePair<int> p = queue.dequeue();
		p.print();
	}
}
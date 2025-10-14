#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
class Heap
{
public:
    T *arr;
    int initialSize;
    int size;
    bool minHeap;

    Heap(bool _min = true, int _initialSize = 8)
    {
        arr = new T[_initialSize];
        minHeap = _min;
        size = 0;
        initialSize = _initialSize;
    }

    void resize()
    {
        int newSize = initialSize * 2;
        T *newArr = new T[newSize];
        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        initialSize = newSize;
    }

    void insert(T _data)
    {
        if (size >= initialSize)
        {
            resize();
        }
        int i = size;
        arr[i] = _data;
        ++size;
        int parent = floor((i - 1) / 2);
        if (minHeap)
        {
            if (i > 0)
            {
                while (i > 0 && arr[i] < arr[parent])
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
                while (arr[i] > arr[parent])
                {
                    swap(arr[i], arr[parent]);
                    i = parent;
                    parent = floor((i - 1) / 2);
                }
            }
        }
    }

    T pop()
    {
        if (size == 0)
            throw runtime_error("Heap is empty");

        int i = 0;
        T popped = arr[i];
        arr[i] = arr[size - 1];
        --size;

        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int target = i;

            if (minHeap)
            {
                if (left < size && arr[left] < arr[target])
                    target = left;
                if (right < size && arr[right] < arr[target])
                    target = right;
            }
            else
            {
                if (left < size && arr[left] > arr[target])
                    target = left;
                if (right < size && arr[right] > arr[target])
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

        return popped;
    }

    T peek() const
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
            cout << arr[i];
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
                cout << arr[k] << string(pow(2, numOfLevels - i) - 1, ' ');
            	++k;

            }
            cout << endl;
        }
    }	
    ~Heap() {
    delete[] arr;
}

};

// int main()
// {
//     Heap<int> h1(false);
//     h1.insert(2);
//     h1.draw();

//     h1.insert(3);
//     h1.draw();

//     h1.insert(19);

//     h1.draw();
//     h1.insert(8);
//     h1.draw();
//     h1.insert(9);
//     h1.draw();
//     h1.insert(1);
//     h1.draw();

//     h1.insert(5);
//     h1.insert(4);
//     h1.insert(12);
//     h1.insert(22);
//     h1.printArray();
//     h1.draw();

//      h1.pop();
//      h1.draw();
//      h1.pop();
//      h1.draw();
// }
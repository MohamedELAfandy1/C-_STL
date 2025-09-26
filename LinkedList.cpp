#include <iostream>
#include <stdexcept>

using namespace std;
template <class T>
class LinkedListNode
{
public:
    T data;
    LinkedListNode<T> *next;

    LinkedListNode(T _data, LinkedListNode<T> *ptr = NULL) : data(_data), next(ptr) {}
    void print()
    {
        cout << "DATA:   " << data << endl;
        cout << "NODE2:  " << next << endl;
    }
};

template <class T>
class LinkedListIterator
{
public:
    LinkedListNode<T> *currentNode;

    LinkedListIterator(LinkedListNode<T> *_current = NULL) : currentNode(_current) {};

    LinkedListIterator<T> &next()
    {
        this->currentNode = this->currentNode->next;
        return *this;
    }
};

template <class T>
class LinkedList
{
public:
    LinkedListNode<T> *head;
    LinkedListNode<T> *tail;
    int *length;
    int *refCount;

    LinkedList() : head(NULL), tail(NULL), length(new int(0)), refCount(new int(1)) {}

    T front() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("List is empty");
        }
        return this->head->data;
    }

    T back() const
    {
        if (this->tail == NULL)
        {
            throw runtime_error("List is empty");
        }
        return this->tail->data;
    }

    bool isEmpty() const
    {
        return head == NULL;
    }

    int getLength() const
    {
        return *length;
    }

    void insertLast(T _data)
    {
        LinkedListNode<T> *newNode = new LinkedListNode<T>(_data);
        // Check if linkedlist is empty
        if (this->head == NULL)
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            this->tail->next = newNode;
            this->tail = newNode;
        }
        ++(*length);
        return;
    }

    void insertLast(LinkedListNode<T> *newNode)
    {
        // Nodes passed to any function are stored in heap(declared by new) 'as dcomented in documentation'
        // But, if node is stored in stack
        // Make new Node and store it in heap to be kept after ending of scope
        // and avoid dangling pointers [node deleted and affect other pointers]
        // we use node->data only, use next in merge between two lists
        if (newNode != NULL)
        {
            newNode->next = NULL;
            // LinkedListNode *newNodeInHeap = new LinkedListNode(newNode->data);
            // Check if linkedlist is empty
            if (this->head == NULL)
            {
                this->head = newNode;
                this->tail = newNode;
            }
            else
            {
                this->tail->next = newNode;
                this->tail = newNode;
            }
            ++(*length);
        }
    }

    void insertAfter(T nodeValue, T value, int skip = 0)
    {
        LinkedListNode<T> *foundNode = this->find(nodeValue, skip);
        if (foundNode != NULL)
        {
            LinkedListNode<T> *newNode = new LinkedListNode<T>(value, foundNode->next);
            foundNode->next = newNode;
            if (foundNode == this->tail)
                this->tail = newNode;
            ++(*length);
            return;
        }
        cout << "The Item Not Found\n";
    }

    void insertAfter(LinkedListNode<T> *&n, T value)
    {
        if (n != NULL)
        {
            LinkedListNode<T> *foundNode = this->findByAddress(n);
            if (foundNode != NULL)
            {
                LinkedListNode<T> *newNode = new LinkedListNode<T>(value, n->next);
                n->next = newNode;
                if (n == this->tail)
                    this->tail = newNode;
                ++(*length);
                return;
            }
        }
        cout << "The Item Not Found\n";
    }

    void insertBefore(T nodeValue, T value, int skip = 0)
    {
        if (this->head == NULL)
        {
            cout << "List is empty\n";
            return;
        }

        LinkedListNode<T> *ParentNode = this->findParent(nodeValue, skip);
        LinkedListNode<T> *FoundNode = (ParentNode != NULL) ? ParentNode->next : NULL;

        // if there is no parent this means that the node to be found is head or not found at all
        if (this->head->data == nodeValue && skip == 0)
        {
            FoundNode = this->head;
        }

        if (FoundNode == NULL)
        {
            cout << "Item Not Found\n";
            return;
        }

        LinkedListNode<T> *newNode = new LinkedListNode<T>(value, FoundNode);

        if (FoundNode == this->head)
        {
            this->head = newNode;
            ++(*length);
        }
        else if (ParentNode != NULL)
        {
            ParentNode->next = newNode;
            ++(*length);
        }
        else
        {
            delete newNode;
            cout << "Parent Not Found\n";
        }
    }

    void insertBefore(LinkedListNode<T> *node, T value)
    {
        // list is empty
        if (this->head == NULL)
        {
            cout << "List is empty\n";
            return;
        }

        if (node == NULL)
        {
            cout << "Item Not Found\n";
            return;
        }

        LinkedListNode<T> *newNode = new LinkedListNode<T>(value, node);

        if (node == this->head)
        {
            this->head = newNode;
            ++(*length);
        }
        else
        {
            LinkedListNode<T> *ParentNode = this->findParentByAddress(node);
            if (ParentNode != NULL)
            {
                ParentNode->next = newNode;
                ++(*length);
            }
            else
            {
                delete newNode;
                cout << "Parent Not Found\n";
                return;
            }
        }
    }

    void deletePointer(T nodeValue, int skip = 0)
    {
        // If List Is Empty
        if (this->head == NULL)
        {
            cout << "List is empty\n";
            return;
        }
        // If List Have One Element
        else if (this->head->data == nodeValue && this->tail->data == nodeValue && skip == 0)
        {
            delete this->head;
            this->head = this->tail = NULL;
            --(*length);
            return;
        }
        // If I Want To Delete Head
        else if (this->head->data == nodeValue && skip == 0)
        {
            LinkedListNode<T> *newHead = this->head->next;
            delete this->head;
            this->head = newHead;
            --(*length);
            return;
        }
        else
        {
            LinkedListNode<T> *ParentNode = this->findParent(nodeValue, skip);
            if (ParentNode != NULL && ParentNode->next != NULL)
            {
                LinkedListNode<T> *FoundNode = ParentNode->next;
                ParentNode->next = FoundNode->next;
                if (FoundNode == this->tail) // handle tail case safely
                    this->tail = ParentNode;
                delete FoundNode;
                --(*length);
            }
            else
            {
                cout << "Item Not Found\n";
            }
        }
    }

    void deletePointer(LinkedListNode<T> *node)
    {
        if (node == NULL)
        {
            cout << "Item Not Found\n";
            return;
        }
        // If List Is Empty
        if (this->head == NULL)
        {
            cout << "List is empty\n";
            return;
        }
        // If List Have One Element
        else if (this->head == node && this->tail == node)
        {
            this->head = this->tail = NULL;
            --(*length);
        }
        // If I Want To Delete Head
        else if (this->head == node)
        {
            this->head = node->next;
            --(*length);
        }
        // If I Want To Delete Tail
        else if (this->tail == node)
        {
            LinkedListNode<T> *ParentNode = this->findParentByAddress(node);
            if (ParentNode != NULL)
            {
                this->tail = ParentNode;
                this->tail->next = NULL;
                --(*length);
            }
            else
            {
                cout << "Parent not found\n";
                return;
            }
        }
        // If I Want To Delete Node From Middle Of List
        else
        {
            // LinkedListNode *FoundNode = this->find(nodeValue);
            LinkedListNode<T> *ParentNode = this->findParentByAddress(node);
            if (ParentNode != NULL && ParentNode->next != NULL)
            {
                ParentNode->next = node->next;
                --(*length);
            }
            else
            {
                cout << "Item Not Found\n";
                return;
            }
        }
        delete node;
    }

    LinkedListNode<T> *find(T nodeValue, int skip = 0)
    {
        LinkedListIterator<T> itr = this->begin();
        while (itr.currentNode != NULL)
        {
            if (itr.currentNode->data == nodeValue)
            {
                if (skip == 0)
                    return itr.currentNode;
                --skip;
            }
            itr.next();
        }
        return NULL;
    }

    LinkedListNode<T> *findParent(T nodeValue, int skip = 0)
    {
        LinkedListIterator<T> itr = this->begin();
        while (itr.currentNode != NULL)
        {
            if (itr.currentNode->next != NULL && itr.currentNode->next->data == nodeValue)
            {
                if (skip == 0)
                    return itr.currentNode;
                --skip;
            }
            itr.next();
        }
        return NULL;
    }

    LinkedListNode<T> *findParentByAddress(LinkedListNode<T> *node)
    {
        LinkedListIterator<T> itr = this->begin();
        while (itr.currentNode != NULL)
        {
            if (itr.currentNode->next == node)
            {
                return itr.currentNode;
            }
            itr.next();
        }
        return NULL;
    }
    LinkedListNode<T> *findByAddress(LinkedListNode<T> *node)
    {
        LinkedListIterator<T> itr = this->begin();
        while (itr.currentNode != NULL)
        {
            if (itr.currentNode == node)
            {
                return itr.currentNode;
            }
            itr.next();
        }
        return NULL;
    }

    LinkedListIterator<T> begin()
    {
        return LinkedListIterator<T>(this->head);
    }

    void printList()
    {
        LinkedListIterator<T> itr = this->begin();
        while (itr.currentNode != NULL)
        {
            cout << itr.currentNode->data << " ";
            itr.next();
        }
        cout << "\n";
    }

    //! Copy constructor (shallow copy)
    /*LinkedList(const LinkedList<T> &other)
    {
        this->head = other.head;
        this->tail = other.tail;
        this->length = other.length;
        this->refCount = other.refCount;
        ++(*refCount);
    }
    */
    //! Shallow Assignment Operator
    /*LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if (this != &other)
        {
            if (--(*refCount) == 0)
            {
                // if it was the last reference, delete all nodes
                LinkedListNode<T> *current = head;
                while (current != NULL)
                {
                    LinkedListNode<T> *next = current->next;
                    delete current;
                    current = next;
                }
                delete refCount;
            }

            head = other.head;
            tail = other.tail;
            length = other.length;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }
    */

    //! Explicit deep copy function
    LinkedList copy()
    {
        // cout << "Deep Copy Function\n";
        LinkedListIterator<T> itr = this->begin();
        LinkedList copiedList;
        while (itr.currentNode != NULL)
        {
            copiedList.insertLast(itr.currentNode->data);
            itr.next();
        }
        // copiedList.printList();
        return copiedList;
    }

    //! Copy constructor (Deep Copy)
    LinkedList(const LinkedList<T> &other)
    {
        // cout << "Copy Constractor\n";
        this->head = this->tail = NULL;
        this->length = new int(0);
        this->refCount = new int(1); // new ownership

        LinkedListNode<T> *current = other.head;
        while (current != NULL)
        {
            this->insertLast(current->data);
            current = current->next;
        }
    }

    //! Deep Assignment Operator
    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        // cout << "Assignment Operator\n";
        if (this != &other)
        {
            // clear old data
            if (--(*refCount) == 0)
            {
                LinkedListNode<T> *current = head;
                while (current)
                {
                    LinkedListNode<T> *next = current->next;
                    delete current;
                    current = next;
                }
                delete refCount;
                delete length;
            }

            // start fresh
            this->head = this->tail = NULL;
            this->length = new int(0);
            this->refCount = new int(1);

            LinkedListNode<T> *current = other.head;
            while (current != NULL)
            {
                this->insertLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    //! Explicit shallow copy function
    LinkedList<T> shallowCopy()
    {
        // cout << "Shallow copy\n";
        LinkedList<T> copy;
        copy.head = this->head;
        copy.tail = this->tail;
        copy.length = this->length;
        copy.refCount = this->refCount;
        ++(*refCount);
        return copy;
    }

    ~LinkedList()
    {
        if (--(*refCount) == 0)
        {
            LinkedListNode<T> *current = head;
            while (current)
            {
                LinkedListNode<T> *next = current->next;
                delete current;
                current = next;
            }
            delete refCount;
            delete length;
        }
    }
};
/*
int main()
{
    LinkedList<int> l1;
    l1.insertLast(1);
    l1.insertLast(3);
    l1.insertBefore(3,2);
    l1.insertAfter(3, 4);
    l1.printList();
    cout<<l1.back()<<endl;


    LinkedListNode<int>* ln = new LinkedListNode<int>(0);
    l1.insertLast(ln);
    l1.printList();
    l1.insertBefore(ln, 5);
    l1.insertAfter(ln, 66);
    l1.printList();
    cout << l1.back() << endl;
    cout<<l1.front();
    l1.insertLast(5);


    l1.deletePointer(ln);
    l1.deletePointer(5,1);
    l1.deletePointer(1);
    l1.printList();
    cout << l1.front()<<endl;

    cout << "\n-----------------------\n";
    LinkedList <int> l2(l1);    //copy constractor
    l2.printList();
    LinkedList <int> l3=l1;     //copy constractor
    l3.printList();
    LinkedList <int> l4 = l1.copy();    //function
    l4.printList();
    LinkedList <int> l5;
    l5.insertLast(777);
    l5.printList();
    l5 = l1;    //assignment operator
    l5.printList();

    LinkedList<int> l6 = l1.shallowCopy();  //shallow copy
    l6.printList();
    l1.insertLast(88);
    l1.printList();
    l6.printList();

}
*/

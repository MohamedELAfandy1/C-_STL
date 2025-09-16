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

    LinkedListIterator<T> next()
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
    int length;
    //	int* refCount;  // reference count for shallow copy //to avoid double deletion of nodes

    LinkedList() : head(NULL), tail(NULL), length(0),
    //	 refCount(new int(1))
    {
    }
    //    shallow copy
    //    LinkedList(const LinkedList<T>& other) {
    //        this->head = other.head;
    //        this->tail = other.tail;
    //        this->length = other.length;
    //		  this->refCount = other.refCount;
    //        ++(*refCount);
    //    }

    //Deep Copy
    LinkedList copy()
    {
        LinkedListIterator<T> itr = this->begin();
        LinkedList copiedList;
        while (itr.currentNode != NULL)
        {
            copiedList.insertLast(itr.currentNode->data);
            itr.next();
        }
        return copiedList;
    }

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
        ++length;
        return;
    }

    void insertLast(LinkedListNode<T> *newNode)
    {
        // Make new Node and store it in heap to be kept aftor ending of scope
        // and avoid dangling pointers [node deleted and affect other pointers]
        // we use node->data only, use next in merge between two lists
        if (newNode != NULL)
        {
            //            LinkedListNode *newNodeInHeap = new LinkedListNode(newNode->data);
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
            ++length;
        }
    }

    void insertAfter(T nodeValue, T value)
    {
        LinkedListNode<T> *foundNode = this->find(nodeValue);
        if (foundNode != NULL)
        {
            LinkedListNode<T> *newNode = new LinkedListNode<T>(value, foundNode->next);
            foundNode->next = newNode;
            if (foundNode == this->tail)
                this->tail = newNode;
            ++length;
            return;
        }
        cout << "The Item Not Found\n";
    }

    void insertAfter(LinkedListNode<T> *&n, T value)
    {
        if (n != NULL)
        {
            LinkedListNode<T> *newNode = new LinkedListNode<T>(value, n->next);
            n->next = newNode;
            if (n == this->tail)
                this->tail = newNode;
            ++length;
            return;
        }
        cout << "The Item Not Found\n";
    }

    void insertBefore(T nodeValue, T value)
    {
        LinkedListNode<T> *FoundNode = this->find(nodeValue);
        if (FoundNode != NULL)
        {
            LinkedListNode<T> *newNode = new LinkedListNode<T>(value, FoundNode);
            if (FoundNode == this->head)
            {
                this->head = newNode;
                ++length;
            }
            else
            {
                LinkedListNode<T> *parent = this->findParent(nodeValue);
                if (parent != NULL)
                {
                    parent->next = newNode;
                    ++length;
                }
                else
                {
                    delete newNode;
                    cout << "Parent Not Found";
                }
            }
        }
        else
        {
            cout << "Item Not Found\n";
        }
    }

    void insertBefore(LinkedListNode<T> *node, T value)
    {
        if (node != NULL)
        {
            LinkedListNode<T> *newNode = new LinkedListNode<T>(value, node);
            if (node == this->head)
            {
                this->head = newNode;
                ++length;
            }
            else
            {
                LinkedListNode<T> *parent = this->findParentByAddress(node);
                if (parent != NULL)
                {
                    parent->next = newNode;
                    ++length;
                }
                else
                {
                    delete newNode;
                    cout << "Parent Not Found";
                }
            }
        }
        else
        {
            cout << "Item Not Found\n";
        }
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
            --length;
            return;
        }
        // If I Wnat To Delete Head
        else if (this->head->data == nodeValue && skip == 0)
        {
            LinkedListNode<T> *newHead = this->head->next;
            delete this->head;
            this->head = newHead;
            --length;
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
                --length;
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
            --length;
        }
        // If I Wnat To Delete Head
        else if (this->head == node)
        {
            this->head = node->next;
            --length;
        }
        // If I Want To Delete Tail
        else if (this->tail == node)
        {
            LinkedListNode<T> *ParentNode = this->findParentByAddress(node);
            if (ParentNode != NULL)
            {
                this->tail = ParentNode;
                this->tail->next = NULL;
                --length;
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
                --length;
            }
            else
            {
                cout << "Item Not Found\n";
                return;
            }
        }
        delete node;
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
    
    bool isEmpty() const
    {
        return head == NULL;
    }

    void clear()
    {
        //    	if(--(*refCount) == 0){	//Decrese Reference Count until it equals 0, so you can delete nodes
        LinkedListNode<T> *current = this->head;
        while (current != NULL)
        {
            LinkedListNode<T> *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        this->head = this->tail = NULL;
        this->length = 0;
    }
    ~LinkedList()
    {
        this->clear();
    }
};

int main()
{
    LinkedList<int> l1;
    l1.insertLast(1);
    l1.insertLast(3);
    l1.insertLast(7);
    cout << l1.length << endl;
    l1.printList();

}

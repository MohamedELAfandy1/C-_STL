#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <functional>
using namespace std;

template <typename T>
string toString(const T& value) {
    stringstream ss;
    ss << value;
    return ss.str();
}


template <class Tkey, class Tvalue>
class HashTable
{
    class KeyValuePair
    {
        Tkey key;
        Tvalue value;
        bool isEmptyValue;
        bool isRemovedValue;

    public:
        KeyValuePair() : key(), value(), isEmptyValue(true), isRemovedValue(false) {}
        KeyValuePair(Tkey _key, Tvalue _value) : key(_key), value(_value), isEmptyValue(false), isRemovedValue(false) {}

        void setValue(Tvalue newVal)
        {
            value = newVal;
            isEmptyValue = false;
            isRemovedValue = false;
        }

        Tkey getKey() const { return key; }
        Tvalue getValue() const { return value; }

        void clear() {
            key = Tkey();
            value = Tvalue();
            isEmptyValue = true;
            isRemovedValue = true;
        }
        bool isEmpty() const { return isEmptyValue; }
        bool isRemoved() const { return isRemovedValue; }
        void setEmptyValue(bool val) { isEmptyValue = val; }
        void setRemovedValue(bool val) { isRemovedValue = val; }
    };

    KeyValuePair* enteries;
    int initialSize;
    int length;
    bool debug;

public:
    HashTable(int _initialSize = 3, bool _debug = false) {
        enteries = new KeyValuePair[_initialSize];
        initialSize = _initialSize;
        length = 0;
        debug = _debug;
    }

    ~HashTable() {
        delete[] enteries;
    }

    unsigned hash(const Tkey & key) {
        string keyStr = toString(key);
        const unsigned offset_basis = 2166136261;
        const unsigned FNVPrime = 16777619;
        unsigned hash = offset_basis;

        for (unsigned i = 0; i < keyStr.size(); i++)
        {
            hash ^= static_cast<unsigned char>(keyStr[i]);
            hash *= FNVPrime;
        }
        hash %= initialSize;
        if (debug)	cout << "[HASH]   " << key << ", " << hash << endl;
        return hash;
    }

    //Linear Proping 
    unsigned collesionHundle(Tkey _key, unsigned hash, bool set) {
        unsigned newHash;
        int firstRemovedIndex = -1;
        for (int i = 1; i < initialSize; i++)
        {
            newHash = (hash + i) % initialSize;
            if (debug)	cout << "[COLL] " << _key << " " << hash << " --> " << newHash << endl;

            if (set) {
                //Update value                    
                if (!enteries[newHash].isEmpty() && enteries[newHash].getKey() == _key) {
                    return newHash;
                }
                if (enteries[newHash].isEmpty()) {
                    //if removed will not return directly and will continue looping for checking if _key = other key in array
                    if (enteries[newHash].isRemoved()) {
                        if (firstRemovedIndex == -1) {
                            firstRemovedIndex = newHash;
                        }
                    }
                    else {
                        //return newHash if there is no skipped removed index 
                        return (firstRemovedIndex != -1) ? firstRemovedIndex : newHash;
                    }
                }
            }
            else {
                if (enteries[newHash].getKey() == _key)
                    return newHash;

                else if (enteries[newHash].isEmpty() && !enteries[newHash].isRemoved()) break;

                continue;
            }
        }
        return -1;
    }


    void remove(Tkey _key) {
        unsigned hashed = hash(_key);

        if (enteries[hashed].getKey() == _key) {
            enteries[hashed].clear();
            --length;
            return;
        }
        else
        {
            unsigned newHash = collesionHundle(_key, hashed, false);
            if (newHash == (unsigned)-1) {
                if (debug)	cout << "[REMOVE] Key not found: " << _key << endl;
                return;
            }
            enteries[newHash].clear();
            --length;
        }
    }

    void set(Tkey _key, Tvalue _value) {
        if (length == initialSize)		resize();

        unsigned hashed = hash(_key);
        if (enteries[hashed].isEmpty()) {
            KeyValuePair newPair(_key, _value);
            enteries[hashed] = newPair;
            ++length;
        }
        else if (enteries[hashed].getKey() == _key) {
            enteries[hashed].setValue(_value);
        }
        else
        {
            unsigned newHash = collesionHundle(_key, hashed, true);
            if (newHash != (unsigned)-1) {
                if (enteries[newHash].isEmpty()) {
                    KeyValuePair newPair = KeyValuePair(_key, _value);
                    enteries[newHash] = newPair;
                    ++length;
                }
                else {
                    enteries[newHash].setValue(_value);
                }
            }
            else {
                throw runtime_error("Table Full");
            }
        }
    }

    Tvalue get(Tkey _key) {
        unsigned hashed = hash(_key);
        if (enteries[hashed].getKey() == _key) {
            return enteries[hashed].getValue();
        }
        else {
            unsigned newHash = collesionHundle(_key, hashed, false);
            if (newHash == (unsigned)-1) {

                if (debug)	 cout << "[GET] Key not found: " << _key << endl;
                return Tvalue();
            }
            return  enteries[newHash].getValue();
        }
    }


    void resize() {
        int newSize = initialSize * 2;
        if (debug)	cout << "[RESIZE]   Resized From " << initialSize << " to " << newSize << endl;

        KeyValuePair* oldEntries = enteries;
        int oldSize = initialSize;

        enteries = new KeyValuePair[newSize];
        initialSize = newSize;
        length = 0;

        for (int i = 0; i < oldSize; i++)
        {
            if (!oldEntries[i].isEmpty()) {
                set(oldEntries[i].getKey(), oldEntries[i].getValue());
            }

        }
        delete[] oldEntries;
    }

    int getSize() const {
        return length;
    }

    bool isEmpty() const {
        return length <= 0;
    }

    void print() {
        if (isEmpty())
        {
            cout << "Hash table Is Empty\n";
            return;
        }

        for (int i = 0; i < initialSize; i++)
        {
            if (!enteries[i].isEmpty())
                cout << i << " => " << enteries[i].getKey() << " : " << enteries[i].getValue() << endl;
            else
                cout << i << " => [EMPTY]" << endl;
        }
    }
};

//int main()
//{
//    HashTable<string, string>* ht = new HashTable<string, string>;
//    ht->print();
//    ht->set("apple", "a.com");
//    ht->set("banana", "b.com");
//    ht->set("orange", "o.com");
//
//    ht->print();
//    ht->set("peach", "p.com");
//    cout << "----\n";
//    ht->set("orange", "o2.com");
//    ht->print();
//    cout << "----\n";
//
//    cout << "Get banana => " << ht->get("banana") << endl;
//    cout << "Get orange => " << ht->get("orange") << endl;
//    cout << "Get grapes => " << ht->get("grapes") << endl;
//    cout << "----\n";
//
//
//
//    return 0;
//}


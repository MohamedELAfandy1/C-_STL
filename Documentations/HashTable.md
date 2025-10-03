# HashTable Documentation

## Overview
`HashTable` is a generic hash table implementation in C++ that supports storing key-value pairs with generic types (`Tkey` and `Tvalue`).  
It uses **FNV-1a hashing** with **linear probing** to handle collisions. The table automatically resizes when full.

---

## Features
- Generic keys and values.
- Linear probing for collision handling.
- Support for deleted entries (tombstones).
- Automatic resizing.
- Optional debug mode to trace hashing and collision steps.
- Simple API to set, get, remove, and print entries.

---

## Class Definition

### `HashTable<Tkey, Tvalue>`

**Data Members**
- `KeyValuePair* enteries` — array of key-value pairs.
- `int initialSize` — current table capacity.
- `int length` — number of elements stored.
- `bool debug` — enable debug logging.

**Public Methods**
| Method | Description |
|--------|-------------|
| `HashTable(int _initialSize = 3, bool _debug = false)` | Constructor. Initializes the table with a given size and optional debug mode. |
| `~HashTable()` | Destructor. Frees allocated memory. |
| `void set(Tkey _key, Tvalue _value)` | Inserts a key-value pair or updates the value if key exists. Resizes table if needed.  With time complexity O(1) |
| `Tvalue get(Tkey _key)` | Retrieves the value associated with the key. Returns `Tvalue()` if key is not found.  With time complexity O(1) |
| `void remove(Tkey _key)` | Removes a key-value pair and marks the slot as deleted.  With time complexity  (1) |
| `void resize()` | Doubles the table size and re-inserts all existing entries. |
| `int getSize()` | Returns the number of elements currently in the table. |
| `bool isEmpty()` | Returns true if the table is empty. |
| `void print()` | Prints all entries in the table, including empty slots. |

**Private Methods**
| Method | Description |
|--------|-------------|
| `unsigned hash(const Tkey & key)` | Computes the hash value for a given key using FNV-1a algorithm. |
| `unsigned collesionHundle(Tkey _key, unsigned hash, bool set)` | Handles collisions using linear probing. Returns index for insertion or search. |

---

### Inner Class: `KeyValuePair<Tkey, Tvalue>`

**Data Members**
- `Tkey key` — stored key.
- `Tvalue value` — stored value.
- `bool isEmptyValue` — true if slot is empty.
- `bool isRemovedValue` — true if slot was removed.

**Methods**
| Method | Description |
|--------|-------------|
| `KeyValuePair()` | Default constructor. Initializes an empty slot. |
| `KeyValuePair(Tkey _key, Tvalue _value)` | Constructor to initialize a key-value pair. |
| `void setValue(Tvalue newVal)` | Updates the value and marks the slot as occupied. |
| `Tkey getKey()` | Returns the key. |
| `Tvalue getValue()` | Returns the value. |
| `void clear()` | Clears the slot and marks it as removed. |
| `bool isEmpty()` | Returns true if the slot is empty. |
| `bool isRemoved()` | Returns true if the slot was removed. |
| `void setEmptyValue(bool val)` | Sets the empty flag manually. |
| `void setRemovedValue(bool val)` | Sets the removed flag manually. |

---

## Usage Example

```cpp
#include <iostream>
#include "HashTable.cpp"
using namespace std;

int main() {
    HashTable<string, string> ht;

    ht.set("apple", "a.com");
    ht.set("banana", "b.com");
    ht.set("orange", "o.com");

    cout << "Get apple: " << ht.get("apple") << endl;
    cout << "Get banana: " << ht.get("banana") << endl;

    ht.remove("banana");

    ht.print();

    return 0;
}
```

**Output Example**
```
Get apple: a.com
Get banana: b.com
0 => [EMPTY]
1 => orange : o.com
2 => apple : a.com
```

---

## Notes
- The table uses **linear probing**, which may lead to clustering if many keys collide.
- Deleted entries are marked as "removed" to allow proper probing for future insertions.
- Automatic resizing ensures the table grows dynamically when capacity is reached.
- Debug mode (`debug = true`) prints hash calculations and collision handling steps.
- Works for any types that can be converted to `string` via `toString`.

---


# Dictionary Class Documentation

## Overview
The `Dictionary` class is a simple implementation of a key-value data structure using dynamic arrays in C++.  
It provides functionality to store, retrieve, update, and delete key-value pairs, similar to a basic map/dictionary.

---

## Class: Dictionary\<Tkey, Tvalue\>

### Inner Class: KeyValuePair
- **Members:**
  - `Tkey key;`
  - `Tvalue value;`
- **Constructors:**
  - `KeyValuePair()` – Default constructor (initializes key and value with default values).
  - `KeyValuePair(Tkey _key, Tvalue _value)` – Parameterized constructor.
- **Methods:**
  - `Tkey getKey() const` – Returns the key.
  - `Tvalue getValue() const` – Returns the value.
  - `void setValue(Tvalue newVal)` – Updates the value.

---

### Members of Dictionary
- `KeyValuePair* entries;` – Dynamic array of key-value pairs.
- `int initialSize;` – Current capacity of the dictionary.
- `int length;` – Number of key-value pairs currently stored.

---

### Constructors & Destructor
- `Dictionary(int _initialSize = 3)` – Initializes dictionary with given initial size (default = 3).
- `~Dictionary()` – Destructor that frees allocated memory.

---

### Methods
#### `void resize()`
- Resizes the internal array when capacity is reached.  
- New size = `initialSize + length`.

#### `int getSize()`
- Returns the number of stored elements.

#### `void set(Tkey _key, Tvalue _value)`
- If `_key` already exists, updates its value.  
- Otherwise, inserts a new key-value pair.  
- Automatically resizes if the capacity is full.

#### `Tvalue get(Tkey _key)`
- Returns the value for the given key.  
- If the key does not exist, returns Throw exception `Key not found in Dictionary`.  

#### `void remove(Tkey _key)`
- Removes a key-value pair if it exists.  
- Swaps with the last element to maintain array consistency.

#### `bool isEmpty()`
- Returns `true` if dictionary contains no elements.

#### `void print()`
- Prints all key-value pairs in the dictionary.

---

## Example Usage

```cpp
int main() {
    Dictionary<string, string> dic;
    dic.print(); // Dictionary is empty

    dic.set("Mohamed", "Mohamed@gmail.com");
    dic.set("Ali", "Ali@gmail.com");
    dic.print();

    cout << "Size: " << dic.getSize() << endl;

    dic.set("Ali", "Ali2@gmail.com");
    dic.set("Ahmed", "Ahmed@gmail.com");
    dic.set("Amr", "Amr@gmail.com");
    dic.print();

    cout << dic.get("Mohamed") << endl;

    dic.remove("Ali");
    dic.print();

    return 0;
}
```

---

## Conclusion
This `Dictionary` class demonstrates the fundamental concepts of dynamic memory management, key-value storage, and simple collection handling in C++.  
It serves as a learning example for building custom data structures.

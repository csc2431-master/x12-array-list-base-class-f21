//
// Interface Definition for the ArrayList Base Class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
using std::ostream;

template <typename ItemType>
class ArrayList {
public:
    ArrayList(size_t capacity);
    ~ArrayList();
    ArrayList(const ArrayList&);
    const ArrayList<ItemType>& operator=(const ArrayList&);

    // Other methods
    bool Get(size_t position, ItemType& item) const;
    int Find(const ItemType& item, size_t start = 0) const;
    virtual bool Insert(size_t position, const ItemType& item) = 0;
    bool Replace(size_t position, const ItemType& item);
    bool Swap(size_t position1, size_t position2);
    virtual bool Remove(size_t position, ItemType& item) = 0;
    void Clear();

    size_t Size() const;

    bool CheckConsistency() const;

    // Stream output
    friend ostream& operator<<(ostream& os, const ArrayList& list) {
        os << "[";
        for (size_t position = 0; position < list._size; position ++) {
            if (position > 0) {
                os << ", ";
            }
            os << list._array[position];
        }
        return os << "]";
    }

protected:
    ItemType* _array;
    size_t _size;
    size_t _capacity;
};

/**
 * Constructor
 * Creates an empty list.
 */
template <typename ItemType>
ArrayList<ItemType>::ArrayList(size_t capacity) {
    this->_array = new ItemType[capacity];
    this->_size = 0;
    this->_capacity = capacity;
}

/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
template <typename ItemType>
ArrayList<ItemType>::~ArrayList() {
    delete[] _array;
}

/**
 * Copy Constructor
 * Creates a deep copy of the list.
 * The running time of the whole method is O(N) time where N is the
 * length of the list
 * @param other the list to be copied
 */
template <typename ItemType>
ArrayList<ItemType>::ArrayList(const ArrayList& other) {
    _array = new ItemType[other._capacity];
    for (size_t i = 0; i < other._size; i ++) {
        _array[i] = other._array[i];
    }
    _size = other._size;
    _capacity = other._capacity;
}

/**
 * Copy assignment operator
 * Enables deep copy assignment using the operator = overload.
 * Uses the copy constructor to copy the rhs.  Then swaps internals of
 * the copy with this.  By doing it this way, the old contents
 * of this will be automatically freed when the method finishes.
 * The running time of this method is the same as the copy
 * constructor , i.e. O(N)
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
template <typename ItemType>
const ArrayList<ItemType>& ArrayList<ItemType>::operator=(const ArrayList<ItemType>& rhs) {
    if (this != &rhs) {
        delete[] _array;
        _array = new ItemType[rhs._capacity];
        for (size_t i = 0; i < rhs._size; i ++) {
            _array[i] = rhs._array[i];
        }
        _size = rhs._size;
        _capacity = rhs._capacity;
    }
    return *this;
}

/**
 * Get  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the item found at position
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Get(size_t position, ItemType& item) const {
    if (position < _size) {
        item = _array[position];
        return true;
    }
    return false;
}

/**
 * Searches for the position of the first matching item in the list starting
 * at position "start".  The method performs a linear search for the item.
 * If the element is found it returns the position, if it is not found it
 * returns -1.
 * The running time of this method depends on where the search starts
 * and where the item is found (if it is found)
 * @param item the object that the client is searching for.
 * @param start position at which to start the search
 * @return the position of the element if found, -1 otherwise.
 */
template <typename ItemType>
int ArrayList<ItemType>::Find(const ItemType& item, size_t start)  const {
    for (size_t i = start; i < _size; i++) {
        if (_array[i] == item) {
            return i;
        }
    }
    return -1;
}

/**
 * Replace  the item at a specified position
 * This method runs in O(1) time.
 * @param position the position of the element to retrieve.
 * @param item the new item to insert in the old one's place
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Replace(size_t position, const ItemType& item) {
    if (position < _size) {
        _array[position] = item;
        return true;
    }
    return false;
}

/**
 * Swap elements in specified positions
 * This method runs in O(1) time.
 * @param position1 the position of the first element
 * @param position2 the position of the second element
 * @return true if valid positions were given, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::Swap(size_t position1, size_t position2) {
    if (position1 < _size && position2 < _size) {
        ItemType tmp;

        tmp = _array[position1];
        _array[position1] = _array[position2];
        _array[position2] = tmp;
        return true;
    }
    return false;
}

/**
 * Clear the list
 * and then resetting _head to nullptr.
 * This method runs in O(1) time
 * There is no need to free the string values
 * that will occur when the class destructs
 */
template <typename ItemType>
void ArrayList<ItemType>::Clear() {
    _size = 0;
}

/**
 * Returns the number of itmes in the array
 * This method runs in O(1) time
 * @return current number of items in array
 */
template <typename ItemType>
size_t ArrayList<ItemType>::Size() const {
    return _size;
}

/**
 * Checks if list data structure appears to be consistent
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool ArrayList<ItemType>::CheckConsistency() const {
    return _size <= _capacity;
};

#endif //ARRAYLIST_H

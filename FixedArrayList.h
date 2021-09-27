//
// Interface Definition for the FixedArrayList Class as a derived class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef FIXEDARRAYLIST_H
#define FIXEDARRAYLIST_H

#include "ArrayList.h"

template <typename ItemType>
class FixedArrayList : public ArrayList<ItemType>  {
public:
    FixedArrayList(size_t capacity)
        : ArrayList<ItemType>(capacity) {};

    bool Insert(size_t position, const ItemType& item) override;
    bool Remove(size_t position, ItemType& item) override;

};

/**
 * Inserts an element into a given position so long as the position is valid
 * and the list is not filled to capacity.
 * THe running time of inserting at the start is O(N), it's O(1) if you are
 * inserting at the end.
 * @param item what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise.
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Insert(size_t position, const ItemType& item) {
    if (position > this->_size) {
        return false;
    }
    else
    {
        if (this->_size == this->_capacity) {
            return false;
        }

        // Shift out elements to make room for insertion
        for (size_t i = this->_size; i > position; i --) {
            this->_array[i] = this->_array[i-1];
        }
        // Insert the element
        this->_array[position] = item;
        this->_size ++;
        return true;
    }
}

/**
 * Removes the item at position, so long as the position is valid. The item previously
 * stored in the list is returned in the supplied parameter.
 * THe running time of removing the first element is  O(N), it's O(1) if you are
 * removing the last element.
 * @param position the position of the element to be removed.
 * @param item the item previously stored in the list
 * @return true if node could be deleted, false if position at end of list or invalid,
 */
template <typename ItemType>
bool FixedArrayList<ItemType>::Remove(size_t position, ItemType& item) {
    if (position >= this->_size) {
        return false;
    }
    else {
        item = this->_array[position];

        // Close up the gap
        for (size_t i = position; i < this->_size-1; i ++) {
            this->_array[i] = this->_array[i+1];
        }
        this->_size--;

        return true;
    }
}


#endif //FIXEDARRAYLIST_H

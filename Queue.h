//
// Interface Definition for the template version of the Queue Class
// Uses a circular array implementation
// Author: Max Benson
// Date: 08/16/2021
//

#ifndef QUEUE_H
#define QUEUE_H

const int MOST_ITEMS_IN_QUEUE = 100;

template <typename ItemType>
class Queue {
public:
    Queue();

    bool IsEmpty() const;
    size_t Size() const;

    ItemType Dequeue();
    bool Enqueue(const ItemType& item);

    friend ostream& operator<<(ostream& os, const Queue& queue) {
        os << queue._list;
    }

private:
    VariableArrayList<ItemType> _list;
};

/**
* Default constructor
*/
template <typename ItemType>
Queue<ItemType>::Queue()
{
    //no need
}

/**
* Returns whether queue is empty
* @return true if queue empty, false otherwise.
*/
template <typename ItemType>
bool Queue<ItemType>::IsEmpty() const
{
    if(_list.Size() == 0)
    {
        return true;
    }
    return false;
}

/**
* Returns number of items in queue
* @return number of items enqueued
*/
template <typename ItemType>
size_t Queue<ItemType>::Size() const
{
    return _list.Size();
}

/**
* Add item to end of the queue
* @return true if successful, false otherwise
*/
template <typename ItemType>
bool Queue<ItemType>::Enqueue(const ItemType& item)
{
    if(_list.Insert(_list.Size(), item))
    {
        return true;
    }
    return false;
}

/**
* Removes item from the front of the queue
* Caller should make sure queue is not empty
* @return item
*/
template <typename ItemType>
ItemType Queue<ItemType>::Dequeue()
{
    ItemType item;
    _list.Remove(0, item);
    return item;
}

#endif //QUEUE_H

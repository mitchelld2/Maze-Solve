//
// Interface Definition for the template version of the Set Class
// Author: Max Benson
// Date: 10/22/2021
//

#ifndef SET_H
#define SET_H

#include "VariableArrayList.h"

template <typename ElementType>
class Set {
public:
    bool Add(const ElementType& element);
    bool Contains(const ElementType& element);
    const ElementType Get(size_t ord) const;
    size_t Size() const;

    friend ostream& operator<<(ostream& os, const Set& set) {
        os << '{';
        for (size_t i = 0; i < set.Size(); i ++ ) {
            if (i > 0) {
                os << ", ";
            }
            os << set.Get(i);
        }
        os << '}';
    }

private:
    VariableArrayList<ElementType> _list;
};

/**
* Adds "element" to set if it not already present
* @return true operation succeeded, false if not
*/
template <typename ElementType>
bool Set<ElementType>::Add(const ElementType& element)
{
    if(_list.Find(element) == -1)
    {
        if (_list.Insert(_list.Size(), element))
        {
            return true;
        }
    }
    return true;
}

/**
* Checks whether element is part of the set
* @return true if set contains element, false if not
*/
template <typename ElementType>
bool Set<ElementType>::Contains(const ElementType& element)
{
    if(_list.Find(element) != -1)
    {
        return true;
    }
    return false;
}

/**
* Returns element at position pos in set
* @return element
*/
template <typename ElementType>
const ElementType Set<ElementType>::Get(size_t ord) const
{
    ElementType element;
    _list.Get(ord, element);
    return element;
}

/**
* Returns number of elements in set
* @return number of elements
*/
template <typename ElementType>
size_t Set<ElementType>::Size() const
{
    return _list.Size();
}



#endif //SET_H

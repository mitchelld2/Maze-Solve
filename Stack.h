//
// Interface Definition for the template version of the Stack Class
// Author: Max Benson
// Date: 08/15/2021
//

#ifndef STACK_H
#define STACK_H

#include "VariableArrayList.h"

template <typename ValueType>
class Stack {
public:
    bool IsEmpty() const;
    size_t Size() const;

    bool Push(const ValueType& value);
    ValueType Peek();
    ValueType Pop();

    friend ostream& operator<<(ostream& os, const Stack& stack) {
        os << stack._list;
    }

private:
    VariableArrayList<ValueType> _list;
};

/**
* Returns whether stack is empty
* @return true if stack empty, false otherwise.
*/
template <typename ValueType>
bool Stack<ValueType>::IsEmpty() const
{
    if(_list.Size() == 0)
    {
        return true;
    }
    return false;
}

/**
* Returns number of values on stack
* @return number of values
*/
template <typename ValueType>
size_t Stack<ValueType>::Size() const
{
    return _list.Size();
}

/**
* Puts the parameter "value" on top of the stack
* @param value
* @return true if successful, false otherwise
*/
template <typename ValueType>
bool Stack<ValueType>::Push(const ValueType& value)
{
    if(_list.Insert(_list.Size(), value))
    {
        return true;
    }
    return false;
}

/**
* Removes the top value on the stack and returns it
* Caller should make sure the stack is not empty.
* @return top value of stack
*/
template <typename ValueType>
ValueType Stack<ValueType>::Pop()
{
    if(_list.Size() > 0)
    {
        ValueType top;
        _list.Remove(_list.Size()-1, top);
        return top;
    }
}

/**
* Returns value stored at the top of the stack
* Caller should make sure the stack is not empty.
* @return stack's top value.
*/
template <typename ValueType>
ValueType Stack<ValueType>::Peek()
{
    if(_list.Size() > 0)
    {
        ValueType top;
        _list.Get(_list.Size()-1, top);
        return top;
    }
}

#endif //STACK_H

#include "../lib/stackint.h"
#include <cstdlib>
#include <stdexcept>

StackInt::StackInt()
{
}

StackInt::~StackInt()
{
}
    
/**
 * Returns true if the stack is empty, false otherwise
 */
bool StackInt::empty() const
{
    return list.size() == 0;
}

/**
 * Pushes a new value, val, onto the top of the stack
 */
void StackInt::push(const int& val)
{
    list.insert(list.size(), val);
}

/**
 * Returns the top value on the stack
 */
int const & StackInt::top() const
{
    return list.get(list.size() - 1);
}

/**
 * Removes the top element on the stack
 */
void StackInt::pop()
{
    list.remove(list.size() - 1);
}
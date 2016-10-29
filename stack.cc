/******************************************************************************
 * stack.cc                                                                   *
 * Skeleton by Alistair Campbell                                              *
 * Completed by: Mitchel Herman and Tom Parker                                                    *
 *                                                                            *
 * February 5, 2016                                                           *
 *                                                                            *
 *****************************************************************************/

#include "stack.h"

stack::stack()
{
    _init();
}

stack::~stack()
{
    _destroy(); // remove all nodes
}

stack::stack(const stack & other)
{
    _init();      // initialize.
    _copy(other); // copy other stack
}

stack & stack::operator=(const stack & rhs)
{
    if (this != &rhs) { // avoid assign to yourself
        _destroy();     // get rid of any data we already have.
        _copy(rhs);     // copy right hand side.
    }
    return *this;       // allows chained assignments
}

// Private methods
void stack::_copy(const stack & other)
{
    stack temp; // temporary storage
    // copy all data from other to temp.
    for (node *p = other._top; p != NULL; p = p->next)
        temp.push(p->data);
    // now temp is the reverse of other;
    // copy all data to this stack.
    for (node *p = temp._top; p != NULL; p = p->next)
        push(p->data);
}

void stack::_init()
{
    _size = 0;
    _top = NULL;
}

void stack::_destroy()
{
    delete _top;
}

// Public methods

void stack::push(const element & item)
{
    _size++; //Increase the size of the stack
    node * baby;
    baby = new node;  //Create new node
    baby->data = item;//data = to item
    baby-> next = _top; //and connect it to the stack at the top
    _top = baby;
    
}

void stack::pop()
{
    node *r;
    r = _top; //set temp pointer to top of stack
    _top = (*r).next; //advance the top to the the next one in the stack
    delete r; //delete the old top
    _size--;  //decrease the size of the stack
}

stack::element stack::top() const
{
    return _top->data; // returns the data of the top stack
}

bool stack::empty() const
{
    return _size == 0; //true if empty
}

size_t stack::size() const
{
    return _size; // returns size of the stack
}

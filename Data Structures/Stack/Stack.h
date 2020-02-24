#ifndef STACK_H
#define STACK_H

// Stack.h  -- a stack implemented as an adapter (of vector or list or ...)

//#include "../lab5/List.h"
#include <memory>
#include <list>

using namespace std;

//Use the following line for STL containers.
template <class T, template <class S, class = allocator<S> > class Container = list>
//template <class T, template <class S> class Container = List>
class Stack
{
public:
   //We don't need a constructor or destructor because the Container has/should have one
   //Stack(): container() { }
   //~Stack() { ~container(); }
   bool empty() const;
   unsigned int size() const;
   void push(const T & x);
   void pop();
   T & top();

private:
   Container<T> container;
};

template <class T, template <class S, class = allocator<S> > class Container = list>
bool Stack<T>::empty() const
{
    return size == 0;
}

template <class T, template <class S, class = allocator<S> > class Container = list>
unsigned int Stack<T>::size() const
{
    return size;
}

template <class T, template <class S, class = allocator<S> > class Container = list>
void Stack<T>::push(const T & x)
{
    push_back(x);
}

template <class T, template <class S, class = allocator<S> > class Container = list>
void Stack<T>::pop()
{
    pop_back();
}

template <class T, template <class S, class = allocator<S> > class Container = list>
T& Stack<T>::top();
{
    return end();
}
#endif

//
//  Priority_queue.h
//  lab9 Priority_Queue
//
//  Created by Kyle Westphal on 11/20/17.
//  Copyright © 2017 KWproductions. All rights reserved.
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Priority_queue.h  -- a priority_queue implemented as a heap
// lc(i) = 2i + 1
// rc(i) = 2i + 2
// parent(i) = (i - 1) / 2

#include <vector>

using namespace std;

template <class T>
class Priority_queue {
public:
    Priority_queue() : c() { }
    Priority_queue(const Priority_queue & p): c(p.c) { }
    Priority_queue & operator=(const Priority_queue & p) { c = p.c; return *this; }
    // vector destructor is automatically called when an obj of type Priority_queue is destroyed
    
    bool empty() { return c.empty(); }
    unsigned int size() { return c.size(); }
    void push(const T & x);
    void pop();
    T & top() { return c.front(); }
private:
    vector<T> c;
};

// your code goes here ...

template <class T>
void Priority_queue<T>::push(const T &x)
{
    c.push_back(x);
    // compare with parent. if greater that parent; swap. repeat
    // Percolate
    unsigned i = c.size() - 1;
    unsigned parent = (i - 1) / 2;
    while (i > 0 && c[i] > c[parent]) {
        swap(c[i], c[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

template <class T>
void Priority_queue<T>::pop()
{
    // set last leaf to root. (compare lc and rc. swap root with larger child) repeat
    if (empty()) return;
    c[0] = c.back();
    c.pop_back();
    unsigned i = 0;
    unsigned lc = 1;
    unsigned rc = 2;
    while (lc < c.size()) {
        unsigned largest = lc;
        if (rc < c.size() && c[lc] < c[rc]) largest = rc;
        // More code here...
        if (c[i] < c[largest]) swap(c[i], c[largest]);
        else return;
        i = largest;
        lc = 2*i + 1;
        rc = 2*i + 2;
    }
}

#endif









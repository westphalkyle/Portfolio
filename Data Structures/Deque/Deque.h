#ifndef DEQUE_H
#define DEQUE_H

// Deque.h - an implementation of double-ended queue

#include <vector>

using namespace std;

template <class T> class DequeIterator;

template <class T>
class Deque {
public:
	typedef DequeIterator<T> iterator;
	
	Deque(): vecOne(), vecTwo() { }
	Deque(const unsigned int size, const T& initial): vecOne(size/2, initial), vecTwo(size-(size/2), initial) { }
	Deque(const Deque<T> & d): vecOne(d.vecOne), vecTwo(d.vecTwo) { }
        ~Deque() { } // destructors for vecOne and vecTwo are automatically called
                     // never call a destructor explicitly
    Deque & operator=(const Deque<T> & d);
    T & operator[](unsigned int);
    T & front();
    T & back();
	bool empty();
	iterator begin();
	iterator end();
	void erase(const iterator &);
	void erase(const iterator &, const iterator &);
	void insert(const iterator &, const T &);
	int size();
	void push_front(const T & value);
	void push_back(const T & value);
	void pop_front();
	void pop_back();
protected:
	vector<T> vecOne;
	vector<T> vecTwo;
};

template <class T>
Deque<T> & Deque<T>::operator=(const Deque<T> & d)
{
    Deque<T> temp = new Deque<T>();
    temp -> vecOne = d.vecOne;
    temp -> vecTwo = d.vecTwo;
    delete *this;
    *this = temp;
}

template <class T>
T & Deque<T>::operator[](unsigned int index)
{
    int n = vecOne.size();
    if (index < n) return vecOne[(n-1) - index];
    else return vecTwo[index - n];
}

template <class T>
T & Deque<T>::front()
{
    if (vecOne.empty()) return vecTwo.front();
    else return vecOne.back();
}

template <class T>
T & Deque<T>::back()
{
    return vecTwo.back();
}

template <class T>
bool Deque<T>::empty()
{
    return (vecOne.empty() && vecTwo.empty());
}

template <class T>
typename iterator Deque<T>::begin()
{
    if (vecOne.empty()) return iterator(vecTwo.front();
    else return iterator(vecOne.back());
}

template <class T>
DequeIterator::iterator Deque::end()
{
    return iterator(vecTwo.back());
}

template <class T>
void Deque<T>::erase(const iterator & i)
{
    int index = i.index;
    int n = vecOne.size();
    if (i < i) vecOne.erase(((n-1) - index) + vecOne.begin());
    else vecTwo.erase((index - n) + vecTwo.begin());
}

template <class T>
void Deque<T>::erase(const iterator & i, const iterator & j)
{
    int n = vecOne.size();
    if (i < n && j < n) vecOne.erase(j-1), i); // All in vecOne
    if (i > n && j > n) vecTwo.erase(i, j);    // All in vecTwo
    else {                                     // Mixed
        erase(vecOne.begin(), i);
        erase(vecTwo.begin(), j);
    }
}

template <class T>
void Deque<T>::insert(const iterator &i, const T & v)
{
    int n = vecOne.size();
    if (i < n) vecOne.insert(i, v);
    else vecTwo.insert(i, v);
}

template <class T>
int Deque<T>::size()
{
    return vecOne.size() + vecTwo.size();
}

template <class T>
void Deque<T>::push_front(const T & value)
{
    vecOne.push_back(value);
}

template <class T>
void Deque::push_back(const T & value)
{
    vecTwo.push_back(value);
}

template <class T>
void Deque<T>::pop_front()
{
    if (vecOne.empty()) vecTwo.pop_front();
    else vecOne.pop_back();
}

template <class T>
void Deque<T>::pop_back()
{
    vecTwo.pop_back();
}

template <class T>
class DequeIterator {
	friend class Deque<T>;
	typedef DequeIterator<T> iterator;
public:
	DequeIterator(): theDeque(0), index(0) { }
	DequeIterator(Deque<T> * d, int i): theDeque(d), index(i) { }
	DequeIterator(const iterator & d): theDeque(d.theDeque), index(d.index) { }

	T & operator*();
	iterator & operator++();
	iterator operator++(int);
	iterator & operator--();
	iterator operator--(int);
	bool operator==(const iterator & r);
	bool operator!=(const iterator & r);
	bool operator<(const iterator & r);
	T & operator[](unsigned int i);
	iterator operator=(const iterator & r);
	iterator operator+(int i);
	iterator operator-(int i);
protected:
	Deque<T> * theDeque;
	int index;
};

template <class T>
T & DequeIterator::operator*()
{
    return (*theDeque)[index];
}

template <class T>
iterator & DequeIterator::operator++()
{
    (*theDeque)[index++];
    return *this;
}

template <class T>
iterator DequeIterator::operator++(int)
{
    DequeIterator<T>::iterator temp = this;
    ++(*this);
    return temp;
}

template <class T>
iterator & DequeIterator::operator--()
{
   (*theDeque)[index--];
   return *this;
} 

template <class T>
iterator DequeIterator::operator--(int)
{
    DequeIterator<T>::iterator temp = this;
    --(*this);
    return temp;
}

template <class T>
bool DequeIterator::operator==(const iterator & r)
{
    return ((*theDeque) == r.(*theDeque) && value == r.value);
}

template <class T>
bool DequeIterator::operator!=(const iterator & r)
{
    return ((*theDeque) != r.(*theDeque) || value != r.value);
}

template <class T>
bool DequeIterator::operator<(const iterator & r)
{
    return value < r.value;
}

template <class T>
T & DequeIterator::operator[](unsigned int i)
{
    return (*theDeque)[index + i];
}

template <class T>
iterator DequeIterator::operator=(const iterator & r)
{
    DequeIterator::iterator temp = this;
    delete *this;
    temp = r;
    return temp;
}

template <class T>
iterator DequeIterator::operator+(int i)
{
    return iterator((*theDeque)[index + i]);
}

template <class T>
iterator DequeIterator::operator-(int i)
{
    return iterator((*theDeque)[index - i]);
}

#endif

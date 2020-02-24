#ifndef LIST_H
#define LIST_H

// List.h - a doubly-linked list

#include <algorithm>

using namespace std;

// forward declaration of classes defined in this header

template <class T> class Link;
template <class T> class List_iterator;

template <class T> 
class List
{
public:
   typedef List_iterator<T> iterator;

   List();
   List(const List<T> & l);
   ~List();

   bool empty() const;
   unsigned int size() const; 
   T & back() const;
   T & front() const;
   void push_front(const T & x);
   void push_back(const T & x);
   void pop_front();
   void pop_back();
   iterator begin() const;
   iterator end() const;
   void insert(iterator pos, const T & x); // insert x before pos
   void erase(iterator & pos);             // pos must be valid after erase() returns
   List<T> operator=(const List<T> & l);

protected:
   Link<T> * first_link;
   Link<T> * last_link;
   unsigned int my_size;
};

template <class T>
List<T>::List()
{
        first_link = 0;
        last_link = 0;
        my_size = 0;
}

template <class T>
List<T>::List(const List & l)
{
        first_link = 0;
        last_link = 0;
        my_size = 0;
        for (Link<T> * current = l.first_link; current != 0; current = current -> next_link)
                push_back(current -> value);
}

template <class T>
List<T>::~List()
{
    while (my_size != 0) pop_back();
}

template <class T>
bool List<T>::empty() const
{
    return (my_size <= 0);
}

template <class T>
unsigned int List<T>::size() const
{
    return my_size;
}

template <class T> 
T& List<T>::back() const
{
    return last_link ->value;
}

template <class T>
T& List<T>::front() const
{
    return first_link ->value;
}

template <class T>
void List<T>::push_front(const T & x)
{
    Link<T> *new_link = new Link<T>(x);
    if (new_link == 0) {
        cout << "Error";
        exit(33);
    }
    if (my_size == 0) {
        first_link = new_link;
        last_link = new_link;
        new_link -> next_link = NULL;
        new_link -> prev_link = NULL;
    }
    else {
        new_link -> next_link = first_link;
        first_link -> prev_link = new_link;
        first_link = new_link;
    }
    my_size++;
}

template <class T>
void List<T>::push_back(const T & x)
{
    Link<T> *new_link = new Link<T>(x);
    if (new_link == 0) {
        cout << "Error";
        exit(33);
    }
    if (my_size == 0) first_link = last_link = new_link;
    else {
        new_link -> prev_link = last_link;
        last_link -> next_link = new_link;
        last_link = new_link ;
    }
    my_size++;
}

template <class T>
void List<T>::pop_front()
{
    if (my_size == 1) {
        first_link = NULL;
        last_link = NULL;
        my_size = 0;
    }
    else {
        first_link = first_link -> next_link;
        delete first_link -> prev_link;
        first_link -> prev_link = NULL;
        my_size--;
    }
}

template <class T>
void List<T>::pop_back()
{
    if(my_size = 1) {
        last_link = NULL;
	first_link = NULL;
        my_size = 0;
    }
    else {
        last_link = last_link -> prev_link;
        delete last_link -> next_link;
        last_link -> next_link = NULL;
        my_size--;
    }
}
template <class T>
typename List<T>::iterator List<T>::begin() const
{
    return iterator(first_link);
}

template <class T>   
typename List<T>::iterator List<T>:: end() const
{
    return iterator(0);
}

template <class T>
void List<T>::insert(iterator pos, const T & x) // insert x before pos
{
    Link<T> *new_link = new Link<T>(x);
    new_link -> next_link = pos.current_link;
    if (pos.current_link == first_link) {
        new_link -> prev_link = NULL;
        pos.current_link -> prev_link = new_link;
        first_link = new_link;
    }
    else {
        new_link -> prev_link = pos.current_link -> prev_link;
        pos--;
        //pos--;
        pos.current_link -> next_link = new_link;
        pos++;
        //pos++;
    }
    my_size++;
    
}

template <class T>
void List<T>::erase(iterator & pos)            // pos must be valid after erase() returns
{
    Link<T>* n = pos.current_link -> next_link;;
    Link<T>* q = pos.current_link -> prev_link;
    n -> prev_link = q;
    q -> next_link = n;
    delete pos.current_link;
    if(pos.current_link > first_link)
        pos--;
    else {
        first_link = pos.current_link;
    }
    my_size--;
        
}

template <class T>
List<T> List<T>::operator=(const List<T> & l)
{
    cout << "Inside assignment op" << endl;
    List<T>* temp = new List<T>();
    for (List<T>::iterator it = l.begin(); it != l.end(); it++) {
        temp -> push_back(*it);
	cout << *it << endl;
    }
    while(l.my_size != 0)
        l.pop_back;
    return *temp;   
}

template <class T> 
class Link 
{
private:
   Link(const T & x): value(x), next_link(0), prev_link(0) {}
                
   T value;     
   Link<T> * next_link;
   Link<T> * prev_link;

   friend class List<T>;
   friend class List_iterator<T>;
};

template <class T>
class List_iterator
{
public:
   typedef List_iterator<T> iterator;

   List_iterator(Link<T> * source_link): current_link(source_link) { }
   List_iterator(): current_link(0) { }
   List_iterator(List_iterator<T> * source_iterator): current_link(source_iterator -> current_link) { }

   T & operator*();  // dereferencing operator
   iterator operator=(const iterator & rhs);
   bool operator==(const iterator & rhs) const;
   bool operator!=(const iterator & rhs) const;
   iterator & operator++();  // pre-increment, ex. ++it
   iterator operator++(int); // post-increment, ex. it++
   iterator & operator--();  // pre-decrement
   iterator operator--(int); // post-decrement

protected:
   Link<T> * current_link;

   friend class List<T>;
};

template <class T>
T & List_iterator<T>::operator*()
{
        return current_link -> value;
}

template <class T>
typename List_iterator<T>::iterator List_iterator<T>::operator=(const iterator &rhs)
{
    this->current_link = rhs.current_link;
    return *this;
}

template <class T>
bool List_iterator<T>::operator==(const iterator &rhs) const
{
    typename Link<T>::iterator temp_it = this;
    *temp_it = *rhs;
    return temp_it;
}

template <class T>
List_iterator<T> & List_iterator<T>::operator++() // pre-increment
{
    current_link = current_link -> next_link;
    return *this;
}

template <class T>
List_iterator<T> List_iterator<T>::operator++(int) // post-increment
{
    typename List_iterator<T>::iterator temp_it = this;
    ++(*this);
    return temp_it;
}

template <class T>
List_iterator<T>& List_iterator<T>::operator--() // pre-decrement
{
    current_link = current_link -> prev_link;
    return *this;
}

template <class T>
typename List_iterator<T>::iterator List_iterator<T>::operator--(int) // post-decrement
{
    typename List_iterator<T>::iterator temp_it = this;
    --(*this);
    return temp_it;
}


template <class T>
class reverse_iterator
{
public:
   typedef reverse_iterator<T> iterator;

   reverse_iterator(Link<T> * source_link): current_link(source_link) { }
   reverse_iterator(): current_link(0) { }
   reverse_iterator(reverse_iterator<T> * source_iterator): current_link(source_iterator -> current_link) { }

   T & operator*();  // dereferencing operator
   iterator operator=(const iterator & rhs);
   bool operator==(const iterator & rhs) const;
   bool operator!=(const iterator & rhs) const;
   iterator & operator++();  // pre-increment, ex. ++it
   iterator operator++(int); // post-increment, ex. it++
   iterator & operator--();  // pre-decrement
   iterator operator--(int); // post-decrement
   iterator operator[](unsigned int);
   iterator rbegin();
   iterator rend();
   void reverse();

protected:
   Link<T> * current_link;

   friend class List<T>;
};


template <class T>
T & reverse_iterator<T>::operator*()
{
        return current_link -> value;
}

template <class T>
typename reverse_iterator<T>::iterator reverse_iterator<T>::operator=(const iterator &rhs)
{
    this->current_link = rhs.current_link;
    return *this;
}

template <class T>
bool reverse_iterator<T>::operator==(const iterator &rhs) const
{
    typename Link<T>::iterator temp_it = this;
    *temp_it = *rhs;
    return temp_it;
}

template <class T>
reverse_iterator<T> & reverse_iterator<T>::operator++() // pre-increment
{
    current_link = current_link -> prev_link;
    return *this;
}

template <class T>
reverse_iterator<T> reverse_iterator<T>::operator++(int) // post-increment
{
    typename reverse_iterator<T>::iterator temp_it = this;
    ++(*this);
    return temp_it;
}

template <class T>
reverse_iterator<T>& reverse_iterator<T>::operator--() // pre-decrement
{
    current_link = current_link -> next_link;
    return *this;
}

template <class T>
typename reverse_iterator<T>::iterator reverse_iterator<T>::operator--(int) // post-decrement
{
    typename List_iterator<T>::iterator temp_it = this;
    --(*this);
    return temp_it;
}

template <class T>
reverse_iterator<T>::iterator reverse_iterator<T>::operator[](unsigned int index)
{
    iterator temp = begin();
    for (int i = 0; i < index; i++) {
        temp++;
    }
    return *temp;
}

template <class T>
reverse_iterator<T>::iterator reverse_iterator<T>::rbegin();
{
    return iterator(last_link);
}

template <class T>
reverse_iterator<T>::iterator reverse_iterator<T>::rend()
{
    return iterator(first_link);
}

template <class T>
reverse_iterator<T>::iterator reverse_iterator<T>::reverse();
{
    List_iterator i = begin();
    reverse_iterator j = begin();
    for(int i = 0; i < my_size / 2; i++) {
        swap(*i++, *j++);
    }
}
    
#endif

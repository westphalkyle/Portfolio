#ifndef SET_H
#define SET_H

// Set.h - an implementation of Set using Node and Set_iterator

#include <iostream>
using namespace std;

template <class T> class Set;
template <class T> class Set_iterator;

template <class T>
class Node {
public:
	Node(): value(0), parent(0), leftChild(0), rightChild(0) { }
	Node(const T & x, Node * p, Node * lc, Node * rc):
		value(x), parent(p), leftChild(lc), rightChild(rc) { }
        // here copy constructor and assignment op don't make too much sense!
        Node(const Node & n): 
                value(n.value), parent(0), leftChild(0), rightChild(0) { }
        Node & operator=(const Node & n) { value = n.value; return *this; }

	~Node() { delete leftChild; delete rightChild; } // this is very recursive, delete also calls the destructor of the object it is deleting

	void insert(Node<T> * newNode); // this is a helper func for Set::insert()
	Node * find(const T & x);
protected:
	T value;
	Node * parent;
	Node * leftChild;
	Node * rightChild;

friend class Set<T>;
friend class Set_iterator<T>;
};

// Your code for Node goes here ...
template <class T>
void Node<T>::insert(Node<T> * newNode) 
{
    if (newNode.value < value) {
        if (this -> leftChild == 0) {
            this -> leftChild = newNode;
            newNode -> parent = this;
        }
        else this -> leftChild.insert(newNode);
    }
    else {
        if (this -> rightChild == 0) {
            this -> rightchild = newNode;
            newNode -> parent = this;
        }
        else this -> rightChild.insert(newNode);
    }
}

template <class T>
Node<T>* Node<T>::find(const T &x)
{
    if (x == value) return this;
    if (x < value) {
        if (this ->leftChild == 0) return 0;
        else return this -> leftChild.find(x);
    }
    else if (x > value) {
        if (this ->rightChild = 0) return 0;
        else return this -> rightChild.find(x);
    }
    else cout << "Error";
}

template <class T>
class Set{
public:
	typedef Set_iterator<T> iterator;

	Set(): root(0), my_size(0) { }

	// the big three
	Set(const Set<T> & );
	~Set() { delete root; }
	Set operator=(const Set & );

	bool empty() const { return root == 0; }
	unsigned int size() const { return my_size; }
	iterator insert(const T & x); // return an iterator to x if it already exists, otherwise insert and return an iterator to x
	void erase(const iterator & it);
	void erase(const T & x);
	unsigned int count(const T & x) const; // returns 1 or 0 because this is a set, not a multi-set
	iterator find(const T & x) const;
	iterator begin() const; // for in-order traversal
	iterator end() const { return iterator(0); }
protected:
	Node<T> * root;
	unsigned int my_size;
	//Node<T> * remove(Node<T> *, const T &);
};

template <class T>
Set<T>::Set(const Set<T> & op)
{
      root = 0;
      for (iterator i = op.begin(); i != op.end(); ++i)
              insert(*i);
}

template <class T>
Set<T> Set<T>::operator=(const Set<T> & op)
{
      delete root;
      root = 0;
      for (iterator i = op.begin(); i != op.end(); ++i)
              insert(*i);
      return *this;
}

// More code for Set goes here ...

template <class T>
typename Set<T>::iterator Set<T>::insert(const T & x) 
{   
    Node<T> *newNode = new Node<T>(x, 0, 0, 0);
    /*
    if (x < this -> value) {
        if (this -> leftChild == 0) {
            Node<T> newNode = new Node<T>(x, 0, 0, 0);
            Node<T>::insert(newNode);
        }
        else this -> leftChild.insert(x);
    }
    else {
        if (this -> rightChild == 0) {
            Node<T> newNode = new Node<T>(x, 0, 0, 0);
            Node<T>::insert(newNode);
        }
        else this -> rightChild.insert(x);
    }
    */
    if (root == NULL) root = newNode;

    if (count(x) == 0) {
        root -> insert(newNode);
        return find(x);
    }
    else {
        return find(x);
    }


    my_size++;
}

template <class T>
void Set<T>::erase(const iterator & it)
{
    if (root != 0 && it != end()) {
        Node<T> * p = it.n;
        Node<T> * left = p ->leftChild;
        Node<T> * right = p -> rightChild;
        if (right != 0) {
            // left slide
            Node<T> * left_slide = right;
            while (left_slide -> leftChild)
                left_slide = left_slide -> leftChild;
            // connect the subtrees after left slide
            left_slide -> leftChild = left;
            if (left != 0)
                left -> parent = left_slide;
            // now connect right subtree to bypass p
            right -> parent = p -> parent;
            if (p -> parent)
                if (p -> parent -> leftChild == p)
                    p -> parent -> leftChild = right;
                else p -> parent -> rightChild = right;
            else // p was root
                root = right;
        } else {
            if (left == 0) {
                if (p -> parent)
                    if (p -> parent -> leftChild == p)
                        p -> parent -> leftChild = 0;
                    else p -> parent -> rightChild = 0;
                else // p was root
                    root = 0;
            } else {
                left -> parent = p -> parent;
                if (p -> parent)
                    if (p -> parent -> leftChild == p)
                        p -> parent -> leftChild = left;
                    else p -> parent -> rightChild = left;
                else // p was root
                    root = left;
            }
        }
        p -> leftChild = 0;
        p -> rightChild = 0;
        delete p;
        my_size--;
    }
}

template <class T>
void Set<T>::erase(const T & x)
{
    iterator it = find(x);
    erase(it);
}

template <class T>
unsigned int Set<T>::count(const T & x) const
{
    if (x == root -> value) return 1;
    if (x < root -> value) {
        if (root ->leftChild == NULL) return 0;
        else return this -> leftChild.count(x);
    }
    else if (x > this.value) {
        if (this ->rightChild = NULL) return 0;
        else return this -> rightChild.count(x);
    }
}

template <class T>
typename Set<T>::iterator Set<T>::find(const T & x) const
{
    if (root == 0) return iterator(0);
    return iterator(root -> find(x));
}

template <class T>
typename Set<T>::iterator Set<T>::begin() const
{
    if (root -> leftChild == NULL) return iterator(root);
    Node<T> * left_slide = root;
    while (left_slide -> leftChild)
        left_slide = left_slide -> leftChild;
    return iterator(left_slide);
}

template <class T>
class Set_iterator {
public:
	Set_iterator(): n(0) { }
	Set_iterator(Node<T> * newNode): n(newNode) { }

	bool operator==(Set_iterator it) const { return n == it.n; }
	bool operator!=(Set_iterator it) const { return n != it.n; }
	Set_iterator & operator++(); // inorder traversal, pre-increment
	Set_iterator operator++(int); // inorder traversal, post-increment
	T & operator*() { return n->value; }
	Set_iterator & operator=(Set_iterator<T> it) { n = it.n; return *this; }
protected:
	Node<T> * n;
friend class Set<T>;
};

// More code for Set_iterator goes here ...

template <class T>
Set_iterator<T> & Set_iterator<T>::operator++()
{
    if (n -> rightChild == NULL) return Set_iterator(n -> parent);
    else return Set_iterator(n -> rightChild);


}

template <class T>
Set_iterator<T> Set_iterator<T>::operator++(int) 
{
    Set_iterator<T> temp = *this;
    ++(*this);
    return temp;
}

#endif

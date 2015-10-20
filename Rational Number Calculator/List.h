#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 5
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

using namespace std;

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the first element in the list
  T & front() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the last element in the list
  T & back() const;

  //MODIFIES: this
  //EFFECTS:  inserts i into the front of the list
  void push_front(const T &datum);

  //MODIFIES: this
  //EFFECTS:  inserts i into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //default constructor and Big Three
    List();
    List(const List &l);
    ~List();
    List& operator=(const List &l);

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //MODIFIES: this
  //EFFECTS:  copies all nodes from l to this
  void copy_all(const List<T> &l);

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  void pop_all();

  Node *first;   // points to first Node in list, or 0 if list is empty
  Node *last;    // points to last Node in list, or 0 if list is empty

public:
  ////////////////////////////////////////
	class Iterator {
    //OVERVIEW: Iterator interface to List

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }
        
    Iterator():node_ptr(0) {}
        
    T& operator* () const{
        assert(node_ptr);
        return node_ptr->datum;
    }
    Iterator& operator++ (){
        assert(node_ptr);
        node_ptr = node_ptr->next;
        return *this;
    }
    bool operator!= (Iterator rhs) const{
        return node_ptr != rhs.node_ptr;
    }
    bool operator== (Iterator rhs) const{
        return node_ptr == rhs.node_ptr;
    }
        
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p):node_ptr(p) {}

  };//List::Iterator
    
  ////////////////////////////////////////
  // return an Iterator pointing to the first node
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator(not end()) associated with this list
  //MODIFIES: this, may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
      assert(i != end());
      Node* tmp = i.node_ptr;
      if(tmp == first){
          pop_front();
      }
      else if(tmp == last){
          pop_back();
      }
      else{
          tmp->next->prev = tmp->prev;
          tmp->prev->next = tmp->next;
          delete tmp;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
      Node *tmp = i.node_ptr;
      if(tmp == first){
          push_front(datum);
      }
      else if(tmp == NULL){
          push_back(datum);
      }
      else{
          Node *np = new Node;
          np->datum = datum;
          np->next = tmp;
          np->prev = tmp->prev;
          tmp->prev->next = np;
          tmp->prev = np;
      }
  }

};//List

////////////////////////////////////////////////////////////////////////////////
//list implementation
template <typename T>
bool List<T>::empty() const{
    return first == 0;
}

template <typename T>
int List<T>::size() const{
    if(first == last){
        if(first == 0)
            return 0;
        else
            return 1;
    }
    Node *runner = first;
    int cnt = 1;
    while(runner != last){
        cnt++;
        runner = runner->next;
    }
    return cnt;
}

template <typename T>
T & List<T>::front() const{
    assert(!empty());
    return first->datum;
}

template <typename T>
T & List<T>::back() const{
    assert(!empty());
    return last->datum;
}

template <typename T>
void List<T>::push_front(const T &datum){
    Node *np = new Node;
    np->datum = datum;
    np->next = first;
    np->prev = NULL;
    if(empty()){
        first = last = np;
    }
    else{
        first->prev = np;
        first = np;
    }
    return;
}

template <typename T>
void List<T>::push_back(const T &elt){
    Node *np = new Node;
    np->datum = elt;
    np->next = 0;
    np->prev = last;
    if(empty()){
        first = last = np;
    }
    else{
        assert(last);
        last->next = np;
        last = np;
    }
}

template <typename T>
void List<T>::pop_front(){
    assert(!empty());
    if(first == last){
        delete first;
        first = NULL;
        last = NULL;
    }
    else{
        Node *tmp = first;
        first = first->next;
        first->prev = 0;
        delete tmp;
    }
}

template <typename T>
void List<T>:: pop_back(){
    assert(!empty());
    if(first == last){
        delete first;
        first = NULL;
        last = NULL;
    }
    else{
        Node *tmp = last;
        last->prev->next = NULL;
        last = last->prev;
        delete tmp;
    }
}

template <typename T>
List<T>::List()
: first(0), last(0) {}

template <typename T>
void List<T>::copy_all(const List<T> &l){
    Node *np = l.first;
    while(np){
        push_back(np->datum);
        np = np->next;
    }
    return;
}

template <typename T>
void List<T>::pop_all() {
    while(!empty()){
        pop_front();
    }
    return;
}

template <typename T>
List<T>::~List() {
    pop_all();
}

template <typename T>
List<T>::List(const List &l)
: first(0), last(0) {
    copy_all(l);
}

template <typename T>
List<T>& List<T>::operator= (const List &l) {
    pop_all();
    copy_all(l);
    return *this;
}

#endif

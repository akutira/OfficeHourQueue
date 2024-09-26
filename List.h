#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() {
    return Listsize == 0;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return Listsize;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node* new_node = new Node;
    new_node->datum = datum;
    new_node->next = first;
    new_node->prev = nullptr;
    if (first != nullptr) {
      first->prev = new_node;
    }
    first = new_node;
    if (empty()){
      last = new_node;
    }
    Listsize++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node* new_node = new Node;
    new_node->datum = datum;
    new_node->next = nullptr;
    new_node->prev = last;
    if (last != nullptr) {
      last->next = new_node;
    }
    last = new_node;
    if (empty()){
      first = new_node;
    }
    Listsize++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node* old_node = first;
    if (last == old_node) {
      last = nullptr;
    }
    first = first->next;
    if (first != nullptr) {
      first->prev = nullptr;
    }
    delete old_node;
    Listsize--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node* old_node = last;
    if (first == old_node) {
      first = nullptr;
    }
    last = last->prev;
    if (last != nullptr) {
      last->next = nullptr;
    }
    delete old_node;
    Listsize--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
  
  List() : first(nullptr), last(nullptr), Listsize(0){
  }

  List(const List<T> &other) : first(nullptr), last(nullptr), Listsize(0){
    copy_all(other);
  }

   ~List() {
    clear();
  }

  List<T> & operator=(const List<T> &other){
    if (this == &other) {
      return *this;
    } 

    clear();
    copy_all(other);
    return *this;
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    assert(empty());
    for (Node *n  = other.first; n != nullptr; n = n->next){
      push_back(n->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int Listsize = 0;

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
    
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator() : node_ptr(nullptr) {}

    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    Iterator copy = i;

    if (i.node_ptr == first){
      pop_front();
    } else if (i.node_ptr == last){
      pop_back();
    } else {
      Iterator prev = i;
      --prev;
      Iterator next = i;
      ++next;
      prev.node_ptr->next = next.node_ptr;
      next.node_ptr->prev = prev.node_ptr;

      delete copy.node_ptr;
      Listsize--;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
void insert(Iterator i, const T &datum) {
    if (i.node_ptr == first) {
      push_front(datum);
    } else if (i.node_ptr == nullptr) {
      push_back(datum);
    } else {
      Node* nnode = new Node;
      nnode->datum = datum;
      Iterator next = i;
      Iterator prev = --i;
      nnode->prev = prev.node_ptr;
      nnode->next = next.node_ptr;
      prev.node_ptr->next = nnode;
      next.node_ptr->prev = nnode;
      Listsize++;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.

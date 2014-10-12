// list.h
// Alistair Campbell
// Fall 2009
// Spring 2011
// Fall 2011
// Spring 2012

/*******************************

Assignment:  Implement the data structure described herein.

 *******************************/


#include <iostream>

class List 
{
 public:
  typedef char ElementType;
  List();
  // Create an empty doubly-linked list with front and rear sentinels,
  // current points to rear, and currentIndex = 0;

  ~List();
  // Delete all nodes (including the sentinels)

  List(const List & orig);
  // Make a deep copy of a list.
  // (currentIndex and current can be set arbitrarily in the copy)

  void add(const ElementType & item,size_t index);
  // Insert a new element at position index 
  // PRE:  List contains <v0, v1, ..., vindex, ...>
  //       0 <= index <= getSize()
  // POST: List contains <v0, v1, ..., item, vindex, ... >
  //       current points to new node containing item.
  // Guarantees constant time access to either end or vicinity of
  // currentIndex.  

  void removeAt(size_t index);
  // Remove an element from the list.
  // Pre: 0 <= index < getSize()
  //      List contains <v0, v1, ..., vindex, v(index+1), ... >
  // Post: List contains <v0, v1, ..., v(index+1), ... >
  //       current points to v(index+1) (or the rear sentinel)
  // Guarantees constant time access to either end or vicinity of
  // currentIndex.  

  void remove(const ElementType & item);
  // Let i be the smallest integer where get(i)==item. 
  // Post: same as for removeAt(i)
  // If no such i exists, no change to the list.

  size_t find(const ElementType & item) const;
  // return smallest integer where get(i)==item,
  // or getSize() if no such integer

  ElementType get(size_t index) const;
  // return the element at position i.
  // Guarantees constant time access to either end or vicinity of
  // currentIndex.  

  size_t getSize() const;
  // return the number of elements of the list
  // runs in constant time
  
  void output(std::ostream & ostr) const;
  // output the list to ostr using format
  // <v0, v1, v2, ..., vn-1>

 private:
  struct Node {
    Node *prev;
    ElementType data;
    Node *next;
    Node();
    Node(Node *p,Node *n);  // create node with given prev and next pointers
    Node(Node *p,const ElementType & d,Node *n);  // create a node with all 
                                                  // three data fields
  };

  void _setCurrentIndex(size_t index) const;  
  // PRE: 0 <= index <= getSize()
  // POST: (1) current points to the node holding the element at position 
  //       index, or to the rear sentinel.
  //       (2) currentIndex is index
  // This is accomplished as quickly as possible, starting from front, rear,
  // or current, whichever is closest to index.
  
  // data fields:
  size_t size; // number of data items
  mutable size_t currentIndex;  // corresponds to current.  
                        // 0 <= currentIndex <= getSize()
  Node *front;  // points to front sentinel
  Node *rear;   // points to rear sentinel
  mutable Node *current;  // points to a node in the list beyond the 
                          // front sentinel
    
};

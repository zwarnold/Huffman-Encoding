//list.cc
//Zach Arnold
//2/22/2012

#include "list.h"
#include<cassert>
#include<cmath>

using namespace std;

List::List()
{
  size = 0;
  currentIndex = 0;
  front = new Node(); //set front
  front->next = current = rear = new Node(front, NULL); //est rear
  rear->prev = front; //connect sents
}

List::~List()
{
  current = front->next;
  size_t count = size;

  //loop through the list
  for (size_t i = 0; i < count; i++){
    current->prev->next = current->next;
    current->next->prev = current->prev;
    Node *p = current;
    current = current->next;
    delete p;
  }

  //handle sentinels
  delete front;
  front = NULL;
  delete rear;
  rear = NULL;
  size = 0;
      
}

List::List(const List &orig)
{
  size = 0;
  currentIndex = 0;
  front = new Node(); //est front
  front->next = current = rear = new Node(front, NULL);//est rear
  rear->prev = front; //connect sents

  if (orig.size == 0) //if empty copy return
    return;

  //copy elements
  for (size_t i = 0; i < orig.size; i++){
    add(orig.get(currentIndex), currentIndex);
    currentIndex++;
  }    
}

List::Node::Node()
{
  //initialize pointers to null
  next = NULL;
  prev = NULL;    
}

List::Node::Node(Node *p,Node *n)
{
  //initialize pointers to given parameters
  next = n;
  prev = p;
}

List::Node::Node(Node *p,const ElementType & d,Node *n)
{
  //initialize pointers to give parameters
  next = n;
  prev = p;

  //initialize data
  data = d;
}

void absVal(int &num)
{
  //if neg, then pos
  if (num < 0)
    num = (num * (-1));
}

void findLowest(int &fromEnd,  int &fromBeg, 
		  int &fromLast, char &low)
{
  abs(fromEnd);
  int fL = fromLast; //temp value for comparison
  absVal(fL);
  int winner;
  
  if (fromBeg == 0){ //case for adding at beginning
    low = 'o';
    return;
  }
   
  else if (fromEnd == 0){ //case for adding at end
    low = 'n';
    return;
  }

  //find the most efficient way
  else if (fromEnd < fromBeg){
    low = 'e'; //case for end
    winner = fromEnd;
  }
  
  else{
    low = 'b'; //case for beginning
    winner = fromBeg;
    }
						
  if(winner > fL)
    low = 'l'; //case for last
}

void List::_setCurrentIndex(size_t index) const
{
  assert(index <= size);

  int fromEnd = size - index;
  int fromBeg = index;
  int fromLast = index - currentIndex;
  char low ;
  size_t num = size;
 
  findLowest(fromEnd, fromBeg, fromLast, low); //find the fastest rout

  if(low == 'b'){
    //loop from beginning
    current = front->next;

    for (size_t i = 0; i < index; i++)
      current = current->next;

    currentIndex = index;
  }

  else if (low == 'e'){
    //loop from end
    current = rear->prev;

    for (size_t i = (num - 1); i > index; i--)
      current = current->prev;

    currentIndex = index;
  }

  else if (low == 'l'){
    //loop from last index

    if (fromLast < 0){ //if distance is neg

      for (size_t i = currentIndex; i > index; i--)
	current = current->prev;

      currentIndex = index;
    }
    
    else{ //if distance is pos

      for (size_t i = currentIndex; i < index; i++)
	current = current->next;

      currentIndex = index;
    }
    
  }
  else if (low == 'o'){
    //case for front
    current = front->next;
    currentIndex = 0;
  }

  else if (low == 'n'){
    //case for rear
    current = rear;
    currentIndex = index;
  } 
}
 
void List::output(std::ostream & ostr) const
{
  Node *p = front->next;
  ostr << "<";
  if(size > 0){

    while(p->next != NULL){ //loop through the list
      ostr << p->data; // output data
      p = p->next; //increment

      if (p->next != NULL)
      ostr << ", ";
    }

  }

  ostr << ">";	      
}

size_t List::getSize() const
{
  return size;
}

List::ElementType List::get(size_t index) const
{
  assert(index <= size); //assert if index invalid

  _setCurrentIndex(index);
  return current->data;
}

size_t List::find(const ElementType & item) const
{
  _setCurrentIndex(0);

  //loop through list
  for (size_t i = 0; i < (size - 1); i++){
    
    if (current->data == item) // if match
      return currentIndex;

    current = current->next;
    currentIndex++;
  }
  return size; //in case of non existence
}

void List::removeAt(size_t index)
{
  assert(index <= (size - 1) & size != 0); //assert if empty or index invalid

  _setCurrentIndex(index);
  
  //reassign pointers
  Node* p = current->prev;
  p->next = current->next;
  p = current->next;
  p->prev = current->prev;

  delete current; //delete node
  current = p; //reassign current
  size--; //decrement
}

void List::add(const ElementType & item, size_t index)
{
  _setCurrentIndex(index);

  Node *p = new Node(current->prev, item, current); //create new node

  //handle pointers
  p->prev->next = p; 
  p->next->prev= p;

  current = p;
  size++; //increment
}

void List::remove(const ElementType & item)
{
  size_t index = find(item);

  if (index < size)
    removeAt(index);
}  



 

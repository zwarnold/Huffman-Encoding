#ifndef HNODE
#define HNODE
#include <cstdlib>

struct Hnode {
  unsigned char ch;
  size_t count;
  Hnode * left;
  Hnode * right;
  Hnode(unsigned char ch, size_t count): ch(ch), count(count), 
					 left(NULL), right(NULL) {}
  Hnode(Hnode * left, Hnode * right): ch(0), count(left->count + right->count),
				      left(left), right(right) {}
};
#endif
  

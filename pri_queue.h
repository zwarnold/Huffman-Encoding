#ifndef PRIQUEUE
#define PRIQUEUE

#include "hnode.h"

class PriQueue {
 public:
  PriQueue(int (*cmp)(void*,void*));
  ~PriQueue();
  size_t get_size();
  void add(void * item);
  void * remove();
  bool empty();

 private:
  int (*cmp) (void *,void *);
  size_t MAX;
  size_t size;
  void ** data;
  void _doubleMax();
  void _reheapUp(size_t curr);
  void _reheapDown(size_t curr);

};

#endif

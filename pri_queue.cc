# include <cstdlib>
# include "pri_queue.h"
#include <cassert>

PriQueue::PriQueue(int (*cmp)(void *, void *))
{
  this->cmp = cmp;
  MAX = 1024;
  size = 0;
  data = new void *[MAX];
  this->cmp = cmp;
}

PriQueue::~PriQueue()
{
  delete [] data;
}

size_t parent(size_t k)
{
  return (k-1) / 2;
}

size_t left(size_t k)
{
  return 2*k + 1;
}

size_t right(size_t k)
{
  return 2*k + 2;
}

void _swap(void ** data, size_t i, size_t j)
{
  void * temp = data[i];
  data[i] = data[j];
  data[j] = temp;
}

bool PriQueue::empty()
{
  return size == 0;
}

void PriQueue::add(void * item)
{
  data[size] = item;
  size++;
  _reheapUp(size-1);
}

void * PriQueue::remove()
{
  assert(size > 0);
  void * item = data[0];
  data[0] = data[size - 1];
  size--;
  _reheapDown(0);
  return item;
}

void PriQueue::_reheapUp(size_t curr)
{
  if (curr == 0) return;
  size_t p = parent(curr);
  // if data at curr comes before data at p, swap, and continue.
  if (cmp(data[curr],data[p]) < 0) {
    _swap(data, curr, p);
    _reheapUp(p);
  }
}
 
void PriQueue:: _reheapDown(size_t curr)
{
  size_t lefty = left(curr);
  size_t righty = right(curr);
  if (lefty >= size)  // and righty >= size, too!
    return;
  size_t sm = 
    righty >= size or 
    cmp(data[lefty],data[righty]) < 0 ? lefty : righty;
  if (cmp(data[curr],data[sm]) > 0) {
    _swap(data, curr, sm);
    _reheapDown(sm);
  }
}

void PriQueue::_doubleMax()
{
  void ** temp = new void * [MAX*2];
  MAX = MAX * 2;
  for(size_t i = 0; i < size; i++)
    temp[i] = data[i];
  delete [] data;
  data = temp;
}

size_t PriQueue::get_size()
{
  return size;
}

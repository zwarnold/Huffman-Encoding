// a program to test out the heap

//#include <ctime>
#include <iostream>
#include "heap.h"

using namespace std;

int intpcmp(void * _a, void *_b)
{
  int *a = (int*)_a;
  int *b = (int*)_b;
  return *a-*b;
}

int main(int argc, char **argv)
{
  Heap heap(intpcmp);
  srand(time(NULL));
  int n = atoi(argv[1]);
  for (int i=0;i<n;i++) {
    int v = rand() % n;
    cout << v << "  ";
    int * vp = new int(v);
    heap.add((void*)vp);
  }
  cout << endl;
  while (heap.get_size() > 0) {
    int * item = (int*) heap.remove();
    cout << *item << "  ";
    delete item;
  }
  cout << endl;
  

}

all: hencode hdecode

hdecode: hdecode.o pri_queue.o
	g++ -o hdecode hdecode.o pri_queue.o

hencode:hencode.o pri_queue.o
	g++ -o hencode hencode.o pri_queue.o

pri_queque.o: pri_queque.h pri_queue.cc
	g++ -c pri_queque.cc

hencode.o: hencode.cc hnode.h
	g++ -c hencode.cc

hdecode.o: hdecode.cc hnode.h
	g++ -c hdecode.cc


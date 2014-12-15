PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64
all: Project1
Project1: Project1.o function.o queue.o stack.o
	g++ Project1.o function.o queue.o stack.o -o Project1
Project1.o: Project1.cpp
	g++ -c Project1.cpp
function.o: function.cpp
	g++ -c function.cpp
queue.o: queue.cpp
	g++ -c queue.cpp
stack.o: stack.cpp
	g++ -c stack.cpp
clean:
	rm -rf *.o Project1

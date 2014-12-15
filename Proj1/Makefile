all: proj1
proj1: Project1.o function.o queue.o stack.o
	g++ Project1.o function.o queue.o stack.o -o proj1
Project1.o: Project1.cpp
	g++ -c Project1.cpp
function.o: function.cpp
	g++ -c function.cpp
queue.o: queue.cpp
	g++ -c queue.cpp
stack.o: stack.cpp
	g++ -c stack.cpp
clean:
	rm -rf *.o proj1

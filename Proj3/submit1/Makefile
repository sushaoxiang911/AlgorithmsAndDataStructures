all: logman
logman: proj3.o inputfile.o function.o
	g++ -O3 proj3.o inputfile.o function.o -o logman
proj3.o: proj3.cpp
	g++ -O3 -c proj3.cpp
inputfile.o: inputfile.cpp
	g++ -O3 -c inputfile.cpp
function.o: function.cpp
	g++ -O3 -c function.cpp
clean:
	rm -rf *.o logman

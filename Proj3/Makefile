all: proj3
proj3: proj3.o inputfile.o function.o
	g++ -O3 proj3.o inputfile.o function.o -o proj3
proj3.o: proj3.cpp
	g++ -O3 -c proj3.cpp
inputfile.o: inputfile.cpp
	g++ -O3 -c inputfile.cpp
function.o: function.cpp
	g++ -O3 -c function.cpp
clean:
	rm -rf *.o proj3

all: proj2
proj2: proj2.o document.o code.o datafunction.o radixsort.o duplicate.o
	g++ -O3 proj2.o document.o code.o datafunction.o radixsort.o duplicate.o -o proj2
proj2.o: proj2.cpp
	g++ -O3 -c proj2.cpp
document.o: document.cpp
	g++ -O3 -c document.cpp
code.o: code.cpp
	g++ -O3 -c code.cpp
datafunction.o: datafunction.cpp
	g++ -O3 -c datafunction.cpp
radixsort.o: radixsort.cpp
	g++ -O3 -c radixsort.cpp
duplicate.o: duplicate.cpp
	g++ -O3 -c duplicate.cpp
clean:
	rm -rf *.o proj2

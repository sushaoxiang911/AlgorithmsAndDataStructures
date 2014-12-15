PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64
all: proj4
proj4: proj4.o getMST.o FASTTSP.o OPTTSP.o OPTTSP2.o
	g++ -O3 proj4.o getMST.o FASTTSP.o OPTTSP.o OPTTSP2.o -o proj4
proj4.o: proj4.cpp
	g++ -O3 -c proj4.cpp
getMST.o: getMST.cpp
	g++ -O3 -c getMST.cpp
FASTTSP.o: FASTTSP.cpp
	g++ -O3 -c FASTTSP.cpp
OPTTSP.o: OPTTSP.cpp
	g++ -O3 -c OPTTSP.cpp
OPTTSP2.o: OPTTSP2.cpp
	g++ -O3 -c OPTTSP2.cpp
clean:
	rm -rf *.o proj4

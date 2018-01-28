all: matrix clean

matrix: main.o helpers.o cmatrix.o
	g++ main.o helpers.o cmatrix.o -o matrix

main.o: main.cpp
	g++ -c main.cpp

helpers.o: helpers.cpp
	g++ -c helpers.cpp

cmatrix.o: cmatrix.cpp
	g++ -c cmatrix.cpp

clean:
	rm -f *.o

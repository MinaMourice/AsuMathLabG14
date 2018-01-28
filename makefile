all: matrix clean

matrix: main.o solve.o decode.o cmatrix.o
	g++ main.o solve.o decode.o cmatrix.o -o matrix

main.o: main.cpp
	g++ -c main.cpp

solve.o: solve.cpp
	g++ -c solve.cpp
  
decode.o: decode.cpp
	g++ -c decode.cpp

cmatrix.o: cmatrix.cpp
	g++ -c cmatrix.cpp

clean:
	rm -f *.o

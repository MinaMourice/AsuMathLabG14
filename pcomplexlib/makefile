all: complex clean

complex: test.o pcomplexlib.o
	g++ -g test.o pcomplexlib.o -o pcomplexlib-0.1b

test.o: test.cpp
	g++ -g -c test.cpp

pcomplexlib.o: pcomplexlib.cpp
	g++ -g -c pcomplexlib.cpp

clean:
	rm -f *.o

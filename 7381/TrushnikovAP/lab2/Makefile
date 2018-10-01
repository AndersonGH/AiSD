all: lab2

lab2: Source/main.o Source/header.o Source/lisp.o
	g++ Source/main.o Source/header.o Source/lisp.o -o lab2

main.o: Source/main.cpp
	g++ -c main.cpp

header.o: Source/header.cpp
	g++ -c header.cpp

lisp.o: Source/lisp.cpp
	g++ -c lisp.cpp

clean:
	rm -f $(binaries) *.o

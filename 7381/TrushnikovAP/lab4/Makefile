OBJ = Source/main.o Source/header.o Source/stack.o

all: lab4

lab4: Source/main.o Source/header.o Source/stack.o
	g++ Source/main.o Source/header.o Source/stack.o -o lab4

main.o: Source/main.cpp
	g++ -c main.cpp

header.o: Source/header.cpp
	g++ -c header.cpp

stack.o: Source/stack.cpp
	g++ -c stack.cpp

clean:
	rm $(OBJ)

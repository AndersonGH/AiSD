OBJ = Source/main.o Source/header.o Source/tree.o lab5

all: lab5

lab5: Source/main.o Source/header.o Source/tree.o
	g++ Source/main.o Source/header.o Source/tree.o -o lab5

main.o: Source/main.cpp
	g++ -c main.cpp

header.o: Source/header.cpp
	g++ -c header.cpp

stack.o: Source/tree.cpp
	g++ -c tree.cpp

clean:
	rm $(OBJ)

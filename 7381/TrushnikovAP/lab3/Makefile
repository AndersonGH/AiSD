OBJ = Source/main.o Source/header.o Source/my_stack.o

all: lab3

lab3: Source/main.o Source/header.o Source/my_stack.o
	g++ Source/main.o Source/header.o Source/my_stack.o -o lab3

main.o: Source/main.cpp
	g++ -c main.cpp

header.o: Source/header.cpp
	g++ -c header.cpp

my_stack.o: Source/my_stack.cpp
	g++ -c my_stack.cpp

clean:
	rm $(OBJ)

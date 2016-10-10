Project1: main.o NFA.o
	g++ -g -std=c++11 -Wall main.o NFA.o -o Project1

main.o: main.cpp Node.h DoubleLinkedList.h Node.hpp DoubleLinkedList.hpp NFA.h NFA.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

NFA.o: NFA.h NFA.cpp Node.h Node.hpp DoubleLinkedList.h DoubleLinkedList.hpp
	g++ -g -std=c++11 -Wall -c NFA.cpp

clean:
	rm *.o main Project1 Project.exe
	clean done

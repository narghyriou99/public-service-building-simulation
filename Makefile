all:	ask3

ask3:	main.o  Visitor.o Building.o 
	gcc -o ask3 main.o  Visitor.o Building.o -lstdc++

main.o: main.cpp
	g++ -c main.cpp	

Visitor.o: Visitor.cpp
	g++ -c Visitor.cpp 

Building.o: Building.cpp
	g++ -c Building.cpp 

clean:
	rm -f *.o ask3

all: changedp changeslow

changedp: changedp.cpp
	g++ -std=c++0x changedp.cpp -o changedp

changeslow: changeslow.cpp
	g++ -std=c++0x changeslow.cpp -o changeslow

clean:
	rm *.o changedp changeslow 

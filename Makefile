all: changedp changeslow changegreedy

changedp: changedp.cpp
	g++ -std=c++0x changedp.cpp -o changedp

changeslow: changeslow.cpp
	g++ -std=c++0x changeslow.cpp -o changeslow

changegreedy: changegreedy.cpp
	g++ -std=c++0x changegreedy.cpp -o changegreedy

clean:
	rm *.o changedp changeslow changegreedy

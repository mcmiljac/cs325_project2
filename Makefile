all: changeslow changegreedy changedp

changeslow: changeslow.cpp
	g++ -std=c++0x changeslow.cpp -o changeslow

changegreedy: changegreedy.cpp
	g++ -std=c++0x changegreedy.cpp -o changegreedy

changedp: changedp.cpp
	g++ -std=c++0x changedp.cpp -o changedp

clean:
	rm *.o changeslow changegreedy changedp 

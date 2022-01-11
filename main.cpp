#include <iostream>
#include "Grafo.h"

using namespace std;

template <typename Element>
void printList(list<Element> in)
{
	for (typename list<Element>::iterator it=in.begin(); it != in.end(); it++)
    	cout << ' ' << *it;
    cout << endl;
}

int main(int argc, char const *argv[])
{
	Grafo<char> G;
	G.agregarVertice('a');
	G.agregarVertice('b');
	G.agregarVertice('c');
	G.agregarVertice('d');
	G.agregarArco('a','b',1);
	G.agregarArco('a','d',1);
	G.agregarArco('b','a',1);
	G.agregarArco('b','d',1);
	G.agregarArco('b','c',1);
	G.agregarArco('c','b',1);
	G.agregarArco('c','d',1);
	G.agregarArco('d','a',1);
	G.agregarArco('d','b',1);
	G.agregarArco('d','c',1);
	G.imprimir();

	list<char> L = G.BFS('a');

	printList(L);

	cout << "Cab";
	return 0;
}

// G.agregarVertice(1);
// 	G.agregarVertice(2);
// 	G.agregarVertice(3);
// 	G.agregarVertice(4);
// 	G.agregarArco(3,2,1.5);
// 	G.agregarArco(3,1,7.0);
// 	G.agregarArco(2,1,0.5);
// 	G.agregarArco(2,3,2.5);
// 	G.agregarArco(1,3,6.7);

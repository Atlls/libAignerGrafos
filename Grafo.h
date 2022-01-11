#ifndef GRAFO_H_
#define GRAFO_H_
// #include "NodosGrafo.h"
#include "NodoVer.h"
#include "NodoAdy.h"
#include <string>
#include <list>
#include <array>
#include <queue>

using namespace std;

/*
	Cosas por hacer...
		- prinft de Nodos
		- predecesores y sucesores
		- getPesoArco() 
		- destruir()
		- Mapeo
		- Recorrido BFS
		Recorrido DFS
	
*/

template <class Element>
class Grafo
{
	private:
		NodoVer<Element>* g;
		NodoVer<Element>* end;
		int nVertices;
		int nArcos;

		NodoVer<Element>* obtVertice(Element);
		NodoAdy<Element>* obtArco(Element,Element);

		int indiceDe(Element);
		Element verticeDe(int); // Retorna el Vertice de una posicion, si no existe, retorna el primer elemento

		Grafo<int> mapear();
	public:
		Grafo();

		float getPesoArco(Element,Element); // Retorna 0 si el arco no existe

		bool esVacio();
		bool existeVertice(Element);
		bool existeArco(Element,Element);
		// Agregar como de manera "push_back"
		void agregarVertice(Element); // O(1)
		void agregarArco(Element,Element,float); // O(n)
		void eliminarVertice(Element); // O(n), Eliminar tambien los arcos correspondientes
		void eliminarArco(Element,Element); // O(n + m)

		list<Element> sucesores(Element);
		list<Element> predecesores(Element);

		void destruir();

		list<Element> BFS(Element);
		
		void consultarVertices();
		void consultarArcos(Element);
		void imprimir();
};

template <class Element>
Grafo<Element>::Grafo()
{
	g = NULL;
	end = NULL;
	nVertices = 0;
	nArcos = 0;
}

template <class Element>
NodoVer<Element>* Grafo<Element>::obtVertice(Element v)
{
	NodoVer<Element>* p = g;
	bool encVertice = false;
	while (p != NULL and !encVertice)
	{ 
		if(p->getElm() == v)
			encVertice = true;
		else
			p = p->getProx();
	}

	return p;
}

template <class Element>
NodoAdy<Element>* Grafo<Element>::obtArco(Element v, Element w)
{
	NodoVer<Element>* p = obtVertice(v);
	NodoAdy<Element>* q = NULL;
	if(p != NULL)
		q = p->getListAdy();

	bool encArco = false;
	while (q != NULL and !encArco)
	{ 
		if(q->getInfo() == w)
			encArco = true;
		else
			q = q->getProx();
	}

	return q;	
}

template <class Element>
int Grafo<Element>::indiceDe(Element v)
{
	NodoVer<Element>* p = g;
	int i = 1;
	bool enc = false;
	while(p != NULL and !enc)
	{
		if(p->getElm() == v)
			enc = true;
		else
			i++;
		p = p->getProx();
	}

	return enc ? i : 0;
}

template <class Element>
Element Grafo<Element>::verticeDe(int pos)
{
	NodoVer<Element>* p = g;
	
	for (int i = 1; i < pos; i++) p = p->getProx();

	return p != NULL ? p->getElm() : g->getElm();
}

template <class Element>
float Grafo<Element>::getPesoArco(Element v, Element w) 
{ 
	NodoAdy<Element>* p = obtArco(v,w);
	return p == NULL ? 0 : p->getPeso();
}

/* Operaciones */

template <class Element>
bool Grafo<Element>::esVacio() { return nVertices == 0; }

template <class Element>
bool Grafo<Element>::existeVertice(Element v) { return obtVertice(v) != NULL; }

template <class Element>
bool Grafo<Element>::existeArco(Element v, Element w) { return obtArco(v,w) != NULL; }

template <class Element>
void Grafo<Element>::agregarVertice(Element e)
{
	NodoVer<Element>* nuevoVertice = new NodoVer<Element>(e);
	if(nVertices == 0)
		g = nuevoVertice;
	else
		end->setProx(nuevoVertice);
	end = nuevoVertice;
	nVertices++;
}

template <class Element>
void Grafo<Element>::agregarArco(Element v,Element w, float peso)
{
	NodoVer<Element>* vertice = obtVertice(v);
	if(vertice == NULL) return;

	NodoAdy<Element>* arcoAux = vertice->getEnd();
	NodoAdy<Element>* nuevoArco = new NodoAdy<Element>(w, peso);

	if(arcoAux != NULL)
		arcoAux->setProx(nuevoArco);
	else
		vertice->setListAdy(nuevoArco);

	vertice->setEnd(nuevoArco);
	vertice->setNArcos(vertice->getNArcos() + 1);
	nArcos++;
}

template <class Element>
void Grafo<Element>::eliminarVertice(Element v)
{
	// Buscar vertice a eliminar y su anterior

	NodoVer<Element>* elim = g;
	NodoVer<Element>* antElim = elim;
	bool encVertice = false;
	while (elim != NULL and !encVertice)
	{ 

		if(elim->getElm() == v)
		{
			encVertice = true;
		}
		else
		{
			antElim = elim;
			elim = elim->getProx();	
		}
	}

	if(elim == NULL) return;

	// Eliminar arcos...

	NodoAdy<Element>* arcElim  = elim->getListAdy();
	NodoAdy<Element>* aux = arcElim; // Se puede hacer con un solo puntero?

	while(arcElim != NULL) 
	{ 
		aux = aux->getProx();
		delete(arcElim);
		elim->setListAdy(aux);
		arcElim = aux;
	}

	// Eliminar...

	if(elim == antElim)
		g = elim->getProx();
	else
		antElim->setProx(elim->getProx());

	delete(elim); // What?! No Elimina?!

	// Acualizar indices...

	int index = antElim->getIndex();
	antElim = antElim->getProx();
	while(antElim != NULL)
	{
		index++;
		antElim->setIndex(index);
		antElim = antElim->getProx();
	}

	nVertices--;
}

template <class Element>
void Grafo<Element>::eliminarArco(Element v, Element w)
{
	NodoVer<Element>* p = obtVertice(v);

	if(p == NULL) return;

	NodoAdy<Element>* elim = p->getListAdy();
	NodoAdy<Element>* antElim = elim;

	bool encVertice = false;
	while (elim != NULL and !encVertice)
	{ 

		if(elim->getElm() == v)
		{
			encVertice = true;
		}
		else
		{
			antElim = elim;
			elim = elim->getProx();	
		}
	}

	if(!encVertice) return;

	if(elim == antElim)
		p->setListAdy(elim->getProx());
	else
		antElim->setProx(elim->getProx());

	p->setNArcos(p->getNArcos() - 1);
}

template <class Element>
list<Element> Grafo<Element>::sucesores(Element v)
{
	list<Element> out;
	NodoVer<Element>* p = obtVertice(v);
	NodoAdy<Element>* q = p->getListAdy();

	for (int i = 0; i < p->getNArcos(); i++)
	{
		out.push_back(q->getInfo());
		q = q->getProx();
	}

	return out;
}

template <class Element>
list<Element> Grafo<Element>::predecesores(Element v)
{
	list<Element> out;

	NodoVer<Element>* p = g;
	NodoAdy<Element>* q;
	bool enc;

	for (int i = 0; i < nVertices; i++)
	{
		enc = false;
		q = p->getListAdy();

		while(q != NULL && !enc)
		{
			if(q->getInfo() == v)
				enc = true;
			else
				q = q->getProx();
		}

		if(enc) out.push_back(p->getElm());

		p = p->getProx();
	}

	return out;
}

template <class Element>
void Grafo<Element>::destruir() { while(!esVacio()) eliminarVertice(g->getElm()); }

/*
	O(n**2+m)
	Tiene que consultar las posisiones de cada vertice, acuando como indice
*/
template <class Element>
Grafo<int> Grafo<Element>::mapear() // O(n**3+m)
{
	Grafo<int> out;
	NodoVer<Element>* vertice = g;
	NodoVer<Element>* srcVer;
	NodoAdy<Element>* arco;
	bool enc;
	int j;

	vertice = g;
	for (int i = 1; i <= nVertices; i++)
	{
		out.agregarVertice(i);
		arco = vertice->getListAdy();
		while(arco != NULL)
		{
			srcVer = g;
			enc = false;
			j = 1;
			while(srcVer != NULL and !enc)
			{
 				if(srcVer->getElm() == arco->getInfo())
				{
					out.agregarArco(i,j,1);
					enc = true;
				}
				else
				{
					j++;
				}
				srcVer = srcVer->getProx();
			}
			arco = arco->getProx();
		}
		vertice = vertice->getProx();
	}
	return out;	
}

template <class Element>
list<Element> Grafo<Element>::BFS(Element fuente)
{
	//	 Algoritmo de mapeo O(n2+m) 

	int mapFuente = indiceDe(fuente); // O(n)
	Grafo<int> mapa = mapear(); 	   // O(n2+m)

	// Algoritmo BFS O(n+m) 

	bool visit[nVertices];
	queue<int> C;
	list<int> recorr, sucesores;
	int i, v, w;

	// Inicialzar
	for (int i = 0; i < nVertices; i++) visit[i] = false;
	C.push(mapFuente);
	visit[mapFuente-1] = true;

	// Recorrer
	while(!C.empty())
	{
		v = C.front();
		C.pop();
		recorr.push_back(v);
		sucesores = mapa.sucesores(v);
		v--;
		while(!sucesores.empty())
		{
			w = sucesores.front() - 1;

			// Marcar
			if(!visit[w])
			{
				visit[w] = true;
				C.push(w+1);
			}
			sucesores.pop_front();
		}
	}

	// desmapear O(n2) 

	list<Element> out;
	int indice;
	for(i = 1; i <= nVertices; i++)
	{
		indice = recorr.front();
		out.push_back(verticeDe(indice));
		recorr.pop_front();
	}

	return out;

}

/* de Testeo */

template <class Element>
void Grafo<Element>::consultarVertices()
{
	NodoVer<Element>* ptr = g;

	for(int i = 0; i < nVertices; i++)
	{
		cout << ptr->getElm() << " ";
		ptr = ptr->getProx();
	}
}

template <class Element>
void Grafo<Element>::consultarArcos(Element v)
{
	NodoVer<Element>* ptr = obtVertice(v);

	if(ptr == NULL) return;

	NodoAdy<Element>* aux = ptr->getListAdy();

	while(aux != NULL)
	{
		cout << aux->getInfo() << " ";
		aux = aux->getProx();
	}
}

template <class Element>
void Grafo<Element>::imprimir()
{
	NodoVer<Element>* p = g;
	NodoAdy<Element>* q;

	for (int i = 0; i < nVertices; i++)
	{
		cout << p->getElm() << " - ";
		q = p->getListAdy();
		for (int j = 0; j < p->getNArcos(); j++)
		{
			cout << q->getInfo() << " - ";
			q = q->getProx();
		}
		cout << "NULL" << endl;
		cout << "|" << endl;
		p = p->getProx();
	}
	cout << "NULL" << endl;
}

#endif /* NodoVer_H_ */
#ifndef NODOVER_H_
#define NODOVER_H_
#include "NodoAdy.h"
#include <string>

using namespace std;

template <class Element>
class NodoVer
{
	private:
		int index; // Eliminar esto
		int nArcos;
		Element elm;
		NodoVer<Element>* prox;
		NodoAdy<Element>* end;
		NodoAdy<Element>* listAdy;
	public:
		NodoVer();
		NodoVer(Element);
		NodoVer(Element,NodoVer<Element>*,int);


		int 			   getIndex();
		Element 		   getElm();
		NodoVer<Element>*& getProx();
		int 			   getNArcos();
		NodoAdy<Element>*& getListAdy();
		NodoAdy<Element>*& getEnd();
		void 			   setProx(NodoVer<Element>*);
		void 			   setListAdy(NodoAdy<Element>*);
		void 			   setNArcos(int);
		void 			   setEnd(NodoAdy<Element>*);

};

template <class Element>
NodoVer<Element>::NodoVer()
{
	index = 0;
	nArcos = 0;
	prox = NULL;
	end = NULL;
	listAdy = NULL;
}

template <class Element>
NodoVer<Element>::NodoVer(Element e)
{
	index = 0;
	nArcos = 0;
	elm = e;
	prox = NULL;
	end = NULL;
	listAdy = NULL;
}

template <class Element>
NodoVer<Element>::NodoVer(Element e, NodoVer<Element>* _prox, int _index)
{
	index = _index;
	nArcos = 0;
	elm = e;
	prox = _prox;
	end = NULL;
	listAdy = NULL;
}

template <class Element>
int NodoVer<Element>::getIndex() { return index; }

template <class Element>
int NodoVer<Element>::getNArcos() { return nArcos; }

template <class Element>
Element NodoVer<Element>::getElm() { return elm; }

template <class Element>
NodoVer<Element>*& NodoVer<Element>::getProx() { return prox; }

template <class Element>
NodoAdy<Element>*& NodoVer<Element>::getEnd() { return end; }

template <class Element>
void NodoVer<Element>::setProx(NodoVer<Element>* _prox) { prox = _prox; }

template <class Element>
void NodoVer<Element>::setNArcos(int _nArcos) { nArcos = _nArcos; }

template <class Element>
void NodoVer<Element>::setListAdy(NodoAdy<Element>* _listAdy) { listAdy = _listAdy; }

template <class Element>
void NodoVer<Element>::setEnd(NodoAdy<Element>* _end) { end = _end; }

template <class Element>
NodoAdy<Element>*& NodoVer<Element>::getListAdy() { return listAdy; }

#endif /* NodoVer_H_ */
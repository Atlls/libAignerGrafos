#ifndef NODOADY_H_
#define NODOADY_H_
#include "NodoVer.h"
#include <string>

using namespace std;

template <class Element>
class NodoAdy
{
	private:
		float peso;
		Element info; // NodoVer<Element>* info;
		NodoAdy<Element>* prox;
	public:
		NodoAdy();
		NodoAdy(Element,float);
		NodoAdy(Element,float,NodoAdy<Element>*);

		float 			   getPeso();
		Element 		   getInfo();
		NodoAdy<Element>*& getProx();
		void 			   setProx(NodoAdy<Element>*);
};

template <class Element>
NodoAdy<Element>::NodoAdy()
{
	peso = 0;
	prox = NULL;
}

template <class Element>
NodoAdy<Element>::NodoAdy(Element _info, float _peso)
{
	info = _info;
	peso = _peso;
	prox = NULL;
}

template <class Element>
NodoAdy<Element>::NodoAdy(Element _info, float _peso, NodoAdy<Element>* _prox)
{
	info = _info;
	peso = _peso;
	prox = _prox;
}


template <class Element>
float NodoAdy<Element>::getPeso() { return peso; }

template <class Element>
NodoAdy<Element>*& NodoAdy<Element>::getProx() { return prox; }

template <class Element>
void NodoAdy<Element>::setProx(NodoAdy<Element>* newProx) { prox = newProx; }

template <class Element>
Element NodoAdy<Element>::getInfo() { return info; }

#endif /* NodoAdy_H_ */
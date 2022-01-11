#ifndef NODOSGRAFO_H_
#define NODOSGRAFO_H_
#include <string>

using namespace std;

template <class Element>
class NodoVer
{
	private:
		Element elm;
		NodoVer<Element>* prox;
		NodoAdy<Element>* listAdy;
	public:
		NodoVer();
		NodoVer(Element);
		NodoVer(Element,NodoVer<Element>*);

		Element 		   getElm();
		NodoVer<Element>*& getProx();

};

template <class Element>
NodoVer<Element>::NodoVer()
{
	prox = NULL;
	listAdy = NULL;
}

template <class Element>
NodoVer<Element>::NodoVer(Element e)
{
	elm = e;
	prox = NULL;
	listAdy = NULL;
}

template <class Element>
NodoVer<Element>::NodoVer(Element e, NodoVer<Element>* _prox)
{
	elm = e;
	prox = _prox;
	listAdy = NULL;
}

template <class Element>
Element NodoVer<Element>::getElm() { return elm; }

template <class Element>
NodoVer<Element>*& NodoVer<Element>::getProx() { return prox; }

template <class Element>
class NodoAdy
{
	private:
		float peso;
		NodoVer<Element>* info;
		NodoAdy<Element>* prox;
};

#endif /* NodoAdy_H_ */
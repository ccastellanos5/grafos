#ifndef COLA_H
#define COLA_H
#include "Lista.h"
#include <iostream>

using namespace std;

template <class T>
class Cola : protected Lista<T>
{
	private:
		Nodo<T> *ult;
	public:
		Cola();
		Cola(Cola<T> &orig);
		void copiar(Cola<T> &orig);
		int obtLong();
		bool esVacia();
		void encolar(T elemento);
		void desencolar();
		T frente();
		T ultimo();
		void imprimir();
};

template<class T>
Cola<T>::Cola()
{
  this->ult = NULL;
}

template<class T>
Cola<T>::Cola(Cola<T> &orig)
{
	this->copiar(orig);
}

template<class T>
void Cola<T>::copiar(Cola<T> &orig)
{
	Nodo<T> *act;
	int i;

	Lista<T>::copiar(orig);

	act = this->primero;
	for (i = 0; i < this->obtLong() - 1; i++)
	{
		act = act->obtProx();
	}
	this->ult = act;
}

template <class T>
int Cola<T>::obtLong()
{
	return Lista<T>::obtLong();
}

template <class T>
bool Cola<T>::esVacia()
{
	return Lista<T>::esVacia();
}

template <class T>
void Cola<T>::encolar(T elemento)
{
	Nodo<T> *aux;

	if(this->obtLong()==0)
	{
		Lista<T>::insertar(elemento, 1);
		this->ult = this->primero;
	}
	else
	{
		aux = new Nodo<T>;
		aux->modInfo(elemento);
		aux->modProx(NULL);
		(this->ult)->modProx(aux);
		this->ult = aux;
		this->longitud += 1;
	}

}

template <class T>
void Cola<T>::desencolar()
{
	Lista<T>::eliminar(1);

	if(this->longitud == 0)
		this->ult = NULL;
}

template <class T>
T Cola<T>::frente()
{
	return this->consultar(1);
}
template <class T>
T Cola<T>::ultimo()
{
	return (this->ult)->obtInfo();
}

template <class T>
void Cola<T>::imprimir()
{
	Lista<T>::imprimir();
}

#endif

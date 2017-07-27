#ifndef NODOA_H
#define NODOA_H
#include <iostream>


template<class vertice>
class NodoV;

template<class T>
class NodoA{
  private:
    NodoA<T> *prox;
    NodoV<T> *vertice;
    float costo;
  public:
    NodoA();
    NodoA(NodoA<T> *p, NodoV<T> *v, float nuevoCosto);
    NodoA<T>* obtProx();
    NodoV<T>* obtVertice();
    float obtCosto();
    void modProx(NodoA<T> *nuevo);
    void modVertice(NodoV<T> *nuevo);
    void modCosto(float nuevo);
};

template<class T>
NodoA<T>::NodoA()
{
  this->prox = NULL;
  this->vertice = NULL;
  this->costo = 0;
}

template<class T>
NodoA<T>::NodoA(NodoA<T> *p, NodoV<T> *v, float nuevoCosto)
{
  this->prox = p;
  this->vertice = v;
  this->costo = nuevoCosto;
}

template<class T>
NodoA<T>* NodoA<T>::obtProx()
{
  return this->prox;
}

template<class T>
NodoV<T>* NodoA<T>::obtVertice()
{
  return this->vertice;
}

template<class T>
float NodoA<T>::obtCosto()
{
  return this->costo;
}

template<class T>
void NodoA<T>::modProx(NodoA<T> *nuevo)
{
  this->prox = nuevo;
}

template<class T>
void NodoA<T>::modVertice(NodoV<T> *nuevo)
{
  this->vertice = nuevo;
}

template<class T>
void NodoA<T>::modCosto(float nuevo)
{
  this->costo = nuevo;
}
#endif

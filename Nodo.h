#ifndef NODO_H
#define NODO_H
#include <iostream>

template<class T>
class Nodo
{
  private:
    Nodo<T> *prox;
    T info;
  public:
    Nodo();
    Nodo(Nodo<T>* a, T b);
    Nodo<T>* obtProx();
    T obtInfo();
    void modProx(Nodo<T>* a);
    void modInfo(T b);
};

template<class T>
Nodo<T>::Nodo()
{
  this->prox = NULL;
}

template<class T>
Nodo<T>::Nodo(Nodo<T>* a, T b)
{
  this->prox = a;
  this->info = b;
}

template<class T>
Nodo<T>* Nodo<T>::obtProx()
{
  return this->prox;
}

template<class T>
T Nodo<T>::obtInfo()
{
  return this->info;
}

template<class T>
void Nodo<T>::modProx(Nodo<T>* a)
{
  this->prox = a;
}

template<class T>
void Nodo<T>::modInfo(T b)
{
  this->info = b;
}

#endif

#ifndef NODOV_H
#define NODOV_H
#include <iostream>

template<class T>
class NodoA;

template<class vertice>
class NodoV
{
  private:
    vertice info;
    NodoV<vertice> *prox;
    NodoA<vertice> *primero;
    bool visitado;
  public:
    NodoV();
    NodoV(NodoV<vertice> *p, NodoA<vertice> *pri, vertice i, bool mark);
    vertice obtInfo();
    NodoV<vertice>* obtProx();
    NodoA<vertice>* obtPrimero();
    bool obtVisitado();
    void modInfo(vertice nuevo);
    void modProx(NodoV<vertice> *nuevo);
    void modPrimero(NodoA<vertice> *nuevo);
    void modVisitado(bool nuevo);
};

template<class vertice>
NodoV<vertice>::NodoV()
{
  this->info = *( new vertice );
  this->prox = NULL;
  this->primero = NULL;
  this->visitado = false;
}

template<class vertice>
NodoV<vertice>::NodoV(NodoV<vertice> *p, NodoA<vertice> *pri, vertice i, bool mark)
{
  this->info = i;
  this->prox = p;
  this->primero = pri;
  this->visitado = mark;
}

template<class vertice>
vertice NodoV<vertice>::obtInfo()
{
  return this->info;
}

template<class vertice>
NodoV<vertice>* NodoV<vertice>::obtProx()
{
  return this->prox;
}

template<class vertice>
NodoA<vertice>* NodoV<vertice>::obtPrimero()
{
  return this->primero;
}

template<class vertice>
bool NodoV<vertice>::obtVisitado()
{
  return this->visitado;
}

template<class vertice>
void NodoV<vertice>::modInfo(vertice nuevo)
{
  this->info = nuevo;
}

template<class vertice>
void NodoV<vertice>::modProx(NodoV<vertice> *nuevo)
{
  this->prox = nuevo;
}

template<class vertice>
void NodoV<vertice>::modPrimero(NodoA<vertice> *nuevo)
{
  this->primero = nuevo;
}

template<class vertice>
void NodoV<vertice>::modVisitado(bool nuevo)
{
  this->visitado = nuevo;
}

#endif

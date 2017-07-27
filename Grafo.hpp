#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <cstdlib>
#include "Lista.h"
#include "Cola.h"
#include "NodoV.hpp"
#include "NodoA.hpp"

using namespace std;

template<class vertice>
class Grafo
{
  private:
    NodoV<vertice> *primero;
    int arcos;
    int vertices;
  public:
    /*------CONSTRUCTORES---------*/
    Grafo();
    /*------CONSULTORES------*/
    bool esVacio();
    int cardinalidad();
    Lista<vertice> obtVertices();
    bool existeVertice(vertice v);
    bool existeArco(vertice v, vertice w);
    Lista<vertice> sucesores(vertice v);
    Lista<vertice> predecesores(vertice v);
    /*------IMPRESORES------*/
    void print();
    /*------MODIFICADORES------*/
    void insertarVertice(vertice v);
    void insertarArco(vertice v, vertice w);
    void eliminarVertice(vertice v);
    void eliminarArco(vertice v, vertice w);
    /*------DESTRUCTORES------*/
    ~Grafo();

};
/*---------------------------CONSTRUCTORES---------------------------*/
template<class vertice>
Grafo<vertice>::Grafo()
{
  this->primero = NULL;
  this->arcos = 0;
  this->vertices = 0;
}
/*---------------------------CONSULTORES---------------------------*/
template<class vertice>
bool Grafo<vertice>::esVacio()
{
  return this->primero == NULL;
}

template<class vertice>
int Grafo<vertice>::cardinalidad()
{
  return this->vertices;
}

template<class vertice>
Lista<vertice> Grafo<vertice>::obtVertices()
{
  Lista<vertice> L;
  NodoV<vertice> *aux;

  if(this->primero != NULL)
  {
    aux = this->primero;
    while(aux != NULL)
    {
      L.insertar(aux->obtInfo(), 1);
      aux = aux->obtProx();
    }
  }
  return L;
}

template<class vertice>
bool Grafo<vertice>::existeVertice(vertice v)
{
  bool band;
  NodoV<vertice>* aux;

  band = false;
  if(this->primero != NULL)
  {
    aux = this->primero;
    while(aux != NULL && !band)
    {
      if(aux->obtInfo() == v)
      {
        band = true;
      }

      aux = aux->obtProx();
    }
  }
  return band;
}

template<class vertice>
bool Grafo<vertice>::existeArco(vertice v, vertice w)
{
  bool band;
  NodoV<vertice> *act;
  NodoA<vertice> *aux;

  band = false;

  if(this->primero != NULL)
  {
    act = this->primero;
    while(act != NULL && !band)
    {
      if(act->obtInfo() == v)
      {
        band = true;
      }
      act = act->obtProx();
    }

    if(band)
    {
      band = false;
      aux = act->obtPrimero();
      while (aux != NULL && !band)
      {
        if(aux->obtVertice()->obtInfo() == w)
          band = true;

        aux = aux->obtProx();
      }
    }

  }

  return band;

  // Esto es si es dirigido
  // if(this->primero != NULL)
  // {
  //     act = this->primero;
  //     while(act != NULL && !band && (act->obtInfo() == v || act->obtInfo() == w))
  //     {
  //       aux = act->obtPrimero();
  //       if(act->obtInfo()==v)
  //       {
  //         while(aux != NULL)
  //         {
  //           if(aux->obtVertice()->obtInfo()==w)
  //           {
  //             band = true;
  //           }
  //           aux = aux->obtProx();
  //         }
  //       }
  //       else
  //       {
  //         while(aux != NULL)
  //         {
  //           if(aux->obtVertice()->obtInfo()==v)
  //           {
  //             band = true;
  //           }
  //           aux = aux->obtProx();
  //         }
  //       }
  //       act = act->obtProx();
  //     }
  // }
}

template<class vertice>
Lista<vertice> Grafo<vertice>::sucesores(vertice v)
{
  Lista<vertice> L;
  NodoV<vertice> aux;
  NodoA<vertice> act;
  bool band;

  if(this->primero != NULL)
  {
    aux = this->primero;
    band=false;
    //Este metodo es teniendo en cuenta que el vertice existe
    while(aux != NULL && !band)
    {
      if(aux->obtInfo() == v)
        band = true;
      else
        aux = aux->obtProx();
    }

    act = aux->obtPrimero();
    while(act!=NULL)
    {
      L.insertar(act->obtVertice()->obtInfo(), 1);
      act = act->obtProx();
    }
  }

  return L;
}

template<class vertice>
Lista<vertice> Grafo<vertice>::predecesores(vertice v)
{
  Lista<vertice> L;
  NodoA<vertice> aux;
  NodoV<vertice> act;
  bool band;

  if(this->primero != NULL)
  {
    act = this->primero;
    while(act!=NULL)
    {
      if(act->obtInfo() != v)
      {
        aux = act->obtPrimero();
        band = false;
        while(aux != NULL && !band)
        {
          if(aux->obtVertice()->obtInfo() == v)
          {
            band =true;
            L.insertar(aux->obtVertice()->obtInfo(), 1);
          }
          else
          {
            aux = aux->obtProx();
          }
        }
      }
      act=act->obtProx();
    }
  }
  return L;
}
/*---------------------------IMPRESORES---------------------------*/
template<class vertice>
void Grafo<vertice>::print()
{
  NodoA<vertice> *ady;
  NodoV<vertice> *act;

  act = this->primero;
  while(act != NULL)
  {
    cout << "Vertice: " << act->obtInfo() <<endl;
    ady = act->obtPrimero();
    cout << "Con Arcos hacia: " << endl;
    while (ady != NULL)
    {
      cout << "---->" << ady->obtVertice()->obtInfo() << endl;
      ady = ady->obtProx();
    }
  }
}
/*---------------------------MODIFICADORES---------------------------*/
template <class vertice>
void Grafo<vertice>::insertarVertice(vertice v)
{
  NodoV<vertice> *nuevo, *aux;

  nuevo = new Nodo<vertice>;
  nuevo->modInfo(v);
  this->vertices = this->vertices + 1;
  if(this->primero == NULL)
  {
    this->primero = nuevo;
  }
  else
  {
    if(!this->existeVertice())
    {
      nuevo->modProx(this->primero);
      this->primero = nuevo;
    }
  }
}

template<class vertice>
void Grafo<vertice>::insertarArco(vertice v, vertice w)
{
  NodoV<vertice> act, aux2, aux3;
  NodoA<vertice> aux;
  bool band, band2, band3;
  if(this->primero == NULL)
  {
    //creo el primero nodo vertice
    aux2 = new NodoV<vertice>;
    aux2->modInfo(v);
    this->primero = aux2;
    //creo el segundo nodo vertice
    aux3 = new NodoV<vertice>;
    aux3->modInfo(w);
    //enlazo el primer nodo con el segundo
    aux2->modProx(aux3);
    //creo el nodo adyancente
    aux = new NodoA<vertice>;
    //lo enlazo con el vertice v
    aux2->modPrimero(aux);
    //apunta al vertice w
    aux->modVertice(aux3);
  }
  else
  {
    if(!this->existeArco(v, w))
    {
      act = this->primero;
      band = false;
      band2 = false;
      band3 = false;

      /*Busca a v y w al mismo tiempo por si existe una y otra no*/
      while(act != NULL && !band3)
      {
        if(act->obtInfo() == v) // Aqui busca a v
        {
          band = true;
          aux2 = act;
        }
        else if(act->obtInfo()==w) //aqui busca a w
        {
          band2 = true;
          aux3 = act;
        }

        if(!band || !band2) //Si no ha encontrado ambas entonces sigue buscando hasta encontrarlas
        {
          act = act->obtProx();
        }
        else
        {
          band3 = true;      //Cuando la encuentra a ambas asino haya terminado de recorrer entonces igual se sale del ciclo
        }
      }

      if(band && !band2) //Si existe solo el nodo v
      {
        //creo el nodo para w
        aux3 = new NodoV<vertice>;
        aux3->modInfo(w);
        //lo enlazo a la lista de vertices
        aux3->modProx(this->primero);
        this->primero = aux3;

      }
      else
      {
        if(band2 && !band) //si solo existe w
        {
          //creo el nodo para v
          aux2 = new NodoV<vertice>;
          aux2->modInfo(v);
          //lo enlazo a la lista de vertices
          aux2->modProx(this->primero);
          this->primero = aux2;
        }
        else if(!band && !band2) //Si no exitse v ni w pero tampoco es vacio el grafo
        {
          //creo el nodo para v
          aux2 = new NodoV<vertice>;
          aux2->modInfo(v);
          //lo enlazo a la lista de vertices
          aux2->modProx(this->primero);
          this->primero = aux2;
          //creo el nodo para w
          aux3 = new NodoV<vertice>;
          aux3->modInfo(w);
          //lo enlazo a la lista de vertices
          aux3->modProx(this->primero);
          this->primero = aux3;
        }
      }
      // Aqui hace el enlace del arco para todos los casos, includo cuando v y w existen
      aux = new NodoA<vertice>;   //Aqui creo el nuevo nodo ady
      aux->modVertice(aux3);      //Apunta a w
      aux->modProx(aux2->obtPrimero()); //el prox del nodo ady apunta a la lista de lso adyacentes quedando como el primero
      aux2->modPrimero(aux);  //el primero del nodo vertice pasa a ser el recien creado
      this->arcos = this->arcos + 1;
    }
  }
}

template<class vertice>
void Grafo<vertice>::eliminarVertice(vertice v)
{
  NodoA<vertice> *aux, *aux1;
  NodoV<vertice> *act, *ant;
  bool band;

  act = this->primero;
  ant = NULL;
  band = false;
  while(act != NULL && !band)
  {
    if(act->obtInfo()==v)
    {
      band = true;
      if(act == this->primero) //Esto es por si el vertice es el primero de la lista
      {
        ant = act->obtProx();
        this->primero = ant;
      }
      else        //Este condicional es basicamente para hacer el enlace de la lista y tener el nodo que voy a eliminar aparte en el apuntador act
      {
        ant->modProx(act->obtProx());
      }
    }
    else
    {
      ant = act;
      act = act->obtProx();
    }
  }

  if(band)        //Si encontro el vertice
  {
    aux = act->obtPrimero();
    while(aux != NULL)
    {
      aux1 = aux->obtProx();
      delete aux;
      aux = aux1;
    }
    delete act;
  }
}

template<class vertice>
void Grafo<vertice>::eliminarArco(vertice v, vertice w)
{
  NodoV<vertice> *act;
  NodoA<vertice> *aux, *ant;
  bool band;

  if(this->existeArco(v, w))
  {
    band = true;
    act = this->primero;
    while(!band)
    {
      if(act->obtInfo()==v)
        band = true;
      else
        act = act->obtInfo();
    }
    //No necesito preguntar por el booleano porque como existe el arco, entonces es seguro que se va a salir con band == true

    aux = act->obtPrimero();
    band = false;
    while(!band)
    {
      if(aux->obtVertice()->obtInfo()==w)
      {
        band = true;
        if(aux == act->obtPrimero())
        {
          ant = aux->obtProx();
          act->modPrimero(ant);
        }
        else
        {
          ant->modProx(aux->obtProx());
        }
      }
      else
      {
        ant = aux;
        aux = aux->obtProx();
      }
    }
    //No necesito preguntar por el booleano porque como existe el arco, entonces es seguro que se va a salir con band == true
    delete aux;
  }
}
/*---------------------------DESTRUCTORES---------------------------*/
template <class vertice>
Grafo<vertice>::~Grafo()
{
  NodoV<vertice> *act;
  NodoA<vertice> *aux, *aux2;

  act = this->primero;
  while(act!=NULL)
  {
    aux = act->obtPrimero();
    while(aux!= NULL)
    {
      aux2 = aux;
      aux = aux->obtProx();
      delete aux2;
    }

    this->primero = act->obtProx();
    delete act;
    act = this->primero;
  }
  this->vertices = 0;
  this->arcos = 0;
}
#endif

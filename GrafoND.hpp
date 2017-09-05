#ifndef GRAFOND_H
#define GRAFOND_H
#include <iostream>
#include <cstdlib>
#include "Lista.h"
#include "Cola.h"
#include "NodoV.hpp"
#include "NodoA.hpp"

using namespace std;

template<class vertice>
class GrafoND
{
  private:
    NodoV<vertice> *primero;
    int arcos;
    int vertices;
  public:
    /*------CONSTRUCTORES---------*/
    GrafoND();
    GrafoND(GrafoND<vertice> &orig);
    void copiar(const GrafoND<vertice> &orig);
    /*------CONSULTORES------*/
    bool esVacio();
    int cardinalidad();
    int obtNumArcos();
    float obtCostoArco(vertice v, vertice w);
    Lista<vertice> obtVertices();
    bool existeVertice(vertice v);
    bool existeArco(vertice v, vertice w);
    bool estaVisitado(vertice v);
    int gradoV(vertice);
    Lista<vertice> adyacentes(vertice v);
    bool esBicolor();
    /*Revisar*/void DFS(vertice v, Lista<vertice> &recorrido); //Recorrido en profundidad
    /*Revisar*/void arbolDFS(vertice v, Lista<vertice> &V, Lista<vertice> &W, Lista<vertice> &recorrido);
    /*Revisar*/Lista<vertice> BFS(vertice v); //recorrdio por anchura
    /*Revisar*/Lista<vertice> caminoHamiltoniano();
    /*Revisar*/void caminoHam(vertice v, Lista<vertice> &result, bool &band);
    /*------IMPRESORES------*/
    void print();
    /*------MODIFICADORES------*/
    void marcarVisitado(vertice v);
    void desmarcarVisitado(vertice v);
    void desmarcarVertices();
    void insertarVertice(vertice v);
    void insertarVerticeO(vertice v); //INSERTA OREDENADO
    void insertarArco(vertice v, vertice w, float costo);
    void insertarArcoO(vertice v, vertice w, float costo);
    void eliminarVertice(vertice v);
    void eliminarArco(vertice v, vertice w);
    /*------DESTRUCTORES------*/
    ~GrafoND();

    /*------SOBRECARGA DE OPERADORES------*/
    template<class Vertice>
    friend ostream& operator<<(ostream& out, GrafoND<Vertice>& G);
    bool operator ==(GrafoND<vertice> &G);
    GrafoND<vertice>& operator=(const GrafoND<vertice> &G);

};

/*---------------------------CONSTRUCTORES---------------------------*/
template<class vertice>
GrafoND<vertice>::GrafoND()
{
  this->primero = NULL;
  this->arcos = 0;
  this->vertices = 0;
}

template<class vertice>
GrafoND<vertice>::GrafoND(GrafoND<vertice> &orig)
{
  this->arcos = 0;
  this->vertices = 0;
  this->copiar = 0;
}

template<class vertice>
void GrafoND<vertice>::copiar(const GrafoND<vertice> &orig)
{
  NodoV<vertice> *act, *nuevoV, *ant, *aux, *act2;
  NodoA<vertice> *ady, *nuevoA, *antA;
  bool band;

  act = orig.primero;
  while(act!=NULL)
  {
    nuevoV = new NodoV<vertice>;
    nuevoV->modInfo(act->obtInfo());

    if(orig.primero == act)
      this->primero = nuevoV;
    else
      ant->modProx(nuevoV);

    ant = nuevoV;
    act = act->obtProx();

  }


  act = orig.primero;
  act2 = this->primero;
  while(act!=NULL)
  {
    ady = act->obtPrimero();
    while(ady!=NULL)
    {
      nuevoA = new NodoA<vertice>;
      aux = this->primero;
      band = false;
      while(aux!=NULL && !band)
      {
        if(aux->obtInfo() == ady->obtVertice()->obtInfo())
          band = true;
        else
          aux = aux->obtProx();
      }
      nuevoA->modVertice(aux);

      if(ady == act->obtPrimero())
        act2->modPrimero(nuevoA);
      else
        antA->modProx(nuevoA);

      antA = nuevoA;
      ady= ady->obtProx();
    }
    act = act->obtProx();
    act2 = act2->obtProx();
  }
  this->vertices = orig.vertices;
  this->arcos = orig.arcos;
}
/*---------------------------CONSULTORES---------------------------*/
template<class vertice>
bool GrafoND<vertice>::esVacio()
{
  return this->primero == NULL;
}

template<class vertice>
int GrafoND<vertice>::cardinalidad()
{
  return this->vertices;
}

template<class vertice>
int GrafoND<vertice>::obtNumArcos()
{
    return this->arcos;
}

template<class vertice>
float GrafoND<vertice>::obtCostoArco(vertice v, vertice w)
{
  NodoV<vertice> *act;
  NodoA<vertice> *ady;
  bool band;
  float costo;

  band = false;
  act = this->primero;
  while(act!= NULL && !band)
  {
    if (act->obtInfo() == v)
    {
      ady = act->obtPrimero();
      while(ady != NULL && !band)
      {
        if(ady->obtVertice()->obtInfo()==w)
        {
          costo = ady->obtCosto();
          band = true;
        }
        else
        {
          ady = ady->obtProx();
        }
      }
    }

    if (act->obtInfo() == w)
    {
      ady = act->obtPrimero();
      while(ady != NULL && !band)
      {
        if(ady->obtVertice()->obtInfo()==v)
        {
          costo = ady->obtCosto();
          band = true;
        }
        else
        {
          ady = ady->obtProx();
        }
      }
    }
    act = act->obtProx();
  }

  if(band)
    return costo;
  else
    return -1;
}

template<class vertice>
Lista<vertice> GrafoND<vertice>::obtVertices()
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
bool GrafoND<vertice>::existeVertice(vertice v)
{
  bool band;
  NodoV<vertice> *aux;

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
bool GrafoND<vertice>::existeArco(vertice v, vertice w)
{
  bool band;
  NodoV<vertice> *act;
  NodoA<vertice> *aux;

  band = false;

  act = this->primero;

  if(this->primero != NULL)
  {
      act = this->primero;
      while(act != NULL && !band && (act->obtInfo() == v || act->obtInfo() == w))
      {
        aux = act->obtPrimero();
        if(act->obtInfo()==v)
        {
          while(aux != NULL)
          {
            if(aux->obtVertice()->obtInfo()==w)
            {
              band = true;
            }
            aux = aux->obtProx();
          }
        }
        else
        {
          while(aux != NULL)
          {
            if(aux->obtVertice()->obtInfo()==v)
            {

              band = true;
            }
            aux = aux->obtProx();
          }
        }
        act = act->obtProx();
      }
  }
  return band;
}

template<class vertice>
bool GrafoND<vertice>::estaVisitado(vertice v)
{
  NodoV<vertice> *act;
  bool band;

  act = this->primero;
  band = false;
  //No hace falta la condicion act!=NULL porque se supone que existe y en algun momento se saldra con el booleano
  while(!band)
  {
    if(act->obtInfo()==v)
      band = true;
    else
      act = act->obtProx();
  }

  return act->obtVisitado();
}

template<class vertice>
int GrafoND<vertice>::gradoV(vertice v)
{
  int cont;
  bool band;
  NodoV<vertice> *act;
  NodoA<vertice> *ady;

  act = this->primero;
  band = false;
  while(act!=NULL && !band)
  {
    if(act->obtInfo()==v)
    {
      band = true;
      cont=0;

      ady = act->obtPrimero();
      while(ady!=NULL)
      {
        cont++;
        ady = ady->obtProx();
      }
    }
    else
      act = act->obtProx();
  }
}

template<class vertice>
Lista<vertice> GrafoND<vertice>::adyacentes(vertice v)
{
  Lista<vertice> L;
  NodoV<vertice> *aux;
  NodoA<vertice> *act;
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
bool GrafoND<vertice>::esBicolor()
{
  return this->arcos == this->vertices - 1;
}

template <class vertice>
void GrafoND<vertice>::DFS(vertice v, Lista<vertice> &recorrido)
{
  Lista<vertice> suc;
  vertice w;

  suc = this->adyacentes(v);

  while(!suc.esVacia())
  {
    w = suc.consultar(1);
    if(!recorrido.esta(w))
    {
      recorrido.insertar(w,1);
      this->DFS(w,recorrido);
    }
    suc.eliminar(1);
  }
}

template <class vertice>
void GrafoND<vertice>::arbolDFS(vertice v, Lista<vertice> &V, Lista<vertice> &W, Lista<vertice> &recorrido)
{
  Lista<vertice> suc;
  vertice w;

  suc = this->adyacentes(v);
  if(!recorrido.esta(v))
    recorrido.insertar(v, 1);
  while(!suc.esVacia())
  {
    w = suc.consultar(1);
    if(!recorrido.esta(w))
    {
      recorrido.insertar(w, 1);
      V.insertar(v,1);
      W.insertar(w,1);
      this->arbolDFS(w,V, W, recorrido);
    }
    suc.eliminar(1);
  }
}

template<class vertice>
Lista<vertice> GrafoND<vertice>::BFS(vertice v)
{
  Lista<vertice> result, aux;
  vertice element;
  Cola<vertice> c;

  c.encolar(v);
  while(!c.esVacia())
  {
    element = c.frente();
    aux = this->adyacentes(element);

    result.insertar(element, 1);
    while(!aux.esVacia())
    {
      element = aux.consultar(1);
      if(!result.esta(element))
      {
        c.encolar(element);
      }
      aux.eliminar(1);
    }
    c.desencolar();
  }

  result.invertir();
  return result;
}

template<class vertice>
Lista<vertice> GrafoND<vertice>::caminoHamiltoniano()
{
  NodoV<vertice> *act;
  bool band;
  Lista<vertice> result;

  band = false;
  act = this->primero;

  while(act!=NULL && !band)
  {
    result.insertar(act->obtInfo(), 1);
    this->caminoHam(act->obtInfo(), result, band);

    act = act->obtProx();
    if(!band)
      result.vaciar();
  }
  result.invertir();
  return result;
}

template <class vertice>
void GrafoND<vertice>::caminoHam(vertice v, Lista<vertice> &result, bool &band)
{
  vertice ady;
  Lista<vertice> aux;

  aux = this->adyacentes(v);
  while(!aux.esVacia() && !band)
  {
    ady = aux.consultar(1);
    aux.eliminar(1);
    if(!result.esta(ady))
    {
      result.insertar(ady, 1);
      if(result.obtLong() == this->vertices)
      {
        band = true;
      }
      else
      {
        caminoHam(ady, result, band);
      }

      if(!band)
      {
        result.eliminar(1);
      }
    }
  }
}

/*---------------------------IMPRESORES---------------------------*/
template<class vertice>
void GrafoND<vertice>::print()
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
    act = act->obtProx();
  }
}
/*---------------------------MODIFICADORES---------------------------*/
template<class vertice>
void GrafoND<vertice>::marcarVisitado(vertice v)
{
  NodoV<vertice> *act;
  bool band;

  act = this->primero;
  band = false;
  while(act!=NULL && !band)
  {
    if(act->obtInfo()==v)
      band = true;
    else
      act = act->obtProx();
  }

  if(band)
    act->modVisitado(true);
}

template<class vertice>
void GrafoND<vertice>::desmarcarVisitado(vertice v)
{
  NodoV<vertice> *act;
  bool band;

  band = false;
  act = this->primero;
  while(act!=NULL && !band)
  {
    if(act->obtInfo()==v)
      band = true;
    else
      act = act->obtProx();
  }

  if(band)
    act->modVisitado(false);
}

template<class vertice>
void GrafoND<vertice>::desmarcarVertices()
{
  NodoV<vertice> *act;

  act = this->primero;
  while(act!=NULL)
  {
    act->modVisitado(false);
    act = act->obtProx();
  }
}

template <class vertice>
void GrafoND<vertice>::insertarVertice(vertice v)
{
  NodoV<vertice> *nuevo, *aux;

  if(this->primero == NULL)
  {
    nuevo = new NodoV<vertice>;
    nuevo->modInfo(v);
    this->primero = nuevo;
    this->vertices = this->vertices + 1;
  }
  else
  {
    if(!this->existeVertice(v))
    {
      nuevo = new NodoV<vertice>;
      nuevo->modInfo(v);
      nuevo->modProx(this->primero);
      this->primero = nuevo;
      this->vertices = this->vertices + 1;
    }
  }
}

template<class vertice>
void GrafoND<vertice>::insertarVerticeO(vertice v)
{
  NodoV<vertice> *nuevo, *act, *ant;
  bool band;

  if(!this->existeVertice(v))
  {
    nuevo = new NodoV<vertice>;
    nuevo->modInfo(v);
    if(this->primero == NULL)
    {
      this->primero = nuevo;
    }
    else
    {
      act = this->primero;
      ant = NULL;
      band = false;
      while(act != NULL && !band)
      {
        if(v < act->obtInfo())
        {
          band = true;
          if(this->primero == act)
          {
            nuevo->modProx(this->primero);
            this->primero = nuevo;
          }
          else
          {
            ant->modProx(nuevo);
            nuevo->modProx(act);
          }
        }
        else
        {
          ant = act;
          act = act->obtProx();
        }
      }
      if(!band)
      {
        ant->modProx(nuevo);
      }
    }


    this->vertices = this->vertices + 1;
  }
}

template<class vertice>
void GrafoND<vertice>::insertarArco(vertice v, vertice w, float costo)
{
  NodoV<vertice> *act, *aux2, *aux3;
  NodoA<vertice> *aux;
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
    aux->modCosto(costo);

    aux = new NodoA<vertice>;
    aux3->modPrimero(aux);
    aux->modVertice(aux2);
    aux->modCosto(costo);

    this->arcos = this->arcos + 1;
    this->vertices = this->vertices + 2;
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
        this->vertices = this->vertices + 1;

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
          this->vertices = this->vertices + 1;
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
          this->vertices = this->vertices + 2;
        }
      }
      // Aqui hace el enlace del arco para todos los casos, includo cuando v y w existen
      aux = new NodoA<vertice>;   //Aqui creo el nuevo nodo ady
      aux->modVertice(aux3);      //Apunta a w
      aux->modProx(aux2->obtPrimero()); //el prox del nodo ady apunta a la lista de lso adyacentes quedando como el primero
      aux->modCosto(costo);
      aux2->modPrimero(aux);  //el primero del nodo vertice pasa a ser el recien creado

      aux = new NodoA<vertice>;   //Aqui creo el nuevo nodo ady
      aux->modVertice(aux2);      //Apunta a w
      aux->modProx(aux3->obtPrimero()); //el prox del nodo ady apunta a la lista de lso adyacentes quedando como el primero
      aux->modCosto(costo);
      aux3->modPrimero(aux);
      this->arcos = this->arcos + 1;
    }
  }
}

template<class vertice>
void GrafoND<vertice>::insertarArcoO(vertice v, vertice w, float costo)
{
  NodoV<vertice> *act, *aux2, *aux3, *ante;
  NodoA<vertice> *aux, *ant, *ady;
  bool band, band2, band3;
  if(this->primero == NULL)
  {
    //creo el primero nodo vertice
    aux2 = new NodoV<vertice>;
    aux2->modInfo(v);
    //creo el segundo nodo vertice
    aux3 = new NodoV<vertice>;
    aux3->modInfo(w);

    if(aux2->obtInfo() < aux3->obtInfo())
    {
      this->primero = aux2;
      aux2->modProx(aux3);
    }
    else
    {
      this->primero = aux3;
      aux3->modProx(aux2);
    }

    //creo el nodo adyancente
    aux = new NodoA<vertice>;
    aux->modVertice(aux3);
    aux->modCosto(costo);
    aux2->modPrimero(aux);

    //creo el nodo adyancente
    aux = new NodoA<vertice>;
    aux->modVertice(aux2);
    aux->modCosto(costo);
    aux3->modPrimero(aux);
    this->arcos = this->arcos + 1;
    this->vertices = this->vertices + 2;
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
        act = this->primero;
        band = false;
        aux3 = new NodoV<vertice>;
        aux3->modInfo(w);
        while(act != NULL && !band)
        {
          if(w < act->obtInfo())
          {
            band = true;
            if(this->primero == act)
            {
              aux3->modProx(act);
              this->primero = aux3;
            }
            else
            {
              aux3->modProx(act);
              ante->modProx(aux3);
            }
          }
          else
          {
            ante = act;
            act = act->obtProx();
          }
        }

        if(!band)
        {
          ante->modProx(aux3);
        }
        this->vertices = this->vertices + 1;
      }
      else
      {
        if(band2 && !band) //si solo existe w
        {
          act = this->primero;
          band = false;
          aux2 = new NodoV<vertice>;
          aux2->modInfo(v);
          while(act != NULL && !band)
          {
            if(v < act->obtInfo())
            {
              band = true;
              if(this->primero == act)
              {
                aux2->modProx(act);
                this->primero = aux2;
              }
              else
              {
                aux2->modProx(act);
                ante->modProx(aux2);
              }
            }
            else
            {
              ante = act;
              act = act->obtProx();
            }
          }

          if(!band)
          {
            ante->modProx(aux2);
          }
          this->vertices = this->vertices + 1;
        }
        else if(!band && !band2) //Si no exitse v ni w pero tampoco es vacio el grafo
        {
          aux2 = new NodoV<vertice>;
          aux2->modInfo(v);

          aux3 = new NodoV<vertice>;
          aux3->modInfo(w);

          act = this->primero;
          band = false;
          while(act != NULL && !band)
          {
            if(v < act->obtInfo())
            {
              band = true;
              if(this->primero == act)
              {
                aux2->modProx(act);
                this->primero = aux2;
              }
              else
              {
                aux2->modProx(act);
                ante->modProx(aux2);
              }
            }
            else
            {
              ante = act;
              act = act->obtProx();
            }
          }

          if(!band)
          {
            ante->modProx(aux2);
          }

          act = this->primero;
          band = false;
          while(act != NULL && !band)
          {
            if(w < act->obtInfo())
            {
              band = true;
              if(this->primero == act)
              {
                aux3->modProx(act);
                this->primero = aux3;
              }
              else
              {
                aux3->modProx(act);
                ante->modProx(aux3);
              }
            }
            else
            {
              ante = act;
              act = act->obtProx();
            }
          }
          if(!band)
          {
            ante->modProx(aux3);
          }
          this->vertices = this->vertices + 2;
        }
      }
      aux = new NodoA<vertice>;
      aux->modVertice(aux3);
      aux->modCosto(costo);
      ady = aux2->obtPrimero();

      if(ady == NULL)
        aux2->modPrimero(aux);
      else
      {
        band = false;
        while(ady != NULL && !band)
        {
          if(aux->obtVertice()->obtInfo() < ady->obtVertice()->obtInfo())
          {
            band = true;
            if(ady == aux2->obtPrimero())
            {
              aux->modProx(ady);
              aux2->modPrimero(aux);
            }
            else
            {
              aux->modProx(ady);
              ant->modProx(aux);
            }
          }
          else
          {
            ant = ady;
            ady = ady->obtProx();
          }
        }

        if(!band)
          ant->modProx(aux);
      }

      aux = new NodoA<vertice>;
      aux->modVertice(aux2);
      aux->modCosto(costo);
      ady = aux3->obtPrimero();

      if(ady == NULL)
        aux3->modPrimero(aux);
      else
      {
        band = false;
        while(ady != NULL && !band)
        {
          if(aux->obtVertice()->obtInfo() < ady->obtVertice()->obtInfo())
          {
            band = true;
            if(ady == aux3->obtPrimero())
            {
              aux->modProx(ady);
              aux3->modPrimero(aux);
            }
            else
            {
              aux->modProx(ady);
              ant->modProx(aux);
            }
          }
          else
          {
            ant = ady;
            ady = ady->obtProx();
          }
        }

        if(!band)
          ant->modProx(aux);
      }
      this->arcos = this->arcos + 1;
    }
  }
}

template<class vertice>
void GrafoND<vertice>::eliminarVertice(vertice v)
{
  NodoA<vertice> *aux, *aux1;
  NodoV<vertice> *act, *ant, *aux3;
  bool band;

  act = this->primero;
  ant = NULL;
  while(act != NULL)
  {
    if(act->obtInfo()==v)
    {
      if(act == this->primero) //Esto es por si el vertice es el primero de la lista
      {
        ant = act->obtProx();
        this->primero = ant;
      }
      else        //Este condicional es basicamente para hacer el enlace de la lista y tener el nodo que voy a eliminar aparte en el apuntador act
      {
        ant->modProx(act->obtProx());
      }
      //Luego de encontrarlo borra todos sus sucesores
      aux = act->obtPrimero();
      while(aux != NULL)
      {
        aux1 = aux->obtProx();
        delete aux;
        aux = aux1;
      }
      ant = act;
      act = act->obtProx();
      aux3 = act;
      delete aux3;
      this->vertices = this->vertices - 1;
    }
    else
    {
      aux = act->obtPrimero();
      band = false;
      while(aux!=NULL && !band)
      {
        if(aux->obtVertice()->obtInfo()==v)
        {
          band = true;
          if(aux == act->obtPrimero())
            act->modPrimero(aux->obtProx());
          else
            aux1->modProx(aux->obtProx());

          delete aux;
        }
        else
        {
          aux1 = aux;
          aux = aux->obtProx();
        }
      }
      ant = act;
      act = act->obtProx();
    }
  }
}

template<class vertice>
void GrafoND<vertice>::eliminarArco(vertice v, vertice w)
{
  NodoV<vertice> *act;
  NodoA<vertice> *aux, *ant;
  bool band;

  if(this->existeArco(v, w))
  {
    band = false;
    act = this->primero;
    while(!band)
    {
      if(act->obtInfo()==v)
        band = true;
      else
        act = act->obtProx();
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
    this->arcos = this->arcos - 1;
  }
}

/*---------------------------DESTRUCTORES---------------------------*/
template <class vertice>
GrafoND<vertice>::~GrafoND()
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

/*---------------------------SOBRECARGA DE OPERADORES---------------------------*/
template <class Vertice>
ostream& operator<<(ostream& out, GrafoND<Vertice> &G)
{
  NodoV<Vertice> *act;
  NodoA<Vertice> *ady;

  act = G.primero;

  if(act == NULL)
    out << "El grafo esta vacio" << endl;
  else
  {
    out << "-----GRAFO-----" << endl;

    while(act != NULL)
    {
      out << " " << act->obtInfo();
      ady = act->obtPrimero();

      while(ady != NULL)
      {
        out << " " << ady->obtVertice()->obtInfo();
        ady = ady->obtProx();
      }
      out << "\n";
      act = act->obtProx();
    }
  }
  return out;
}

template <class vertice>
bool GrafoND<vertice>::operator==(GrafoND<vertice> &G)
{
  NodoV<vertice> *act;
  NodoA<vertice> *ady;
  bool band, band2;

  if(this->primero == NULL && G.primero ==NULL)
    band = true;
  else
  {
    if(this->vertices != G.vertices || this->arcos!=G.arcos)
    {
       band = false;
    }
    else
    {
      act = this->primero;
      band = true;
      while( act != NULL && band)
      {
        if(G.existeVertice(act->obtInfo()) == false)
          band = false;
        else
        {
          ady = act->obtPrimero();
          band2 = true;
          while(ady != NULL && band2)
          {
            if(G.existeArco(act->obtInfo(), ady->obtVertice()->obtInfo()) == false)
            {
              band = false;
              band2 = false;
            }
            else
              ady = ady->obtProx();
          }
        }
        act = act->obtProx();
      }
    }
  }
  return band;
}

template <class vertice>
GrafoND<vertice>& GrafoND<vertice>::operator=(const GrafoND<vertice> &G)
{

  this->copiar(G);
  return *this;
}

#endif

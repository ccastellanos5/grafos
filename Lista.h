#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"
#include <iostream>

using namespace std;

template <class T>
class Lista
{
	protected:
		Nodo<T>* primero;
		int longitud;
		void mezcla(Nodo<T> *(*p), Nodo<T> *s);
	public:
		Lista();																						//Constructor
		Lista(Lista<T> &original);													//Constructor copia
		int obtLong();
		bool esVacia();
		void copiar(const Lista<T> &original);
		bool esta(T elemento);
		T consultar(int pos);
		int aparicion(T elemento);													//devuelve el numero de apariciones de un elemento en la lista
		Lista<int> aparicionL(T elemento);										//devuelve una lista con las posiciones donde se encuentra el elemento;
		int posicion(T elemento);														//Devuelve la posicion de un elemento
		T obtMayor();																				//Devuelve el mayor de la Lista
		T obtMenor();																				//Devuelve el menor de la lista
		Lista<T> subLista(int inicio, int fin);							//Obtiene una subLista
		void insertar(T elemento, int pos);									//Inserta un elemento en un pos
		void insertar(T elemento, bool band);								//Inserta un elemento de manera ordenada
		void insertar(Lista<T> &ls, int pos);								//Inserta una lista dentro de otra
		void eliminar(int pos);
		void eliminar(int inicio, int fin);									//Eliminar los elementos entre dos posiciones
		void modificar(T elemento, int pos);
		void invertir();																		//Invierte una lista completa
		void invertirSub(T a, T b);													//Invierte una sub lista
		void ordenarA();																		//Ordena ascendente
		void ordenarD();																		//Ordena Descendente
		void mezclar(Lista<T> &p, Lista<T> &s);							//mezcla dos lista de manera ordenada
		void imprimir();
		void vaciar();
		~Lista();
		Lista<T> operator =(const Lista<T> &original);
		bool operator ==(const Lista<T> &original);
		Lista<T> operator +(const Lista<T> &L1);
		bool operator <(Lista<T> L2);
		bool operator >(Lista<T> L2);
		template <class t>
		friend ostream& operator << (ostream &op,const Lista<t> &l);
};

template <class T>
Lista<T>::Lista()
{

	this->primero = NULL;
	this->longitud = 0;
}

template <class T>
Lista<T>::Lista(Lista<T> &original)
{
	this->longitud = 0;
	this->primero= NULL;
	this->copiar(original);
}

template <class T>
int Lista<T>::obtLong()
{
	return this->longitud;
}

template <class T>
bool Lista<T>::esVacia()
{
	return this->longitud == 0;
}

template <class T>
void Lista<T>::copiar(const Lista<T> &original)
{
	int i;
	Nodo<T> *nuevo, *act, *ant;
	this->vaciar();

	if(original.longitud != 0)
	{
		act = original.primero;
		nuevo = new Nodo<T>;
		nuevo->modInfo(act->obtInfo());
		nuevo->modProx(NULL);
		this->primero = nuevo;

		for (i = 2; i <= original.longitud ; i++)
		{
			act = act->obtProx();
			ant = nuevo;
			nuevo = new Nodo<T>;
			nuevo->modInfo(act->obtInfo());
			nuevo->modProx(NULL);
			ant->modProx(nuevo);
		}
		this->longitud = original.longitud;

	}
}


template <class T>
bool Lista<T>::esta(T elemento)
{
	Nodo<T> *act;
	bool band;

	band = false;
	act = this->primero;
	while(act != NULL && !band)
	{
		if (act->obtInfo() == elemento)
		band = true;
		act= act->obtProx();
	}

	return band;
}

template <class T>
T Lista<T>::consultar(int pos)
{
	Nodo<T> *act;
	int i;
	act = this->primero;
	for (i = 2; i <= pos; i++)
	{
		act = act->obtProx();
	}
	return act->obtInfo();
}

template <class T>
int Lista<T>::aparicion(T elemento)
{
	Nodo<T> *act;
	int i;

	i=0;
	act = this->primero;
	while(act != NULL)
	{
		if(act->obtInfo()==elemento)
		{
			i++;
		}
		act=act->obtProx();
	}
	return i;
}

template <class T>
Lista<int> Lista<T>::aparicionL(T elemento)
{
	Lista<T> result;
	Nodo<T> *act;
	int i;

	act = this->primero;
	i=1;
	while(act!=NULL)
	{
		if(act->obtInfo() == elemento)
		{
			result.insertar(i,1);
		}
		i++;
		act = act->obtProx();
	}
	result.invertir();
	return result;
}

template <class T>
int Lista<T>::posicion(T elemento)
{
	Nodo<T>* aux;
	int i;

	aux = this->primero;
	i = 1;

	while(aux != NULL && aux->obtInfo() != elemento)
	{
		aux = aux->obtProx();
		i++;
	}

	if(aux == NULL)
		return 0;
	else
		return i;
}

template<class T>
T Lista<T>::obtMayor()
{
	Nodo<T> *aux;
	T result;

	if(this->primero != NULL)
	{
		aux = this->primero;
		result = aux->obtInfo();
		while(aux != NULL)
		{
			aux = aux->obtProx();
			if(aux!= NULL && aux->obtInfo() > result)
			{
				result = aux->obtInfo();
			}
		}
		return result;
	}
	else
	{
		cout << "ERROR (Lista Vacia)" << endl;
	}
}

template <class T>
T Lista<T>::obtMenor()
{
	Nodo<T> *aux;
	T result;

	if(this->primero != NULL)
	{
		aux = this->primero;
		result = aux->obtInfo();
		while(aux != NULL)
		{
			aux = aux->obtProx();
			if(aux!= NULL && aux->obtInfo() < result)
			{
				result = aux->obtInfo();
			}
		}
		return result;
	}
	else
	{
		cout << "ERROR (Lista Vacia)" << endl;
	}
}

template <class T>
Lista<T> Lista<T>::subLista(int inicio, int fin)
{
	Nodo<T> *aux, *nuevo, *act;
	Lista<T> result;

	aux = this->primero;
	int i;

	if(inicio <= fin && inicio >= 1 && fin <= this->longitud)
	{
		for(i = 0; i < inicio - 1; i++)
		{
			aux = aux->obtProx();
		}

		nuevo = new Nodo<T>;
		nuevo->modInfo(aux->obtInfo());
		result.primero = nuevo;
		aux = aux->obtProx();
		act = nuevo;
		result.longitud = 1;

		for(i = inicio; i < fin; i++)
		{
			nuevo = new Nodo<T>;
			nuevo->modInfo(aux->obtInfo());
			act->modProx(nuevo);
			aux = aux->obtProx();
			act = nuevo;
			result.longitud++;
		}
		act->modProx(NULL);
	}
	return result;

}

template <class T>
void Lista<T>::insertar(T elemento, int pos)
{
	Nodo<T> *act, *nuevo;
	int i;
	if(pos >= 1 && pos <= this->longitud + 1)
	{
		nuevo = new Nodo<T>;
		nuevo->modInfo(elemento);
		if(pos == 1)
		{
			nuevo->modProx(this->primero);
			this->primero = nuevo;
		}
		else
		{
			act = this->primero;
			for (i = 2; i < pos; i++)
				act = act->obtProx();

			nuevo->modProx(act->obtProx());
			act->modProx(nuevo);
		}
		(this->longitud)++;
	}
}

template <class T>
void Lista<T>::insertar(T elemento, bool band)
{
	Nodo<T> *aux, *nuevo, *act;
	bool flag = true;

	nuevo = new Nodo<T>;
	nuevo->modInfo(elemento);
	act = this->primero;
	aux = NULL;
	this->longitud++;

	if(band)
	{
		while(act != NULL && flag)
		{
			if(act->obtInfo() >= elemento)
			{
				flag = false;
			}
			else
			{
				aux = act;
				act = act->obtProx();
			}
		}

		if(aux == NULL)
		{
			this->primero = nuevo;
			nuevo->modProx(act);
		}
		else
		{
			aux->modProx(nuevo);
			nuevo->modProx(act);
		}

	}
	else
	{
		while(act != NULL && flag)
		{
			if(act->obtInfo() <= elemento)
			{
				flag = false;
			}
			else
			{
				aux = act;
				act = act->obtProx();
			}
		}

		if(aux == NULL)
		{
			this->primero = nuevo;
			nuevo->modProx(act);
		}
		else
		{
			aux->modProx(nuevo);
			nuevo->modProx(act);
		}

	}
}

template <class T>
void Lista<T>::insertar(Lista<T> &ls, int pos)
{
	Lista<T> aux;
	int i;
	Nodo<T> *act, *aux2;

	aux.copiar(ls);
  act = this->primero;
	if(pos == 1)
	{
		this->primero = aux.primero;
		aux2 = this->primero;

		for(i = 0; i < aux.longitud - 1; i++)
		{
			aux2 = aux2->obtProx();
		}
		aux2->modProx(act);
	}
	else
	{
		aux2 = act->obtProx();
		for(i = 0; i < pos - 2; i++)
		{
			act = act->obtProx();
			aux2 = act->obtProx();
		}
		act->modProx(aux.primero);

		for(i = 0; i < aux.longitud; i++)
		{
			act = act->obtProx();
		}
		act->modProx(aux2);
	}
	this->longitud = this->longitud + aux.longitud;
	aux.primero = NULL;
	aux.longitud = 0;
}

template <class T>
void Lista<T>::eliminar(int pos)
{
	Nodo<T> *act, *aux;
	int i;
	act = this->primero;
	if(pos == 1)
	{
		this->primero = act->obtProx();
		delete act;
	}
	else
	{
		for (i = 2; i < pos; i++)
			act = act->obtProx();

		aux = act->obtProx();
		act->modProx(aux->obtProx());
		delete aux;
	}
	(this->longitud)--;
}

template <class T>
void Lista<T>::eliminar(int inicio, int fin)
{
	Nodo<T> *act, *sig, *aux;
	int i, j;

	act = this->primero;
	for(i = 1; i < inicio - 1; i++)
	{
		act = act->obtProx();
	}
	sig = act;
	for(j = i; j < fin + 1; j++)
	{
		sig = sig->obtProx();
	}

	if(inicio == 1)
	{
		this->primero = sig;
	}
	else
	{
		aux = act->obtProx();
		act->modProx(sig);
		act = aux;
	}

	while(act != sig)
	{
		aux = act;
		act = act->obtProx();
		delete aux;
		this->longitud--;
	}
}

template <class T>
void Lista<T>::modificar(T elemento, int pos)
{
	int i;
	Nodo<T> *act;
	act = this->primero;

	for (i = 2; i <= pos; i++)
		act = act->obtProx();

	act->modInfo(elemento);
}

template <class T>
void Lista<T>::invertir()
{
	Nodo<T> *sig, *act, *ant;

	ant = NULL;
	act = this->primero;
	while( act != NULL)
	{
		sig = act->obtProx();
		act->modProx(ant);
		ant = act;
		act = sig;
	}
	this->primero = ant;
}

template <class T>
//Asumiendo que las lentras estan en la cadena y que no se repiten y que b no puede estar antes que a
void Lista<T>::invertirSub(T a, T b)
{
	Nodo<T> *ant, *rec, *ult, *sig, *aux;
	rec = this->primero;

	if(rec->obtInfo() != b)
	{
			while(rec->obtInfo() != a)
			{
				ant = rec;
				rec = rec->obtProx();
			}
			ult = rec;
			sig = ult->obtProx();
			while(ult->obtInfo() != b)
			{
				ult = sig;
				sig = sig->obtProx();
			}

			if(rec != ult)
			{
				aux = rec->obtProx();
				ant->modProx(ult);
				rec->modProx(sig);

			}
			while(rec != ult)
			{
				ant = rec;
				rec = aux;
				aux = aux->obtProx();
				rec->modProx(ant);
			}
	}
}

template<class T>
void Lista<T>::ordenarA()
{
	int i, j;
	Nodo<T> *sig, *act;
	T aux;


	for (i = 1; i < this->longitud; i++)
	{
		act = this->primero;
		sig = act->obtProx();
		for (j = 1; j < this->longitud ; j++)
		{
				if(sig->obtInfo() < act->obtInfo())
				{
					aux = sig->obtInfo();
					sig->modInfo(act->obtInfo());
					act->modInfo(aux);
				}
				act = sig;
				sig = sig->obtProx();
		}
	}
}

template<class T>
void Lista<T>::ordenarD()
{
	int i, j;
	Nodo<T> *sig, *act;
	T aux;

	for (i = 1; i < this->longitud; i++)
	{
		act = this->primero;
		sig = act->obtProx();
		for (j = 1; j < this->longitud ; j++)
		{
				if(sig->obtInfo() > act->obtInfo())
				{
					aux = sig->obtInfo();
					sig->modInfo(act->obtInfo());
					act->modInfo(aux);
				}
				act = sig;
				sig = sig->obtProx();
		}
	}
}

template <class T>
void Lista<T>::mezcla(Nodo<T> *(*p), Nodo<T> *s)
{
	if (s != NULL)
	{
		this->mezcla(p, s->obtProx());
		while((*p) && (*p)->obtInfo() <= s->obtInfo())
		{
			this->insertar((*p)->obtInfo(), 1);
			(*p) = (*p)->obtProx();
		}
		this->insertar(s->obtInfo(), 1);
	}
}

template <class T>
void Lista<T>::mezclar(Lista<T> &p, Lista<T> &s)
{
	Nodo<T> **x, *y;

	x = &p.primero;
	y = s.primero;

	this->mezcla(x, y);
	while ((*x) != NULL)
	{
		this->insertar((*x)->obtInfo(), 1);
		(*x) = (*x)->obtProx();
	}

}

template <class T>
void Lista<T>::imprimir()
{
	Nodo<T> *aux;

		aux = this->primero;
		while(aux != NULL)
		{
			cout << aux->obtInfo() << " ";
			aux = aux->obtProx();
		}
		cout << endl;
}


template <class T>
void Lista<T>::vaciar()
{
	Nodo<T> *act;
	if (this->longitud != 0)
	{
		act = this->primero;
		while(act != NULL)
		{
			this->primero = act->obtProx();
			delete act;
			act = this->primero;
		}
		this->longitud = 0;
	}
}

template <class T>
Lista<T>::~Lista()
{
	while(!this->esVacia())
		this->eliminar(1);
}

template <class T>
Lista<T> Lista<T>::operator =(const Lista<T> &original)
{
	this->copiar(original);
	return *(this);
}

template <class T>
bool Lista<T>::operator ==(const Lista<T> &original)
{
	Nodo<T> *act, *act2;

	if(this->longitud == original.longitud)
	{
		act = this->primero;
		act2 = original.primero;

		while(act!=NULL && act->obtInfo() == act2->obtInfo())
		{
			act = act->obtProx();
			act2 = act2->obtProx();
		}

		if(act == NULL)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

template<class T>
Lista<T> Lista<T>::operator +(const Lista<T> &L1)
{
	Lista<T> L3, aux1, aux2;
	T sum1, sum2;

	aux1.copiar(L1);
	aux2.copiar(*this);

	while(!aux1.esVacia() && !aux2.esVacia())
	{
		sum1 = aux1.consultar(1);
		sum2 = aux2.consultar(1);

		L3.insertar(sum1 + sum2, 1);

		aux1.eliminar(1);
		aux2.eliminar(1);
	}

	while(!aux1.esVacia())
	{
		L3.insertar(aux1.consultar(1), 1);
		aux1.eliminar(1);
	}

	while(!aux2.esVacia())
	{
		L3.insertar(aux2.consultar(1), 1);
		aux2.eliminar(1);
	}

	L3.invertir();
	return L3;
}

template <class T>
bool Lista<T>::operator <(Lista<T> L2)
{
	return this->obtLong() < L2.obtLong();
}

template <class T>
bool Lista<T>::operator >(Lista<T> L2)
{
	return this->obtLong() > L2.obtLong();
}

template<class T>
ostream& operator << (ostream &op,const Lista<T> &l)
{
	Nodo<T> *act;

	act = l.primero;

	while(act != NULL)
	{
		op << act->obtInfo() << " ";
		act = act->obtProx();
	}

	return op;
}
#endif

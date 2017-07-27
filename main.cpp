#include <iostream>
#include "Grafo.hpp"

using namespace std;

int main()
{
  Grafo<char> G;
  Lista<char> vertices, predecesores;

  G.insertarVertice('a');
  G.insertarVertice('b');
  G.insertarVertice('c');
  G.insertarVertice('d');
  G.insertarVertice('f');
  G.insertarVertice('e');

  G.insertarArco('a','f');
  G.insertarArco('a','b');
  G.insertarArco('a','c');
  G.insertarArco('b','d');
  G.insertarArco('c','d');
  G.insertarArco('c','e');
  G.insertarArco('d','a');
  G.insertarArco('d','e');
  G.insertarArco('f','b');

  vertices = G.obtVertices();
  vertices.imprimir();

  G.print();
  predecesores = G.predecesores('b');
  cout << "Predecesores: ";
  predecesores.imprimir();

  cout << "Numero de arcos: " << G.obtNumArcos() << endl;
  cout << "Cardinalidad: " << G.cardinalidad() << endl;
  return 0;
}

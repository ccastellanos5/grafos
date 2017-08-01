#include <iostream>
#include "Grafo.hpp"

using namespace std;

int main()
{
  Grafo<char> G, G2;
  Lista<char> vertices, predecesores;

  G.insertarVerticeO('c');
  G.insertarVerticeO('b');
  G.insertarVerticeO('a');
  G.insertarVerticeO('e');
  G.insertarVerticeO('f');
  G.insertarVerticeO('d');

  G.insertarArco('a','f',0);
  G.insertarArco('a','b',0);
  G.insertarArco('a','c',5);
  G.insertarArco('b','d',0);
  G.insertarArco('c','d',0);
  G.insertarArco('c','e',0);
  G.insertarArco('d','a',0);
  G.insertarArco('d','e',0);
  G.insertarArco('f','b',0);

  cout << "Sali del procedimiento" << endl;
  vertices = G.obtVertices();
  cout << vertices << endl;
  cout << "Cardinalidad: " << G.cardinalidad() << endl;

  cout << G << endl;

  return 0;
}

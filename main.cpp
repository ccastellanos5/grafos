#include <iostream>
#include "Grafo.hpp"

using namespace std;

int main()
{
  Grafo<char> G, G2;
  Lista<char> vertices, predecesores;

  G.insertarVertice('a');
  G.insertarVertice('b');
  G.insertarVertice('c');
  G.insertarVertice('d');
  G.insertarVertice('f');
  G.insertarVertice('e');

  G.insertarArco('a','f',0);
  G.insertarArco('a','b',0);
  G.insertarArco('a','c',5);
  G.insertarArco('b','d',0);
  G.insertarArco('c','d',0);
  G.insertarArco('c','e',0);
  G.insertarArco('d','a',0);
  G.insertarArco('d','e',0);
  G.insertarArco('f','b',0);

  G.DFS('a',vertices);
  vertices.invertir();
  cout << vertices << endl;
  vertices.vaciar();

  G.DFS('c',vertices);
  vertices.invertir();
  cout << vertices << endl;

  cout << G << endl;

  return 0;
}

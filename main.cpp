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

  G.insertarArco('a','f',0);
  G.insertarArco('a','b',0);
  G.insertarArco('a','c',0);
  G.insertarArco('b','d',0);
  G.insertarArco('c','d',0);
  G.insertarArco('c','e',0);
  G.insertarArco('d','a',0);
  G.insertarArco('d','e',0);
  G.insertarArco('f','b',0);


  G.print();

  cout << "Numero de arcos: " << G.obtNumArcos() << endl;
  cout << "Cardinalidad: " << G.cardinalidad() << endl;
  return 0;
}

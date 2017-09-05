#include <iostream>
#include "GrafoND.hpp"

using namespace std;

int main()
{
  GrafoND<char> G, G2;
  Lista<char> vertices, predecesores, lista1, lista2;
  char v, w, esp;


  G.insertarArcoO('A','B',0);
  G.insertarArcoO('A','C',0);
  G.insertarArcoO('B','D',0);
  G.insertarArcoO('D','C',0);
  G.insertarArcoO('E','C',0);

  G.DFS('A', vertices);
  cout << vertices << endl;
  G.print();
  return 0;
}

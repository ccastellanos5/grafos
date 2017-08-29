#include <iostream>
#include "Grafo.hpp"

using namespace std;

int main()
{
  Grafo<char> G, G2;
  Lista<char> vertices, predecesores, lista1, lista2;
  char v, w, esp;

  cin >> v;
  cin.get();
  cin >> w;

  while( v != '*' && w != '*')
  {
    G.insertarArco(v, w, 0);
    cin.get();
    cin >> v;
    cin.get();
    cin >> w;
  }

  vertices = G.sumideros();
  predecesores = G.fuentes();

  cout << "SUMIDEROS:" << endl;
  cout << vertices << endl;

  cout << "FUENTES" << endl;
  cout << predecesores << endl;
  return 0;
}

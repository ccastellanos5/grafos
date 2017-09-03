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
    G.insertarArcoO(v, w, 0);
    cin.get();
    cin >> v;
    cin.get();
    cin >> w;
  }

  G2.copiar(G);
  cout << "CARDINALIDAD DE G: " << G.cardinalidad()<<endl;
  cout << "CARDINALIDAD DE G2: " << G2.cardinalidad()<<endl;

  G.print();
  cout << "----------------------" <<endl;
  G2.print();
  if(G == G2)
  {
    cout<<"SON IGUALES"<< endl;
  }

  return 0;
}

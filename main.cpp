#include <iostream>
#include "Grafo.hpp"

using namespace std;

int main()
{
  Grafo<char> G;

  if(G.esVacio())
    cout << "Vacio";
  else
    cout << "no vacio";

  return 0;
}

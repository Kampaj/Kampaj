#include <iostream>
#include "kolejka.h"
using namespace std;


int main()
{
  int n,m;                        // Liczba wierzcholków i krawedzi
  Edge e;
  TNode * p;
  int i,v;

  cout << "Podaj ilosc wierzcholkow i ilosc krawedzi: ";
  cin >> n >> m;                  // Czytamy liczbe wierzcholków i krawedzi

  Queue Q(m);                     // Kolejka priorytetowa oparta na kopcu
  MSTree T(n);                    // Minimalne drzewo rozpinajace
  MSTree G(n);                    // Graf
  bool * visited = new bool [n];

  for(i = 0; i < n; i++)
    visited[i] = false;           // Inicjujemy tablice odwiedzin

  for(i = 0; i < m; i++)
  {
    cin >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne krawedzie grafu
    G.addEdge(e);                 // i umieszczamy je w G
  }



  //==========================================
  // Tworzymy minimalne drzewo rozpinajace

  v = 0;                          // Wierzcholek startowy
  visited[v] = true;              // Oznaczamy go jako odwiedzonego

  for(i = 1; i < n; i++)          // Do drzewa dodamy (n - 1) krawedzi grafu
  {
    for(p = G.getAList(v); p; p = p->next) // Przegladamy liste sasiadów
      {
          if(!visited[p->v])          // Jezli sasiad jest nieodwiedzony,
            {
                e.v1 = v;                 // to tworzymy krawedz
                e.v2 = p->v;
                e.weight = p->weight;
                Q.push(e);                // Dodajemy ja do kolejki priorytetowej
            }
      }
    do
      {
          e = Q.front();              // Pobieramy krawedz z kolejki
          Q.pop();
      } while(visited[e.v2]);       // Krawedz prowadzi poza drzewo?

    T.addEdge(e);                 // Dodajemy krawedz do drzewa rozpinajacego
    visited[e.v2] = true;         // Oznaczamy drugi wierzcholek jako odwiedzony
    v = e.v2;
  }
  //==========================================




  // Wyswietlamy wyniki
  T.print();

  delete [] visited;

  return 0;
}

#include <iostream>
#include "kolejka.h"
using namespace std;

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementowa tablice heap na kopiec
//---------------------------------------------------------
Queue::Queue(int n)
{
  Heap = new Edge [n];            // Tworzymy tablice
  hpos = 0;                       // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pamieci
//------------------------------------
Queue::~Queue()
{
  delete [] Heap;
}

// Zwraca krawedz z poczatku kopca
//--------------------------------
Edge Queue::front()
{
  return Heap[0];
}

// Umieszcza w kopcu nowa krawedz i odtwarza strukture kopca
//----------------------------------------------------------
void Queue::push(Edge e)
{
  int i,j;

  i = hpos++;                     // i ustawiamy na koniec kopca
  j = (i - 1) >> 1;               // Obliczamy pozycje rodzica

  // Szukamy miejsca w kopcu dla e

  while(i && (Heap[j].weight > e.weight))
  {
    Heap[i] = Heap[j];
    i = j;
    j = (i - 1) >> 1;
  }

  Heap[i] = e;                    // Krawedz e wstawiamy do kopca
}

// Usuwa korzen z kopca i odtwarza jego strukture
//-----------------------------------------------
void Queue::pop()
{
  int i,j;
  Edge e;

  if(hpos)
  {
    e = Heap[--hpos];

    i = 0;
    j = 1;

    while(j < hpos)
    {
      if((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
      if(e.weight <= Heap[j].weight) break;
      Heap[i] = Heap[j];
      i = j;
      j = (j << 1) + 1;
    }

    Heap[i] = e;
  }
}

// Definicje metod obiektu MSTree
//-------------------------------

// Konstruktor - tworzy tablice pustych list sasiedztwa
//-----------------------------------------------------
MSTree::MSTree(int n)
{
  int i;

  A = new TNode * [n];            // Tworzymy tablice dynamiczna
  for(i = 0; i < n; i++) A[i] = NULL; // i wypelniamy ja pustymi listami
  Alen = n - 1;                   // Zapamiêtujemy dlugosc tablicy
  weight = 0;                     // Zerujemy wage drzewa
}

// Destruktor - usuwa listy oraz tablice sasiedztwa
//-------------------------------------------------
MSTree::~MSTree()
{
  int i;
  TNode *p,*r;

  for(i = 0; i <= Alen; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;                      // Zapamietujemy wskazanie
      p = p->next;                // Przesuwamy sie do nastepnego elementu listy
      delete r;                   // Usuwamy element
    }
  }

  delete [] A;                    // Usuwamy tablice list sasiedztwa
}

// Dodaje krawedz do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
  TNode *p;

  p = new TNode;                  // Tworzymy nowy wezel
  p->v = e.v2;                    // Wierzcholek koncowy
  p->weight = e.weight;           // Waga krawedzi
  p->next = A[e.v1];              // Dodajemy p do listy wierzcholka v1
  A[e.v1] = p;

  p = new TNode;                  // To samo dla krawedzi odwrotnej
  p->v = e.v1;                    // Wierzcholek koncowy
  p->weight = e.weight;           // Waga krawedzi
  p->next = A[e.v2];              // Dodajemy p do listy wierzcholka v2
  A[e.v2] = p;
  weight+=e.weight;             // Do wagi drzewa dodajemy wage krawedzi
}

// Zwraca wskaznik poczatku listy sasiadów wierzcholka
//----------------------------------------------------
TNode * MSTree::getAList(int n)
{
  return A[n];
}

// Wyswietla zawartosc drzewa oraz jego wage
//------------------------------------------
void MSTree::print()
{
  int i;
  TNode *p;

  cout << endl;
  for(i = 0; i <= Alen; i++)
  {
    cout << "Wierzcholek " << i << " - ";
    for(p = A[i]; p; p = p->next) cout << i << "-" << p->v << ":" << p->weight << " ";
    cout << endl;
  }
  cout << endl << endl << "Minimalna wielkosc drzewa = " << weight << endl << endl;
}

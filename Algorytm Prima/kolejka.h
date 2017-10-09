#ifndef KOLEJKA_H_INCLUDED
#define KOLEJKA_H_INCLUDED
#include <iostream>
using namespace std;

struct Edge
{
  int v1,v2,weight;               // Wierzcholki krawedzi, waga krawedzi
};

class Queue
{
  private:
    Edge * Heap;
    int hpos;
  public:
    Queue(int n);
    ~Queue();
    Edge front();
    void push(Edge e);
    void pop();
};

// Definicja obiektu minimalnego drzewa rozpinajacego
//---------------------------------------------------
struct TNode
{
  TNode * next;
  int v,weight;
};

class MSTree
{
  private:
    TNode ** A;                   // Tablica list sasiedztwa
    int Alen;                     // Liczba komórek w tablicy
    int weight;                   // Waga calego drzewa
  public:
    MSTree(int n);
    ~MSTree();
    void addEdge(Edge e);
    TNode * getAList(int n);
    void print();
};

#endif // KOLEJKA_H_INCLUDED

//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_NO_H
#define TRABALHOGRAFOS_NO_H



#include <iostream>
#include "Aresta.h"

using namespace std;

class No {
public:
    No() {lista = new Aresta; dIn = 0; dOut = 0; }
    ~No() { delete lista; }


    No* getProx() { return prox; }
    void* setProx(No* p) { prox = p; }
    void setId(int idNo) { id = idNo; }
    int getId() { return id; }
    void addAresta(int idVertice, int idAresta, int peso)
    {lista->insereAresta(idVertice, idAresta, peso); dIn++; dOut++;}
    void removeAresta(int idNo) { lista->removeAresta(idNo); dIn--; dOut--; }
    void imprimeArestas() { cout << "No " << id << " possui arestas com: "; lista->imprimirArestas(); }
    int getGrauEntrada() { return dIn; }
    int getGrauSaida() { return dOut; }


private:
    int id;
    int dIn;
    int dOut;
    float peso;
    No* prox;
    Aresta *lista;
};


#endif //TRABALHOGRAFOS_NO_H

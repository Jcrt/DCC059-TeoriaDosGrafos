//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_GRAFO_H
#define TRABALHOGRAFOS_GRAFO_H


#include "No.h"
#include "Aresta.h"

class Grafo {
public:
    Grafo();
    ~Grafo();

    void insereNo(int idNo);
    void removeNo(int idNo);
    No* busca(int idNo);
    void addAresta(int idVertice1, int idVertice2, int idAresta, int peso);
    void imprimirVertices();
    void imprimirArestas();

private:
    int numeroDeNos;
    int ordem;
    No *primeiro;

};


#endif //TRABALHOGRAFOS_GRAFO_H

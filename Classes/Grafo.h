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
    No* buscaNo(int idNo);
    void addAresta(int idVertice1, int idVertice2, int peso);
    void removeAresta(int idVertice1, int idVertice2);
    void imprimirVertices();
    void imprimirArestas();
    void grauEntrada(int idNo);
    void grauSaida(int idNo);
    bool existeAresta(int idVertice1, int idVertice2);
    bool existeVertice(int idVertice);

private:
    int numeroDeNos;
    No* primeiro;
    No* ultimo;

};


#endif //TRABALHOGRAFOS_GRAFO_H

//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_ARESTA_H
#define TRABALHOGRAFOS_ARESTA_H

#include "Aresta.h"


class ListaArestas {
public:
    ListaArestas();
    ~ListaArestas();

    void insereAresta(int idVerticeOrigem, int idVerticeAdj, int peso);
    void removeAresta(int idNo);
    void setId(int idAresta);
    float getPeso(int idAdj);
    void imprimirArestas();
    bool existeAresta(int idNo);
    Aresta* getPrimeira();
    void removeDoKruskal(Aresta* a);

private:
    Aresta* primeira;
    Aresta* ultima;
    int numeroDeArestas;

};


#endif //TRABALHOGRAFOS_ARESTA_H

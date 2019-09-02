//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_GRAFO_H
#define TRABALHOGRAFOS_GRAFO_H


#include "No.h"
#include "Aresta.h"

class Grafo {
public:
    Grafo(int ordem, bool orientado, bool ponderado_aresta, bool ponderado_vertice);
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
    bool ehPonderadoVertice();
    bool ehPonderadoAresta();
    int getOrdem();

private:
    // variavel para acompanhar o tamanho do grafo no momento que o no eh adicionado.
    int n;
    int ordem;
    No* primeiro;
    No* ultimo;
    bool orientado;
    bool ponderado_aresta;
    bool ponderado_vertice;

};


#endif //TRABALHOGRAFOS_GRAFO_H

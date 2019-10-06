#ifndef TRABALHOGRAFOS_NO_H
#define TRABALHOGRAFOS_NO_H

#include <iostream>
#include "ListaArestas.h"

using namespace std;

class No {
public:
    No(int idNo);
    ~No();

    void addAresta(int idVerticeOrigem, int idVerticeAdj, int peso);
    void removeAresta(int idNo);
    bool existeAresta(int idAdj);
    void imprimeArestas();
    void setProx(No* p);
    No* getProx();
    void setId(int idNo);
    void setIndice(int indice);
    int getIndice();
    int getId();
    int getDIn();
    int getDOut();
    void setPeso(float peso);
    float getPeso() const;
    float getPesoAresta(int idAdj);
    Aresta* getPrimeiraAresta();


private:
    int id;
    float peso;
    int dIn;
    int dOut;
    No* prox;
    ListaArestas *lista;
    int indice;

};


#endif //TRABALHOGRAFOS_NO_H

#ifndef TRABALHOGRAFOS_NO_H
#define TRABALHOGRAFOS_NO_H

#include <iostream>
#include "Aresta.h"

using namespace std;

class No {
public:
    No(int idNo);
    ~No();

    void addAresta(int idVertice, int peso);
    void removeAresta(int idNo);
    bool existeAresta(int idAdj);
    void imprimeArestas();
    void setProx(No* p);
    No* getProx();
    void setId(int idNo);
    int getId();
    int getDIn();
    int getDOut();
    void setPeso(float peso);
    float getPeso() const;


private:
    int id;
    float peso;
    int dIn;
    int dOut;
    No* prox;
    Aresta *lista;

};


#endif //TRABALHOGRAFOS_NO_H

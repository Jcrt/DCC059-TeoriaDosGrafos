//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_ARESTA_H
#define TRABALHOGRAFOS_ARESTA_H


class Aresta {
public:
    Aresta();
    ~Aresta();

    void* insereAresta(int idVertice, int peso);
    void removeAresta(int idNo);
    void setProx(Aresta* p);
    Aresta* getProx();
    void setAdj(int adj);
    int getAdj();
    void setPeso(float pesoAresta);
    void setId(int idAresta);
    void imprimirArestas();
    bool existeAresta(int idNo);

private:
    int id;
    Aresta* primeira;
    Aresta* ultima;
    int numeroDeArestas;
    int noAdj;
    float peso;
    Aresta *prox;
};


#endif //TRABALHOGRAFOS_ARESTA_H

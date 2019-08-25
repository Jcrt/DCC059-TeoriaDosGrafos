//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_ARESTA_H
#define TRABALHOGRAFOS_ARESTA_H


class Aresta {
public:
    Aresta();
    ~Aresta();

    void insereAresta(int idVertice, int idAresta, int peso);
    int getId() {return id;}
    void setProx(Aresta* p) { prox = p; }
    Aresta* getProx() { return prox; }
    void setAdj(int adj) { noAdj = adj; }
    int getAdj() { return noAdj; }
    void setPeso(float pesoAresta) { pesoAresta = peso; }
    void setId(int idAresta) { id = idAresta; }
    void imprimirArestas();

private:
    Aresta* primeira;
    Aresta* ultima;
    int numeroDeArestas;
    int id;
    int noAdj;
    float peso;
    Aresta *prox;
};


#endif //TRABALHOGRAFOS_ARESTA_H

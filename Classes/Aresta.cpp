//
// Created by julio on 24/08/2019.
//

#include <iostream>
#include "Aresta.h"

using namespace std;

/**
 * Construtor das Arestas
 */
Aresta::Aresta() {
    primeira = nullptr;
    ultima = nullptr;
    numeroDeArestas = 0;
}

/**
 * Destrutor das Arestas, deleta todas arestas da memoria.
 */
Aresta::~Aresta() {
    Aresta *p = new Aresta();
    while(p != nullptr){
        Aresta *q = p->getProx();
        delete p;
        p = q;
    }
}

/**
 * Metodo para inserir aresta a partir do vertice atual. Atualmente insere de tras para frente.
 * @param idVertice id do vertice que sera adjacente ao vertice atual.
 * @param idAresta id da aresta.
 * @param peso peso que sera inserido na aresta.
 */
void Aresta::insereAresta(int idVertice, int idAresta, int peso) {
    Aresta* p = new Aresta();
    p->setAdj(idVertice);
    p->setId(idAresta);
    p->setPeso(peso);
    p->setProx(nullptr);

    if(primeira == nullptr){
        primeira = p;
        ultima = p;
    }
    else{
        ultima->setProx(p);
        ultima = p;
    }

    numeroDeArestas++;
}

/**
 * Metodo que imprime as relacoes de arestas do no atual.
 */
void Aresta::imprimirArestas() {
    Aresta* p = primeira;
    while(p != nullptr){
        cout << p->getAdj() << " ";
        p = p->getProx();
    }
    cout << endl;
}
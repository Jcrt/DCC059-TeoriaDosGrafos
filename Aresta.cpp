//
// Created by Leo on 29/09/2019.
//

#include "Aresta.h"

Aresta::Aresta() {
}

Aresta::~Aresta() {
}

void Aresta::setId(int id){
    this->id = id;
}

int Aresta::getId(){
    return this->id;
}

void Aresta::setPeso(int peso) {
    this->peso = peso;
}

void Aresta::setAdj(int idAdj) {
    this->adj = idAdj;
}

void Aresta::setProx(Aresta* p) {
    prox = p;
}

Aresta* Aresta::getProx() {
    return prox;
}

float Aresta::getPeso() {
    return this->peso;
}

int Aresta::getAdj() {
    return this->adj;
}

#include "No.h"

No::No(int idNo) {
    lista = new ListaArestas();
    dIn = 0;
    dOut = 0;
    setId(idNo);
}

No::~No() {
    delete lista;
}


void No::addAresta(int idVerticeOrigem, int idVerticeAdj, int peso) {
    lista->insereAresta(idVerticeOrigem, idVerticeAdj, peso);
}

void No::removeAresta(int idNo){
    lista->removeAresta(idNo);
}

void No::imprimeArestas() {
    cout << "No " << id << " possui arestas com: ";
    lista->imprimirArestas();
}

bool No::existeAresta(int idAdj) {
    if(lista->existeAresta(idAdj))
        return true;
    else
        return false;
}

float No::getPesoAresta(int idAdj) {
     return lista->getPeso(idAdj);
}

int No::getDIn() {
    return dIn;
}

int No::getDOut() {
    return dOut;
}

void No::setPeso(float peso) {
    No::peso = peso;
}

float No::getPeso() const {
    return peso;
}

void No::setProx(No* p) {
    this->prox = p;
}

No* No::getProx() {
    return this->prox;
}

void No::setId(int idNo) {
    this->id = idNo;
}

int No::getId() {
    return this->id;
}

Aresta* No::getPrimeiraAresta() {
    return lista->getPrimeira();
}

void No::setIndice(int indice) {
    this->indice = indice;
}

int No::getIndice() {
    return this->indice;
}

Aresta *No::getAresta(int idAdj) {
    Aresta* a = getAresta(lista->getPrimeira(), idAdj);
}

Aresta* No::getAresta(Aresta* _a, int _idAdj){
    if(_a != nullptr){
        if(_a->getAdj() == _idAdj)
            return _a;
        else
            return getAresta(_a->getProx(), _idAdj);
    }
    return _a;
}

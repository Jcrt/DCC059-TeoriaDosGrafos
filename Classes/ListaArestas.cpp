#include <iostream>
#include "ListaArestas.h"

using namespace std;

/**
 * Construtor das Arestas
 */
ListaArestas::ListaArestas() {
    primeira = nullptr;
    ultima = nullptr;
    numeroDeArestas = 0;

}

/**
 * Destrutor das Arestas, deleta todas arestas da memoria.
 */
ListaArestas::~ListaArestas() {
    Aresta *p = primeira;
    while(p != nullptr){
        Aresta *q = p->getProx();
        delete p;
        p = q;
    }
}

/**
 * Metodo para inserir aresta a partir do vertice atual.
 * @param idVertice id do vertice que sera adjacente ao vertice atual.
 * @param idAresta id da aresta.
 * @param peso peso que sera inserido na aresta.
 */
void ListaArestas::insereAresta(int idVertice, int peso) {
    Aresta* p = new Aresta();
    p->setAdj(idVertice);
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
 * Metodo que remove arestas do vertice passado por parametro. O metodo verifica se a aresta olhada possui o vertice
 * que foi passado como parametro como vertice adjacente. Se possuir faz as devidas remocoes.
 * @param idNo id do vertice que sera excluida aresta.
 */
void ListaArestas::removeAresta(int idNo) {
    Aresta* p = primeira;
    Aresta* aux;
    while(p != nullptr){
        if(p->getAdj() == idNo){
            if(p == primeira){
                if(primeira == ultima){
                    delete primeira;
                    primeira = nullptr;
                    ultima = nullptr;
                    numeroDeArestas--;
                    break;
                }
                else{
                    primeira = primeira->getProx();
                    delete p;
                    numeroDeArestas--;
                    break;
                }
            }
            else{
                aux->setProx(p->getProx());
                if(p == ultima)
                    ultima = aux;
                delete p;
                numeroDeArestas--;
                break;
            }
        }
        aux = p;
        p = p->getProx();
    }
}

/**
 * Metodo que imprime as relacoes de arestas do no atual.
 */
void ListaArestas::imprimirArestas() {
    Aresta* p = primeira;
    while(p != nullptr){
        cout << p->getAdj() << " ";
        p = p->getProx();
    }
    cout << endl;
}

/**
 * Verifica se a aresta entre os vertices ja existe.
 * @param idNo id do segundo vertice.
 * @return true ou false
 */
bool ListaArestas::existeAresta(int idNo) {
    Aresta* p = primeira;
    while(p != nullptr){
        if(p->getAdj() == idNo)
            return true;
        p = p->getProx();
    }
    return false;
}

float ListaArestas::getPeso(int idAdj) {
    Aresta* p = primeira;
    while(p != nullptr ){
        if(p->getAdj() == idAdj)
            return p->getPeso();
        p = p->getProx();
    }
    return 0;
}

Aresta* ListaArestas::getPrimeira(){
    return primeira;
}
//
// Created by julio on 24/08/2019.
//


#include "Grafo.h"


#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;


/**
 * Construtor do Grafo
 */
Grafo::Grafo(){
    cout << "---- CRIANDO GRAFO ----" << endl;
    primeiro = nullptr;
    ordem = 0;
    numeroDeNos = 0;
}

/**
 * Destrutor do grafo, desaloca todos os nos.
 */
Grafo::~Grafo() {
    cout << "---- DESTRUINDO GRAFO ----" << endl;
    No *p = primeiro;
    while (p != nullptr) {
        No *t = p->getProx();
        delete p;
        p = t;
    }
}

/**
 * Metodo para insercao de no (Atualmente fazendo insercao de tras para frente).
 * @param idNo id do no que sera inserido.
 */
void Grafo::insereNo(int idNo) {
    No* p = new No();
    p->setId(idNo);
    p->setProx(nullptr);
    if(primeiro != nullptr){
        p->setProx(primeiro);
        primeiro = p;
    } else{
        primeiro = p;
        primeiro->setProx(nullptr);
    }
    numeroDeNos++;
}

/**
 * Metodo para remover no do grafo (Remove todas arestas contidas naquele no).
 * @param idNo id do novo que sera removido.
 */
void Grafo::removeNo(int idNo) {
    No* p = primeiro;
    No* aux;
    if(primeiro != nullptr){
        while(p != nullptr){
            if(p->getId() == idNo){
                cout << "No " << p->getId()  << " removido" << endl;
                if(p == primeiro) {
                    if (primeiro->getProx() == nullptr) {
                        delete primeiro;
                        primeiro = nullptr;
                        numeroDeNos--;
                    }
                    else{
                        primeiro = primeiro->getProx();
                        delete primeiro;
                        numeroDeNos--;
                    }
                }
                else{
                    if(p->getProx() == nullptr) {
                        delete p;
                        numeroDeNos--;
                    }
                    else{
                        aux->setProx(p->getProx());
                        delete p;
                        numeroDeNos--;
                    }
                }
            }
            else {
                aux = p;
                p = p->getProx();
            }
        }
        for(p = primeiro; p != nullptr; p = p->getProx())
            p->removeAresta(idNo);
    }
    else{
        cout << "GRAFO VAZIO" << endl;
    }
    cout << endl;

}

/**
 * Metodo que adiciona a relacao de aresta entre dois vertices do grafo.
 * @param idVertice1 id do primeiro vertice que deseja adicionar a aresta.
 * @param idVertice2 id do segundo vertice que deseja adicionar a aresta.
 * @param idAresta id da aresta que sera adicionada
 * @param peso peso da aresta que sera adicionada
 */
void Grafo::addAresta(int idVertice1, int idVertice2, int idAresta, int peso) {
    if(busca(idVertice1) == nullptr)
        insereNo(idVertice1);
    if(busca(idVertice2) == nullptr)
        insereNo(idVertice2);

    No* p = busca(idVertice1);
    No* q = busca(idVertice2);
    p->addAresta(idVertice2, idAresta, peso);
    q->addAresta(idVertice1, idAresta, peso);
}

/**
 * Metodo para buscar um vertice no Grafo.
 * @param idNo id do vertice que sera procurado.
 * @return retorna um ponteiro para o vertice ou NULL se nao for encontrado.
 */
No* Grafo::busca(int idNo) {
    No* p = primeiro;
    while(p != nullptr){
        if(p->getId() == idNo)
            return p;
        p = p->getProx();
    }
    return p;
}

/**
 * Metodo que imprime os vertices do Grafo.
 */
void Grafo::imprimirVertices(){
    No* p = primeiro;
    cout << "Nos: ";
    while(p != nullptr){
        cout << p->getId() << " ";
        p = p->getProx();
    }
    cout << endl;
}

/**
 * Metodo que imprime todas relacoes de arestas do grafo.
 */
void Grafo::imprimirArestas() {
    No* p = primeiro;
    while(p != nullptr){
        p->imprimeArestas();
        p  = p->getProx();
    }
    cout << endl;
}

void Grafo::grauEntrada(int idNo) {
    No *p = busca(idNo);
    if (p != nullptr)
        cout << "Grau de entrada do no " << idNo << ": " << p->getGrauSaida() << endl;
    else
        cout << "O no " << idNo << " nao existe." << endl;
    cout << endl;
}

void Grafo::grauSaida(int idNo) {
    No* p = busca(idNo);
    if(p != nullptr)
        cout << "Grau de saida do no "<< idNo << ": " << p->getGrauSaida() << endl;
    else
        cout << "O no "<< idNo << " nao existe." << endl;
    cout << endl;
}
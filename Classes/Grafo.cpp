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
Grafo::Grafo(int ordem, bool orientado, bool ponderado_aresta, bool ponderado_vertice){
    cout << "---- CRIANDO GRAFO ----" << endl;

    primeiro = nullptr;
    ultimo = nullptr;
    this->ordem = ordem;
    this->orientado = orientado;
    this->ponderado_aresta = ponderado_aresta;
    this->ponderado_vertice = ponderado_vertice;
    cout << endl;
}

/**
 * Destrutor do grafo, desaloca todos os nos.
 */
Grafo::~Grafo() {
    cout << endl;
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
    No* p = new No(idNo);
    p->setProx(nullptr);
    if(ultimo != nullptr)
        ultimo->setProx(p);

    ultimo = p;
    ordem++;

    if(ordem == 1)
        primeiro = p;

    cout << "No " << idNo << " adicionado ao Grafo.";
    cout << endl;
}

/**
 * Metodo para remover vertice do grafo. Executa a remocao do vertice desejado e depois verifica todos os nos
 * que possuiam adjacencia com esse vertice e exclui a aresta.
 * @param idNo id do novo que sera removido.
 */
void Grafo::removeNo(int idNo) {
    if(existeVertice(idNo)) {
        No *p = primeiro;
        No *aux;
        if (primeiro != nullptr) {
            while (p != nullptr) {
                if (p->getId() == idNo) {
                    cout << "Vertice " << p->getId() << " removido";
                    if (p == primeiro) {
                        if (primeiro == ultimo) {
                            delete primeiro;
                            primeiro = nullptr;
                            ultimo = nullptr;
                            ordem--;
                        } else {
                            primeiro = primeiro->getProx();
                            delete p;
                            ordem--;
                        }
                    } else {
                        aux->setProx(p->getProx());
                        if(p == ultimo)
                            ultimo = aux;
                        delete p;
                        ordem--;
                    }
                } else {
                    aux = p;
                    p = p->getProx();
                }
            }
            for (p = primeiro; p != nullptr; p = p->getProx())
                p->removeAresta(idNo);
        } else
            cout << "GRAFO VAZIO";
    } else
        cout << "O vertice "<< idNo << " nao pode ser removido pois nao existe.";
    cout << endl;

}

/**
 * Metodo que adiciona a relacao de aresta entre dois vertices do grafo.
 * @param idVertice1 id do primeiro vertice que deseja adicionar a aresta.
 * @param idVertice2 id do segundo vertice que deseja adicionar a aresta.
 * @param idAresta id da aresta que sera adicionada
 * @param peso peso da aresta que sera adicionada
 */
void Grafo::addAresta(int idVertice1, int idVertice2, int peso) {
    if(!existeVertice(idVertice1))
        insereNo(idVertice1);
    if(!existeVertice(idVertice2))
        insereNo(idVertice2);

    No* p = buscaNo(idVertice1);
    No* q = buscaNo(idVertice2);
    p->addAresta(idVertice2, peso);
    q->addAresta(idVertice1, peso);
    cout << "Aresta (" << idVertice1 << ", " << idVertice2 << ") adicionada com peso: " << peso << ".";
    cout << endl;
}

void Grafo::removeAresta(int idVertice1, int idVertice2) {
    if (existeAresta(idVertice1, idVertice2)) {
        cout << "Aresta (" << idVertice1 << ", " << idVertice2 << ") removida.";
        No *p = buscaNo(idVertice1);
        p->removeAresta(idVertice2);
        No *q = buscaNo(idVertice2);
        q->removeAresta(idVertice1);
    }
    else{
        cout << "Nao eh possivel remover a aresta (" << idVertice1 << ", " << idVertice2 << ") pois ela nao existe.";
    }
    cout << endl;
}

/**
 * Metodo para buscar um vertice no Grafo.
 * @param idNo id do vertice que sera procurado.
 * @return retorna um ponteiro para o vertice ou NULL se nao for encontrado.
 */
No* Grafo::buscaNo(int idNo) {
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
    cout << endl;
    No* p = primeiro;
    while(p != nullptr){
        p->imprimeArestas();
        p  = p->getProx();
    }
    cout << endl;
}

bool Grafo::existeVertice(int idVertice){
    No* p = buscaNo(idVertice);
    if(p != nullptr)
        return true;
    else
        return false;
}

bool Grafo::existeAresta(int idVertice1, int idVertice2) {
    No* p = buscaNo(idVertice1);
    No* q = buscaNo(idVertice2);
    if(p != nullptr && q != nullptr)
        if(p->existeAresta(idVertice2) && q->existeAresta(idVertice1))
            return true;
        else
            return false;
    else
        return false;
}


/**
 * Imprime o grau de entrada do vertice informado.
 * @param idNo id do vertice que deseja saber o grau de entrada.
 */
void Grafo::grauEntrada(int idNo) {
    No *p = buscaNo(idNo);
    if (p != nullptr)
        cout << "Grau de entrada do no " << idNo << ": " << p->getDIn() << endl;
    else
        cout << "O no " << idNo << " nao existe." << endl;
    cout << endl;
}

/**
 * Imprime o grau de saida do vertice informado.
 * @param idNo id do vertice que deseja saber o grau de saida.
 */
void Grafo::grauSaida(int idNo) {
    No* p = buscaNo(idNo);
    if(p != nullptr)
        cout << "Grau de saida do no "<< idNo << ": " << p->getDOut() << endl;
    else
        cout << "O no "<< idNo << " nao existe." << endl;
    cout << endl;
}

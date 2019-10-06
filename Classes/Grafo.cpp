#include "Grafo.h"

#include <chrono>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <stack>
#include <list>
#include <climits>
#include <fstream>

using namespace std;

/**
 * Construtor do Grafo
 */
Grafo::Grafo(int ordem, bool orientado, bool ponderado_aresta, bool ponderado_vertice) {
    cout << "---- CRIANDO GRAFO ----" << endl;

	primeiro = nullptr;
	ultimo = nullptr;
	this->ordem = ordem;
	this->orientado = orientado;
	this->ponderado_aresta = ponderado_aresta;
	this->ponderado_vertice = ponderado_vertice;
	this->n = 0;
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
* Função que verifica se o vetor é false em todas as posições
* @param vet bool com os indices dos nos do grafo
* @param n int com o tamanho do vetor
* @return false se todas as posicoes sao false ou true se encontrado ao menos um true
*/
bool Grafo::verificaVisit(bool vet[], int n) // funcao que verifica se todos os indicies do vetor foram visitados
{
    for(int i = 0; i < n; i++)
        if(!vet[i])
            return false;
    return true;
}


/**
 * Busca os nos adjacentes ao passado como parametro e tras quais sao os adjacentes por nivel em largura.
 * @param s vertice 1
 */
void Grafo::buscaEmLargura(int s){
    ofstream arqSaida;
    arqSaida.open("../Saidas.txt", ofstream::ios_base::app);
    arqSaida << endl << "Busca em largura: ";
    No* p = buscaNo(s);
    if(p == nullptr)
        return;

    bool visita[n];
    for(int i = 0; i < n; i++)
        visita[i] = 0;

    list<int> queqe;
    queqe.push_back(s);
    visita[p->getIndice()] = true;
    cout << p->getId() << " ";
    arqSaida << p->getId() << " ";


    Aresta* a;
    while(!queqe.empty()){
        a = p->getPrimeiraAresta();
        while(a != nullptr){
            No* aux = buscaNo(a->getAdj());
            int indice = aux->getIndice();
            int i = 1;
            if(!visita[indice]){
                arqSaida << aux->getId() << " ";
                cout << aux->getId() << " ";
                visita[indice] = true;
                queqe.push_back(aux->getId());
                p = buscaNo(queqe.front());
                a = p->getPrimeiraAresta();
            } else
                a = a->getProx();
        }
        queqe.pop_front();
        if(!queqe.empty())
            p = buscaNo(queqe.front());
    }


    cout << endl;

}



/**
* Algoritmo de Dijkstra para encontrar menor caminho entre dois vertices
* @param v int com o no inicial
* @param vN int com o no destino
* @return dist[vN] com a distancia entre os dois nos passados por parâmetro
*/
void Grafo::menorCaminhoDijkstra(int v, int vN){
    No* p = buscaNoIndice(v-1);
    No* q = buscaNoIndice(vN-1);
    No* aux;
    int indice;
    ofstream arqSaida;
    arqSaida.open("../Saidas.txt", ofstream::ios_base::app);
    if(p != nullptr && q != nullptr){
        int menor;

        int dist[n], pre[n];
        bool visit[n];
        for(int i = 0; i < n; i++){
            dist[i] = INT_MAX/2;
            pre[i] = -1;
            visit[i] = false;
        }
        dist[p->getIndice()] = 0;
        pre[p->getIndice()]=0;

        while(!verificaVisit(visit, n)){
            if(!visit[p->getIndice()]){
                visit[p->getIndice()] = true;
                Aresta* a = p->getPrimeiraAresta();
                if(a != nullptr){
                    while(a != nullptr){
                        if(a->getPeso() >= 0)
                            aux = buscaNo(a->getAdj());
                        indice = aux->getIndice();
                        if(dist[indice] > dist[p->getIndice()] + a->getPeso()){
                            dist[indice] = dist[p->getIndice()] + a->getPeso();
                            pre[indice] = p->getId();
                        }
                        a = a->getProx();
                    }
                }
                int i=0;
                for(i = 0; i < n; i++){
                    if(!visit[i])
                        break;
                    if(i == n-1){
                        cout << endl;
                        cout << "Menor Caminho(Dijkstra) entre " << v << " e " << vN << " e: " << dist[vN-1] << endl;
                        arqSaida << endl << "Menor Caminho(Dijkstra) entre " << v << " e " << vN << " : " << dist[vN-1] << endl;
                    }
                }
                menor = i;
                for(i = menor; i < n; ++i){
                    if(!visit[i] && dist[menor] >= dist[i])
                        menor = i;
                }
                p = buscaNoIndice(menor);
            }
        }
        if(dist[vN] == INT_MAX/2) {
            cout << endl << "Nao existe caminho entre os vertices." << endl;
            arqSaida << endl << "Nao existe caminho entre os vertices. " << endl;
        }
    }
    else{
        cout << "Vertice " << v << " ou "<< vN << " nao encontrados no grafo! (ERRO)" << endl;
        arqSaida << endl << "Vertice " << v << " ou "<< vN << " nao encontrados no grafo! (ERRO)-Algoritmo Dijkstra" << endl;
    }
}


/**
 * Algoritmo de busca em profundindade, passando por todos nós como origem e por todas as arestas dos nós.
 * @param idVertice id do vertice de inicio.
 */
void Grafo::buscaProfundidade(int idVertice){
    ofstream arqSaida;
    arqSaida.open("../Saidas.txt", ofstream::ios_base::app);
    arqSaida << endl <<  "Busca em profundidade: ";
    No* p = buscaNo(idVertice);
    if(p == nullptr)
        return;

    bool visita[n];
    for(int i = 0; i < n; i++)
        visita[i] = 0;

    stack<int> pilha;
    pilha.push(idVertice);
    visita[p->getIndice()] = true;
    cout << p->getId() << " ";
    arqSaida << p->getId() << " ";

    Aresta* a;
    while(!pilha.empty()){
        a = p->getPrimeiraAresta();
        while(a != nullptr){
            No* aux = buscaNo(a->getAdj());
            int indice = aux->getIndice();
            if(!visita[indice]){
                arqSaida << aux->getId() << " ";
                cout << aux->getId() << " ";
                visita[indice] = true;
                pilha.push(aux->getId());
                p = buscaNo(pilha.top());
                a = p->getPrimeiraAresta();
            } else
                a = a->getProx();
        }
        pilha.pop();
        if(!pilha.empty())
            p = buscaNo(pilha.top());
    }
    cout << endl;
}


/**
 * Busca o menor caminho entre dois vertices através de uma matriz que é atualizada com os menores valores.
 * @param a vertice 1
 * @param b vertice 2
 */
void Grafo::algFloyd(int a, int b) {
    ofstream f;
    f.open("../Saidas.txt", ofstream::ios_base::app);
    if(existeVertice(a) && existeVertice(b)) {
        int **mat = new int *[n];
        No* p;

        for (int i = 0; i < n; i++) {
            mat[i] = new int[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    mat[i][j] = 0;
                else {
                    p = buscaNo(i+1);
                    if(p == nullptr)
                        break;
                    mat[i][j] = p->getPesoAresta(j+1);
                }
            }
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (mat[i][j] > mat[i][k] + mat[k][j] && mat[i][k] + mat[k][j] > 0)
                        mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }

        f << endl << "Menor Caminho(Floyd) entre " << a << " e " << b << " : " << mat[a-1][b-1] << endl;
        cout << endl << "Menor Caminho(Floyd) entre " << a << " e " << b << " : " << mat[a-1][b-1] << endl;

        for (int i = 0; i < n; i++)
            delete[] mat[i];

        delete[]mat;

    } else{
        f << endl << "Vertices Invalidos (ERRO)-Algoritmo Floyd" << endl;
        cout << endl << "Vertices Invalidos (ERRO)-Algoritmo Floyd" << endl;
    }
    f.close();
}

/**
 * Metodo para insercao de no (Atualmente fazendo insercao de tras para frente).
 * @param idNo id do no que sera inserido.
 */
void Grafo::insereNo(int idNo) {
    No* p = new No(idNo);
    p->setProx(nullptr);
    p->setIndice(this->n);
    if(ultimo != nullptr)
        ultimo->setProx(p);

    ultimo = p;
    n++;

    if(n == 1)
        primeiro = p;

    //cout << "No " << idNo << " adicionado ao Grafo.";
    //cout << endl;
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
                            No* q = primeiro;
                            // Reduz o indice dos vertices que estavam na frente
                            while(q!= nullptr){
                                q->setIndice(q->getIndice()-1);
                                q = q->getProx();
                            }
                            delete p;
                            ordem--;
                        }
                    } else {
                        aux->setProx(p->getProx());
                        // Reduz o indice dos vertices que estavam na frente
                        while(aux->getProx() != nullptr){
                            aux->getProx()->setIndice(aux->getProx()->getIndice()-1);
                            aux = aux->getProx();
                        }
                        if(p == ultimo)
                            ultimo = aux;
                        delete p;
                        ordem--;
						break;
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
    /*Se o grafo é orientado, apenas o vértice 1 recebe o ponteiro pro vertice 2*/
    if (!this->orientado) {
        q->addAresta(idVertice1, peso);
        //cout << "ListaArestas (" << idVertice1 << ", " << idVertice2 << ") adicionada com peso: " << peso << ".";
    } else {
        //cout << "ListaArestas (" << idVertice1 << " -> " << idVertice2 << ") adicionada com peso: " << peso << ".";
    }

    //cout << endl;
}


/**
 * O metodo para remover uma aresta entre dois vertices verifica se primeiro se essa aresta existe
 * e, caso exista faz a remocao da aresta. (Caso seja orientado, apenas 1 no possui a aresta, entao so é
 * removida dele).
 * @param idVertice1
 * @param idVertice2
 */
void Grafo::removeAresta(int idVertice1, int idVertice2) {
    if (existeAresta(idVertice1, idVertice2)) {
        cout << "ListaArestas (" << idVertice1 << ", " << idVertice2 << ") removida.";
        No *p = buscaNo(idVertice1);
        p->removeAresta(idVertice2);

        /* Se o grafo é orientado, apenas o vértice 1 recebe o ponteiro pro vertice 2*/
        if(!this->orientado){
            No *q = buscaNo(idVertice2);
            q->removeAresta(idVertice1);
        }
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
    No *p = primeiro;
    while (p != nullptr) {
        if (p->getId() == idNo)
            return p;
        p = p->getProx();
    }
    return p;

}

/**
 * Metodo para buscar um vertice no Grafo pelo indice do vertice.
 * @param indice indice do vertice que sera procurado.
 * @return retorna um ponteiro para o vertice ou NULL se nao for encontrado.
 */
No* Grafo::buscaNoIndice(int indice) {
        No *p = primeiro;
        while (p != nullptr) {
            if (p->getIndice() == indice)
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

/**
 * Verifica se o vertice existe.
 * @param idVertice
 * @return true ou false
 */
bool Grafo::existeVertice(int idVertice){
    No* p = buscaNo(idVertice);
    if(p != nullptr)
        return true;
    else
        return false;
}

/**
 * Verifica se aresta existe.
 * @param idVertice1
 * @param idVertice2
 * @return true ou false.
 */
bool Grafo::existeAresta(int idVertice1, int idVertice2) {
    bool result = false;
    No* p = buscaNo(idVertice1);
    No* q = buscaNo(idVertice2);

    if(p != nullptr && q != nullptr){
        if(p->existeAresta(idVertice2) && this->orientado){
            result = true;
        } else if(p->existeAresta(idVertice2) && q->existeAresta(idVertice1) && !this->orientado) {
            result = true;
        }
    }

    return result;
}


/**
 * Retorna o peso da aresta entre os vertices buscados por indice.
 * @param indice1 vertice 1
 * @param indice2 vertice 2
 * @return peso da aresta.
 */
float Grafo::getPesoArestaIndice(int indice1, int indice2){
    No* p = buscaNoIndice(indice1);
    No* q = buscaNoIndice(indice2);
    if(p != nullptr && q != nullptr) {
        int idVertice1 = p->getId();
        int idVertice2 = q->getId();

        if (existeAresta(idVertice1, idVertice2)) {
            return p->getPesoAresta(idVertice2);
        } else
            return 9999999;
    }
    else
        return 9999999;

}


/**
 * Retorna o peso da aresta entre os vertices idVertice1 e idVertice2
 * @param idVertice1 vertice 1
 * @param idVertice2 vertice 2
 * @return peso da aresta.
 */
float Grafo::getPesoAresta(int idVertice1, int idVertice2) {
    if(existeAresta(idVertice1, idVertice2)) {
        No *p = buscaNo(idVertice1);
        return p->getPesoAresta(idVertice2);
    }
    else
        return 0;

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

bool Grafo::ehPonderadoAresta() {
    return this->ponderado_aresta;
}

bool Grafo::ehPonderadoVertice() {
    return this->ponderado_vertice;
}

int Grafo::getOrdem() {
    return this->ordem;
}
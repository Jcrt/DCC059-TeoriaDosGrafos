#include "Grafo.h"
#include <iostream>
#include <stack>
#include <list>
#include <climits>
#include <fstream>
#include <vector>
#include <algorithm>

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
bool Grafo::verificaVisit(bool vet[], int n) {
    for(int i = 0; i < n; i++)
        if(!vet[i])
            return false;
    return true;
}

/**
* Algoritmo de Dijkstra para encontrar menor caminho entre dois vertices
* @param v int com o no inicial
* @param vN int com o no destino
* @return dist[vN] com a distancia entre os dois nos passados por parâmetro
*/
void Grafo::menorCaminhoDijkstra(int v, int vN, char* caminhoArqSaida){
    No* p = buscaNoIndice(v-1);
    No* q = buscaNoIndice(vN-1);
    No* aux;
    int indice;
    ofstream arqSaida;
    arqSaida.open(caminhoArqSaida, ofstream::ios_base::app);
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
            arqSaida << endl << "Nao existe caminho entre os vertices. " << endl;
        }
    }
    else{
        arqSaida << endl << "Vertice " << v << " ou "<< vN << " nao encontrados no grafo! (ERRO)-Algoritmo Dijkstra" << endl;
        //return -1;
    }
    cout << endl;
    arqSaida << endl;
}

/**
 * Busca os nos adjacentes ao passado como parametro e tras quais sao os adjacentes por nivel em largura.
 * @param s vertice 1
 */
void Grafo::buscaEmLargura(int s, char* arqSaida){
    ofstream file;
    file.open(arqSaida, ofstream::ios_base::app);
    file << endl << "Busca em largura: ";
    No* p = buscaNo(s);
    if(p == nullptr)
        return;

    bool visita[n];
    for(int i = 0; i < n; i++)
        visita[i] = 0;

    list<int> queqe;
    queqe.push_back(s);
    visita[p->getIndice()] = true;
    file << p->getId() << " ";


    Aresta* a;
    while(!queqe.empty()){
        a = p->getPrimeiraAresta();
        while(a != nullptr){
            No* aux = buscaNo(a->getAdj());
            int indice = aux->getIndice();
            int i = 1;
            if(!visita[indice]){
                file << aux->getId() << " ";
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
    file << endl;
}

/**
 * Algoritmo de busca em profundindade, passando por todos nós como origem e por todas as arestas dos nós.
 * @param idVertice id do vertice de inicio.
 */
void Grafo::buscaProfundidade(int idVertice, char* caminhoArqSaida){
    ofstream arqSaida;
    arqSaida.open(caminhoArqSaida, ofstream::ios_base::app);
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
    arqSaida << p->getId() << " ";

    Aresta* a;
    while(!pilha.empty()){
        a = p->getPrimeiraAresta();
        while(a != nullptr){
            No* aux = buscaNo(a->getAdj());
            int indice = aux->getIndice();
            if(!visita[indice]){
                arqSaida << aux->getId() << " ";
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
    arqSaida << endl;
}

/**
 * Busca o menor caminho entre dois vertices através de uma matriz que é atualizada com os menores valores.
 * @param a vertice 1
 * @param b vertice 2
 */
void Grafo::algFloyd(int a, int b, char* caminhoArqSaida) {
    ofstream f;
    f.open(caminhoArqSaida, ofstream::ios_base::app);
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

        for (int i = 0; i < n; i++)
            delete[] mat[i];

        delete[]mat;

    } else{
        f << endl << "Vertices Invalidos (ERRO)-Algoritmo Floyd" << endl;
    }
    f.close();
}

/**
 * Retorna a lista de todas as arestas do grafo.
 * @param _no - Nó de entrada do algoritmo (pois ele pesquisa as arestas por nó, de forma recursiva)
 * @param _isSorted - Em caso de true, ordena as arestas crescentemente pelo peso
 * @return Lista de arestas ordenadas ou não
 */
vector<Aresta*> Grafo::GetAllArestas(No* _no, bool _isSorted, bool _isRecursive){
    vector<Aresta*> AllArestas;
    Aresta* aresta = _no->getPrimeiraAresta();

    if(_isRecursive){
        if(_no->getProx() != nullptr)
            AllArestas = GetAllArestas(_no->getProx(), true);
    }

    if(aresta != nullptr){
        do{
            AllArestas.push_back(aresta);
            aresta = aresta->getProx();
        }while(aresta != nullptr);
    }

    if(AllArestas.size() >= 2 && _isSorted)
        sort(AllArestas.begin(), AllArestas.end(), CompareArestas);

    return AllArestas;
}

/**
 * Compara os pesos da aresta
 * @param a - aresta 1
 * @param b - aresta 2
 * @return - bool com verificação de qual aresta tem mais peso
 */
bool Grafo::CompareArestas(Aresta* a, Aresta* b){
    return a->getPeso() < b->getPeso();
}

/**
 * Retorna todos os nós do grafo
 * @param _no - Nó de entrada na função
 * @param _isSorted - Se passado true, ordena os nós do grafo por peso
 * @return - Lista com todos os nós do grafo
 */
vector<No*> Grafo::GetAllNos(No * _no, bool _isSorted){
    vector<No*> allNos;
    if(_no->getProx() != nullptr)
        allNos = GetAllNos(_no->getProx(), true);
    allNos.push_back(_no);
    if(_isSorted)
        sort(allNos.begin(), allNos.end(), CompareNos);
    return allNos;
}

/**
 * Retorna se um determinado nó tem peso maior que o do outro nó
 * @param a - Nó do grafo
 * @param b - Nó do grafo
 * @return - Bool com resultado da comparação de pesos
 */
bool Grafo::CompareNos(No* a, No* b){
    return a->getPeso() < b->getPeso();
}

void Grafo::Prim(char* caminhoArqSaida){
    ofstream f;
    f.open(caminhoArqSaida, ofstream::ios_base::app);
    vector<No*> inSolution;
    vector<No*> outSolution;
    vector<Aresta*> allArestas;
    vector<Aresta*> arestasNaSolucao;
    Aresta* arestaMenorPeso = nullptr;
    bool isGeraFloresta = false;
    int LoopLimit = 0;

    //Trago lista de arestas ordenadas e pego a aresta de menor peso (que sempre estará na solução)
    allArestas = GetAllArestas(this->primeiro, true);
    outSolution = GetAllNos(this->primeiro, true);

    //Insiro o nó de origem da aresta de menor peso na lista de soluções
    No* n1 = this->buscaNo(allArestas[0]->getId());
    inSolution.push_back(n1);
    outSolution = RemoveNoFromVector(outSolution, n1);

    //Busco o nó adjascente à aresta de menor peso
    No* n2 = this->buscaNo(allArestas[0]->getAdj());
    inSolution.push_back(n2);
    outSolution = RemoveNoFromVector(outSolution, n2);

    //Coloca a primeira aresta na solução
    arestasNaSolucao.push_back(allArestas[0]);

    while(outSolution.size() > 0 && LoopLimit <= 3) {
        arestaMenorPeso = nullptr;
        LoopLimit++;

        if(!isGeraFloresta){
            for (int i = 0; i < inSolution.size(); i++) {
                Aresta* aux = MenorArestaNo(inSolution[i]->getPrimeiraAresta(), inSolution);
                if(aux != nullptr && (arestaMenorPeso == nullptr || (arestaMenorPeso != nullptr && arestaMenorPeso->getPeso() > aux->getPeso())))
                    arestaMenorPeso = aux;
            }
        }
        else {
            for (int i = 0; i < outSolution.size(); i++) {
                Aresta* aux = MenorArestaNo(outSolution[i]->getPrimeiraAresta(), inSolution);
                if(aux != nullptr && (arestaMenorPeso == nullptr || (arestaMenorPeso != nullptr && arestaMenorPeso->getPeso() > aux->getPeso())))
                    arestaMenorPeso = aux;
            }
        }

        if(arestaMenorPeso != nullptr){
            No* newNo = this->buscaNo(arestaMenorPeso->getAdj());
            inSolution.push_back(newNo);
            outSolution = RemoveNoFromVector(outSolution, newNo);
            arestasNaSolucao.push_back(arestaMenorPeso);
            isGeraFloresta = false;
            LoopLimit = 0;
        } else{
            isGeraFloresta = true;
        }
    }

    if(LoopLimit > 3) {
        f << "Grafo não construído. O algoritmo não conseguiu contemplar todos os nós" << endl;
    } else {
        f << "Arestas na solução (PRIM): " << endl;
        for(int i = 0; i < arestasNaSolucao.size(); i++){
           f << "Do no " << arestasNaSolucao[i]->getId() << " para o no " << arestasNaSolucao[i]->getAdj() << " com peso " << arestasNaSolucao[i]->getPeso() <<endl;
        }
    }
    f << endl;
    cout << endl;
}
/**
 * Faz uma arvore geradora minima ou se o grafo for conexo ou
 * faz florestas se o grafo for desconexo
 */
void Grafo::kruskal(char* caminhoArqSaida) {
    ofstream arqSaida;
    arqSaida.open(caminhoArqSaida, ofstream::ios_base::app);
    if(n != 0){
        No* p = primeiro;
        int vetArvores[n];
        bool visitado[n];
        bool condicao[n];
        Aresta* a = p->getPrimeiraAresta();
        ListaArestas* lista = new ListaArestas();

        for(int i = 0; i < n; i++){
            vetArvores[i] = p->getId();
            condicao[i] = false;
            visitado[i] = false;
                        p = p->getProx();
        }
        p = primeiro;

        /// percorro todas as arestas do grafo e inserindo na lista com seus respectivos Id e o adjacente e o peso, para
        /// ordenarmos o menor peso.

        while(p != NULL){
            while(a != NULL){
                if(!visitado[a->getId()])
                    lista->insereAresta(a->getId(), a->getAdj(), a->getPeso());
                a = a->getProx();
            }
            visitado[p->getId()] = true;
            p = p->getProx();
            if(p != NULL)
                a = p->getPrimeiraAresta();
        }

        ///percorro a lista de arestas partindo da primeira aresta em busca do menor caminho separadamente que vai juntando
        /// uma unica componente conexa de peso minimo, imprimo a lista das arestas com seu peso e insercao na arvore.
        p = primeiro;
        a = lista->getPrimeira();
        int cont = 0;
        arqSaida << endl <<  "Arvore de Kruskal: " << endl;
        while(lista != nullptr && cont != n-1){
            if(condicao[lista->getPrimeira()->getId()] && condicao[lista->getPrimeira()->getAdj()])
                lista->removeDoKruskal(lista->getPrimeira());
            else{
                if(lista->getPrimeira()->getAdj() >= lista->getPrimeira()->getId()){
                    arqSaida <<  "Aresta de " << lista->getPrimeira()->getId() << " para " << lista->getPrimeira()->getAdj() << " peso: " << lista->getPrimeira()->getPeso() << endl;
                    condicao[lista->getPrimeira()->getId()] = true;
                    lista->removeDoKruskal(lista->getPrimeira());
                    cont++;
                }
                else{
                    arqSaida << "Aresta de " << lista->getPrimeira()->getAdj() << " para " << lista->getPrimeira()->getId() << " peso: " << lista->getPrimeira()->getPeso() << endl;
                    condicao[lista->getPrimeira()->getId()] = true;
                    lista->removeDoKruskal(lista->getPrimeira());
                    cont++;
                }
            }

        }
        if(lista != nullptr && cont != n-1)
            arqSaida << "Numero de aresta na solucao: " << cont << endl;
        arqSaida <<  "Numero de vertices: " << cont+1 << endl;

        arqSaida.close();
        delete lista;
    }
    arqSaida << endl;
}

Aresta* Grafo::MenorArestaNo(Aresta* _aresta, vector<No*> _inSolution){
    Aresta* aux = nullptr;

    if(_aresta != nullptr)
        if(_aresta->getProx() != nullptr)
            aux = MenorArestaNo(_aresta->getProx(), _inSolution);

    for(int i = 0;  i < _inSolution.size(); i++){
        if(_aresta != nullptr && _aresta->getAdj() == _inSolution[i]->getId())
            _aresta = nullptr;
        if(aux != nullptr && aux->getAdj() == _inSolution[i]->getId())
            aux = nullptr;
    }

    if(_aresta == nullptr || (aux != nullptr && _aresta != nullptr && aux->getPeso() < _aresta->getPeso()))
        _aresta = aux;

    return _aresta;
}

vector<No*> Grafo::RemoveNoFromVector(vector<No*> _vector, No* _target){
    auto objPointer = find(_vector.begin(), _vector.end(), _target);
    if(objPointer != _vector.end()){
        _vector.erase(objPointer);
    }
    return _vector;
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

    p->addAresta(idVertice1, idVertice2, peso);
    /*Se o grafo é orientado, apenas o vértice 1 recebe o ponteiro pro vertice 2*/
    if (!this->orientado) {
        q->addAresta(idVertice2, idVertice1, peso);
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

No *Grafo::GetPrimeiroNo() {
    return this->primeiro;
}
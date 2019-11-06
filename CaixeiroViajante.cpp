//
// Created by julio on 05/11/2019.
//

#include <fstream>
#include "CaixeiroViajante.h"
#include "Grafo.h"
#include <math.h>
using namespace std;

/***
 * Faz a leitura do arquivo que contém o grafo do caixeiro viajante e constrói um grafo
 * @param _filename o caminho completo do arquivo
 * @return um ponteiro apontando para o grafo construido
 */
Grafo* CaixeiroViajante::BuildTSPGraphFromFile(string _filename){
    No* no;
    int ordem, idNo, coordx, coordy;
    vector<LinhaArquivoCV> linhasArquivo;

    //Lê a primeira linha do grafo para determinar a ordem e construir o grafo
    ifstream file;
    file.open(_filename);
    file >> ordem;

    //Instancia o grafo
    Grafo* grafo = new Grafo(ordem, 0, 1, 0);;

    /*Percorre todo o arquivo para gerar as linhas e, ao mesmo tempo que as guarda numa lista, cria os nós*/
    while(file >> idNo >> coordx >> coordy){
        linhasArquivo.push_back(
                LinhaArquivoCV{idNo = idNo, coordx = coordx, coordy = coordy}
        );
        grafo->insereNo(idNo);
    }

    //fecha o arquivo
    file.close();

    /*Percorre a lista de arestas duas vezes, uma para pegar nó por nó e outra
     * para criar as arestas, pois o problema do caixeiro viajante é sobre um grafo completo,
     * com peso nas arestas e não orientado
     * */
    for (int i = 0; i < linhasArquivo.size(); i++) {
        no = grafo->buscaNo(linhasArquivo[i].idNo);
        for(int j = 0; j < linhasArquivo.size(); j++){
            if(no->getId() != linhasArquivo[j].idNo){
                //Calcula a distancia euclideana no grafo
                int euclideanDistance = CaixeiroViajante::GetEuclideanDistance(
                    linhasArquivo[i].coordx, linhasArquivo[i].coordy,
                    linhasArquivo[j].coordx, linhasArquivo[j].coordy
                );

                //Adiciona a nova aresta
                no->addAresta(no->getId(), linhasArquivo[j].idNo, euclideanDistance);
                cout << "Aresta de " << no->getId() << " para " << linhasArquivo[j].idNo << " custa " << euclideanDistance << endl;
            }
        }
    }

    return grafo;
}

/**
 * Função que calcula a distancia euclidiana entre as arestas
 * @param _xa Posição x do nó a
 * @param _ya Posição y do nó a
 * @param _xb Posição x do nó b
 * @param _yb Posição y do no b
 * @return Inteiro positivo representando a distancia
 */
int CaixeiroViajante::GetEuclideanDistance(int _xa, int _ya, int _xb, int _yb){
    int x = pow(_xa - _xb, 2);
    int y = pow(_ya - _yb, 2);
    int result = sqrt(x + y);
}

/***
 * Constrói uma lista de arestas que faz a representação do grafo de menor custo do caixeiro viajante, abordagem gulosa
 * @param _grafo O grafo que contém a instância do problema
 * @return Lista de arestas que formam o grafo de menor custo
 */
vector<Aresta* > CaixeiroViajante::GetBetterCostG(Grafo* _grafo){
    No* pontaDireita;
    No* pontaEsquerda;
    Aresta* menorArestaPontaDireita;
    Aresta* menorArestaPontaEsquerda;
    Aresta* arestaCorrente;
    No* noCorrente;

    vector<No*> noInSolution;
    vector<Aresta*> arestasInSolution;

    //Pego todos os nós do grafo e indico que estão fora da solução
    vector<No*> noOutSolution = _grafo->GetAllNos(_grafo->GetPrimeiroNo(), false);

    //Pra transformar em randomizado, mudar aqui para pegar a primeira aresta randomizada;
    //Pego a menor aresta do grafo para iniciar a construção e a insiro na lista de arestas na solução
    Aresta* menorAresta = _grafo->GetAllArestas(_grafo->GetPrimeiroNo(), true)[0];
    arestaCorrente = menorAresta;
    arestasInSolution.push_back(arestaCorrente);

    //Defino os nós de 'ponta direita' e 'ponta esquerda' do caminho como sendo os dois nós que compoem a primeira aresta
    pontaDireita = _grafo->buscaNo(arestaCorrente->getId());
    pontaEsquerda = _grafo->buscaNo(arestaCorrente->getAdj());

    //Incluo o nó da ponta direita nos nós da solução e removo o nó da ponta direita dos nós que estão fora da solução
    noInSolution.push_back(pontaDireita);
    noOutSolution = _grafo->RemoveNoFromVector(noOutSolution, pontaDireita);
    cout << "Nó " << pontaDireita->getId() << " na ponta direita"<< endl;

    //Incluo o nó da ponta esquerda nos nós da solução e removo o nó da ponta esquerda dos nós que estão fora da solução
    noInSolution.push_back(pontaEsquerda);
    noOutSolution = _grafo->RemoveNoFromVector(noOutSolution, pontaEsquerda);
    cout << "Nó " << pontaEsquerda->getId() << " na ponta esquerda"<< endl;

    //Enquanto eu tiver ítens fora da solução, faço...
    while(noOutSolution.size() > 0){

        //Para transformar em randomizado, mudar aqui para pegar as arestas de cada nó randomizadas
        //Pego as menores arestas da ponta esquerda e da ponta direita
        menorArestaPontaDireita = _grafo->MenorArestaNo(pontaDireita->getPrimeiraAresta(), noInSolution);
        menorArestaPontaEsquerda = _grafo->MenorArestaNo(pontaEsquerda->getPrimeiraAresta(), noInSolution);

        //Verifico qual aresta é menor e, então, assumo que essa é a aresta corrente e insiro na solução
        if(menorArestaPontaDireita->getPeso() <= menorArestaPontaEsquerda->getPeso())
            arestaCorrente = menorArestaPontaDireita;
        else
            arestaCorrente = menorArestaPontaEsquerda;
        arestasInSolution.push_back(arestaCorrente);

        //Busco o nó adjascente à aresta que acabou de entrar para compor a solução e removo este nó da lista de nós fora da solução
        noCorrente = _grafo->buscaNo(arestaCorrente->getAdj());
        noInSolution.push_back(noCorrente);
        noOutSolution = _grafo->RemoveNoFromVector(noOutSolution,noCorrente);
        cout << "Aresta entre " << arestaCorrente->getId() << " e " << arestaCorrente->getAdj() << " com custo " << arestaCorrente->getPeso() << " inserida" << endl;

        //Verifico qual ponta será atualizada baseado no id da aresta corrente
        if(arestaCorrente->getId() == pontaDireita->getId()){
            cout << "Substituindo nó " << pontaDireita->getId() << " por " << noCorrente->getId() << " na ponta direita" << endl;
            pontaDireita = noCorrente;
        } else{
            cout << "Substituindo nó " << pontaEsquerda->getId() << " por " << noCorrente->getId() << " na ponta esquerda" << endl;
            pontaEsquerda = noCorrente;
        }
    }

    //Ao fim do laço, pego a aresta que liga a ponta esquerda à ponta direita e retorno a lista de arestas
    arestaCorrente = pontaEsquerda->getAresta(pontaDireita->getId());
    arestasInSolution.push_back(arestaCorrente);

    return arestasInSolution;
}
/* =======================================================================*/


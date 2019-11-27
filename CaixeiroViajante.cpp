//
// Created by julio on 05/11/2019.
//

#include <fstream>
#include "CaixeiroViajante.h"
#include "Grafo.h"
#include <cmath>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace chrono;

const vector<double> ALPHA_COLLECTION { 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50 };
const double RANDOM_FACTOR = 1000;
const double RECALL_PERCENT_OVER_ALPHA = 0.05;
const int EXECUTIONS_RANDOMIZING_REACTIVE = 1500;
const int EXECUTIONS_RANDOMIZING = 100;
const bool DEBUG = false;
const bool DEBUG_GRR = false;

CaixeiroViajante::CaixeiroViajante() {
    double initialProb = double(1/(double)ALPHA_COLLECTION.size());

    for(int i = 0; i <  ALPHA_COLLECTION.size(); i++){
        this->alphaParams.push_back(
            AlphaParams{ALPHA_COLLECTION[i], 0, initialProb}
        );
    }
}

/***
 * Faz a leitura do arquivo que contém o grafo do caixeiro viajante e constrói um grafo
 * @param _filename o caminho completo do arquivo
 * @return um ponteiro apontando para o grafo construido
 */
Grafo* CaixeiroViajante::BuildTSPGraphFromFile(string _filename){
    No* no;
    int ordem, idNo;
    double coordx, coordy;
    vector<LinhaArquivoCV> linhasArquivo;

    //Lê a primeira linha do grafo para determinar a ordem e construir o grafo
    ifstream file;
    file.open(_filename);
    file >> ordem;

    //Instancia o grafo
    Grafo* grafo = new Grafo(ordem, false, true, false);

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
                if(DEBUG)
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
    return result;
}

/***
 * Constrói uma lista de arestas que faz a representação do grafo de menor custo do caixeiro viajante, abordagem gulosa randomizada
 * @param _grafo: O grafo que contém a instância do problema
 * @param _randomizacao: Double sinalizando qual será a randomização do grafo. Caso não informado, será passado 0 como default
 * @return Lista de arestas que formam o grafo de menor custo
 */
vector<Aresta*> CaixeiroViajante::GetBetterCostGR(Grafo* _grafo, double _randomizacao){
    int randomFactor = CaixeiroViajante::Random(_randomizacao, _grafo->getOrdem());
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
    vector<Aresta*> allArestas = _grafo->GetArestasSorted(_grafo->GetPrimeiroNo());
    Aresta* menorAresta = allArestas[randomFactor];
    arestaCorrente = menorAresta;
    arestasInSolution.push_back(arestaCorrente);

    //Defino os nós de 'ponta direita' e 'ponta esquerda' do caminho como sendo os dois nós que compoem a primeira aresta
    pontaDireita = _grafo->buscaNo(arestaCorrente->getId());
    pontaEsquerda = _grafo->buscaNo(arestaCorrente->getAdj());

    //Incluo o nó da ponta direita nos nós da solução e removo o nó da ponta direita dos nós que estão fora da solução
    noInSolution.push_back(pontaDireita);
    noOutSolution = _grafo->RemoveNoFromVector(noOutSolution, pontaDireita);
    if(DEBUG)
        cout << "Nó " << pontaDireita->getId() << " na ponta direita"<< endl;

    //Incluo o nó da ponta esquerda nos nós da solução e removo o nó da ponta esquerda dos nós que estão fora da solução
    noInSolution.push_back(pontaEsquerda);
    noOutSolution = _grafo->RemoveNoFromVector(noOutSolution, pontaEsquerda);
    if(DEBUG)
        cout << "Nó " << pontaEsquerda->getId() << " na ponta esquerda"<< endl;

    //Enquanto eu tiver ítens fora da solução, faço...
    while(!noOutSolution.empty()){

        //Pego as menores arestas da ponta esquerda e da ponta direita com abordagem randomizada
        menorArestaPontaDireita = CaixeiroViajante::GetRandomEdge(pontaDireita, _grafo, noInSolution, _randomizacao);
        menorArestaPontaEsquerda = CaixeiroViajante::GetRandomEdge(pontaEsquerda, _grafo, noInSolution, _randomizacao);

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
        if(DEBUG)
            cout << "Aresta entre " << arestaCorrente->getId() << " e " << arestaCorrente->getAdj() << " com custo " << arestaCorrente->getPeso() << " inserida" << endl;

        //Verifico qual ponta será atualizada baseado no id da aresta corrente
        if(arestaCorrente->getId() == pontaDireita->getId()){
            if(DEBUG)
                cout << "Substituindo nó " << pontaDireita->getId() << " por " << noCorrente->getId() << " na ponta direita" << endl;
            pontaDireita = noCorrente;
        } else{
            if(DEBUG)
                cout << "Substituindo nó " << pontaEsquerda->getId() << " por " << noCorrente->getId() << " na ponta esquerda" << endl;
            pontaEsquerda = noCorrente;
        }
    }

    //Ao fim do laço, pego a aresta que liga a ponta esquerda à ponta direita e retorno a lista de arestas
    arestaCorrente = pontaEsquerda->getAresta(pontaDireita->getId());
    arestasInSolution.push_back(arestaCorrente);

    return arestasInSolution;
}

/***
 * Gerador de números aleatórios com percentual dentro da ordem do grafo
 * @param _percent: O percentual sobre a ordem que desejo fazer a randomização
 * @param _grafo: O grafo do problema
 * @return inteiro representando o randomizado encontrado
 */
int CaixeiroViajante::Random(double _percent, int _maxRandom){
    int base = double(_maxRandom * _percent);
    int randomNumber = rand() % (base <= 0 ? 1 : base);
    return randomNumber;
}

/***
 * Função que escolhe qual será o proximo vértice baseado na escolha randômica de arestas
 * @param _node: Qual nó estou verificando as arestas no momento
 * @param _grafo: O grafo que contém os nós
 * @param _nodeInSolution: Lista de nós que ja estão na solução
 * @param _randomPercent: Percentual de variação dentro da ordem do grafo
 * @return Aresta indicando qual será o próximo nó randomizado
 */
Aresta* CaixeiroViajante::GetRandomEdge(No* _node, Grafo* _grafo, vector<No*> _nodeInSolution, float _randomPercent){
    vector<Aresta*> elegibleEdges = GetEdgesOutSolution(_node, _grafo, _nodeInSolution);
    int random = CaixeiroViajante::Random(_randomPercent, _grafo->getOrdem());

    if(random >= elegibleEdges.size())
        random = elegibleEdges.size() - 1;
    return elegibleEdges[random];
}

/***
 * Percorro todas as arestas de um determinado nó e verifico se ele está na solução. Se não tiver
 * Posso colocá-lo como vértice elegível para seleção
 * @param _node: O nó que quero pesquisar as arestas
 * @param _grafo: O grafo que contém os nós
 * @param _nodeInSolution: Lista de nós que já estão na solução
 * @return um vector de arestas que podem ser escolhidas como próximas
 */
vector<Aresta*> CaixeiroViajante::GetEdgesOutSolution(No* _node, Grafo* _grafo, vector<No*> _nodeInSolution){
    vector<Aresta*> allEdges = _grafo->GetAllArestas(_node, false);
    vector<Aresta*> edgesOutSolution;
    bool isNotInSolution;

    for(long i = 0; i < allEdges.size(); i++){
        isNotInSolution = true;
        for(long j = 0; j < _nodeInSolution.size() && isNotInSolution; j++){
            if(allEdges[i]->getAdj() == _nodeInSolution[j]->getId())
                isNotInSolution = false;
        }
        if(isNotInSolution)
            edgesOutSolution.push_back(allEdges[i]);
    }
    return edgesOutSolution;
}

/**
 * Calcula a soma dos pesos das arestas na solução
 * @param _grafo: Grafo completo
 * @param _randomizacao: O alfa que determina a randomização
 * @return: Inteiro com peso das arestas somados
 */
int CaixeiroViajante::GetSumOfEdgeHeights(Grafo* _grafo, double _randomizacao){
    long totalHeight = 0;
    vector<Aresta*> arestasInSolution = CaixeiroViajante::GetBetterCostGR(_grafo, _randomizacao);
    for(Aresta* aresta : arestasInSolution)
        totalHeight += aresta->getPeso();
    return totalHeight;
}

/**
 * Faz a execução do algoritmo do caixeiro viajante e retorna uma struct com dados da execução
 * @param _grafo: Grafo completo
 * @param _randomizacao: O alfa que determina a randomizacao
 * @return: Struct ExecutionParams, que armazena qual randomização e peso total de arestas da execução
 */
ExecutionParams CaixeiroViajante::ExecuteGRR(Grafo* _grafo, double _randomizacao){
    high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    int sumOfHeights = CaixeiroViajante::GetSumOfEdgeHeights(_grafo, _randomizacao);
    float timeInSeconds = CaixeiroViajante::CalcExecutionTime(inicio);
    return ExecutionParams{ _randomizacao, sumOfHeights, timeInSeconds };
}

float CaixeiroViajante::CalcExecutionTime(high_resolution_clock::time_point _inicio){
    high_resolution_clock::time_point _fim = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(_fim - _inicio).count() / 1000.00;
}

/**
 * Baseado no número randômico de 0 a 1 que é gerado, pega o alfa correspondente
 * @param _random: Double de 0 a 1 que representa qual é a faixa randomica do alfa
 * @return: Double representando o alfa selecionado
 */
double CaixeiroViajante::GetAlphaByProb(double _random){
    double alpha;
    double rangeInicial = 0;
    AlphaParams p;

    for (long i = 0; i < this->alphaParams.size(); i++) {
        p = this->alphaParams[i];
        if(rangeInicial < _random && _random <= (rangeInicial + p.probValue))
            alpha = p.alpha;
        rangeInicial += 1 * p.probValue;
    }
    return alpha;
}

/**
 * Produz a normalização da lista de N execuçãoes do algoritmo para um determinado alfa
 * @param _execParams: Lista com o alfa e o peso total da solução
 * @param _normalizedVal: Parametro para que seja inforamado qual alfa que está sendo normalizado
 * @return: Struct AlphaParams, que tem os dados da nova atualização de normalização
 */
AlphaParams CaixeiroViajante::GetHeightNormalization(vector<ExecutionParams> _execParams, AlphaParams _normalizedVal){
    int minValue = -1;
    int totalHeight = 0;
    int execsToThisAlpha = 0;
    double normalizedVal = 0;

    for (long i = 0; i < _execParams.size(); i++) {
        if(minValue == -1 || minValue > _execParams[i].totalHeight)
            minValue = _execParams[i].totalHeight;

        if(_execParams[i].alpha == _normalizedVal.alpha){
            totalHeight +=_execParams[i].totalHeight;
            execsToThisAlpha++;
        }
    }
    if(execsToThisAlpha > 0)
        normalizedVal = (double(minValue) / (double(totalHeight) / double(execsToThisAlpha)));

    AlphaParams ap {
            _normalizedVal.alpha,
            normalizedVal,
            _normalizedVal.probValue,
        _normalizedVal.executionTimes += execsToThisAlpha
    };
    return ap;
}

/**
 * Recalcula a probabilidade com base na lista normalizada de execuções
 */
void CaixeiroViajante::RecallProbability() {
    double sumOfNormalizations = 0;

    if(DEBUG_GRR)
        cout << endl << "= Recall de probabilidade =====" << endl;

    for (int i = 0; i < this->alphaParams.size(); i++)
        sumOfNormalizations += this->alphaParams[i].normalizedValue;

    for (int j = 0; j < alphaParams.size(); ++j) {
        AlphaParams p = this->alphaParams[j];
        p.probValue = this->alphaParams[j].normalizedValue / sumOfNormalizations;
        this->alphaParams[j] = p;

        if(DEBUG_GRR)
            cout << "A probabilidade para o alfa " << p.alpha << " foi recalculada para " << p.probValue<< endl;
    }
}

/**
 * Recalcula a normalização de execuções
 * @param _execParams: Lista de execuções do algoritmo guloso
 */
void CaixeiroViajante::RecallNormalization(vector<ExecutionParams> _execParams) {
    AlphaParams normalizedVal;

    if(DEBUG_GRR)
        cout << endl << "= Recall de normalizacao =====" << endl;

    for (int i = 0; i < this->alphaParams.size(); i++) {
        normalizedVal = CaixeiroViajante::GetHeightNormalization(_execParams, this->alphaParams[i]);;
        this->alphaParams[i] = normalizedVal;

        if(DEBUG_GRR)
            cout << "A normalização para o alfa " << normalizedVal.alpha << " foi recalculada para " << normalizedVal.normalizedValue << endl;
    }
}

ExecutionParams CaixeiroViajante::ExecGuloso(Grafo *_grafo) {
    ExecutionParams p = CaixeiroViajante::ExecuteGRR(_grafo, 0);
    return p;
}

ExecutionParams CaixeiroViajante::ExecRandomizado(Grafo *_grafo, double alfa) {
    high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    ExecutionParams atual = CaixeiroViajante::ExecuteGRR(_grafo, alfa);
    ExecutionParams exec;

    for (int i = 1; i < EXECUTIONS_RANDOMIZING; ++i){
        exec = CaixeiroViajante::ExecuteGRR(_grafo, alfa);
        if(atual.totalHeight > exec.totalHeight)
            atual = exec;
    }

    atual.timeInSeconds = CaixeiroViajante::CalcExecutionTime(inicio);

    return atual;
}

/**
 * Executa o randomizado reativo
 * @param _grafo: O grafo completo
 * @return Lista de ExecutionParams, que é a estrutura que armazena os resultados de cada execução
 */
ExecutionParams CaixeiroViajante::ExecRandomizadoReativo(Grafo* _grafo){
    high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    double alpha;
    double randomDouble;
    int recallPoint = int(EXECUTIONS_RANDOMIZING_REACTIVE * RECALL_PERCENT_OVER_ALPHA);

    vector<ExecutionParams> execParams;
    ExecutionParams lowestParam = ExecutionParams{0, INT32_MAX};

    for (int i = 0; i < EXECUTIONS_RANDOMIZING_REACTIVE; i++) {
        randomDouble = (double(CaixeiroViajante::Random(1, RANDOM_FACTOR))/RANDOM_FACTOR);
        alpha = GetAlphaByProb(randomDouble);

        ExecutionParams currentParam = CaixeiroViajante::ExecuteGRR(_grafo, alpha);
        execParams.push_back(currentParam);

        if (lowestParam.totalHeight > currentParam.totalHeight)
            lowestParam = currentParam;

        if(i > 0 && i % recallPoint == 0){

            if(DEBUG_GRR){
                cout << endl << "*************************************************";
                cout << endl << "**** Iteração " << i << " *******************************";
                cout << endl << "*************************************************";
                cout << endl << "Menor peso até agora: " << lowestParam.totalHeight;
            }

            RecallNormalization(execParams);
            RecallProbability();
            execParams.clear();
        }
    }

    if(DEBUG_GRR){
        cout << endl << "=========================";
        cout << endl << "= Resultados finais =====";
        cout << endl << "=========================";
        for (int i = 0; i < this->alphaParams.size(); i++) {
            cout << endl << "Para o alfa " << this->alphaParams[i].alpha << " temos: " << endl;
            cout << "-Normalizacao: " << this->alphaParams[i].normalizedValue << endl;
            cout << "-Probabilidade: " << this->alphaParams[i].probValue << endl;
            cout << "-Execuções: " << this->alphaParams[i].executionTimes << endl;
        }
    }

    lowestParam.timeInSeconds = CaixeiroViajante::CalcExecutionTime(inicio);

    return lowestParam;
}
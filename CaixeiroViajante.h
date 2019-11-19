//
// Created by julio on 05/11/2019.
//

#ifndef TRABALHOGRAFOS_CAIXEIROVIAJANTE_H
#define TRABALHOGRAFOS_CAIXEIROVIAJANTE_H


#include "Grafo.h"

struct LinhaArquivoCV{
    int idNo;
    double coordx;
    double coordy;
};

struct ExecutionParams{
    double alpha = 0;
    int totalHeight = 0;
};

struct AlphaParams{
    double alpha;
    double normalizedValue;
    double probValue;
    int executionTimes;
};

struct RDI{
    double value = 0;
    double timeInSeconds = 0;
    int bestHeight = 0;
};

class CaixeiroViajante {

public:
    vector<AlphaParams> alphaParams;

    CaixeiroViajante();
    static Grafo *BuildTSPGraphFromFile(std::basic_string<char> _filename);
    static int GetEuclideanDistance(int _xa, int _ya, int xb, int yb);
    static vector<Aresta *> GetBetterCostGR(Grafo *_grafo, double _randomizacao = 0);
    static int Random(double _percent, int _maxRandom);
    static vector<Aresta *> GetEdgesOutSolution(No *_node, Grafo *_grafo, vector<No *> _nodeInSolution);
    static Aresta *GetRandomEdge(No *_node, Grafo *_grafo, vector<No *> _nodeInSolution, float _randomPercent);
    static int GetSumOfEdgeHeights(Grafo *_grafo, double _randomizacao);
    static ExecutionParams ExecuteGRR(Grafo *_grafo, double _randomizacao);
    static bool OrdenaExecutions(ExecutionParams _e1, ExecutionParams _e2);
    static AlphaParams GetHeightNormalization(vector<ExecutionParams> _execParams, AlphaParams _normalizedVal);
    static vector<AlphaParams> GetListNormalizedHeights(Grafo *_grafo);


    double GetAlphaByProb(double _random);
    void RecallProbability();
    void RecallNormalization(vector<ExecutionParams>  _execParams);

    RDI ExecGuloso(Grafo *_grafo);
    RDI ExecRandomizado(Grafo *_grafo);
    RDI ExecRandomizadoReativo(Grafo *_grafo);
};


#endif //TRABALHOGRAFOS_CAIXEIROVIAJANTE_H

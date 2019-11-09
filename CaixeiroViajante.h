//
// Created by julio on 05/11/2019.
//

#ifndef TRABALHOGRAFOS_CAIXEIROVIAJANTE_H
#define TRABALHOGRAFOS_CAIXEIROVIAJANTE_H


#include "Grafo.h"

struct LinhaArquivoCV{
    int idNo;
    int coordx;
    int coordy;
};

struct ExecutionParams{
    double alpha;
    int totalHeight;
};

struct NormalizedValue{
    double alpha;
    double value;
};

class CaixeiroViajante {

public:
    static Grafo *BuildTSPGraphFromFile(std::basic_string<char> _filename);
    static int GetEuclideanDistance(int _xa, int _ya, int xb, int yb);
    static vector<Aresta *> GetBetterCostGR(Grafo *_grafo, double _randomizacao = 0);
    static int Random(double _percent, int _maxRandom);
    static vector<Aresta *> GetEdgesOutSolution(No *_node, Grafo *_grafo, vector<No *> _nodeInSolution);
    static Aresta *GetRandomEdge(No *_node, Grafo *_grafo, vector<No *> _nodeInSolution, float _randomPercent);
    static int GetSumOfEdgeHeights(Grafo *_grafo, double _randomizacao);
    static vector<ExecutionParams> ExecuteGRR(Grafo *_grafo, double _randomizacao);
    static bool OrdenaExecutions(ExecutionParams _e1, ExecutionParams _e2);
    static double GetHeightNormalization(vector<ExecutionParams> _execParams);

    static vector<NormalizedValue> GetListNormalizedHeights(Grafo *_grafo);
};


#endif //TRABALHOGRAFOS_CAIXEIROVIAJANTE_H

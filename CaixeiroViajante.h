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

class CaixeiroViajante {

public:
    static Grafo *BuildTSPGraphFromFile(std::basic_string<char> _filename);
    static int GetEuclideanDistance(int _xa, int _ya, int xb, int yb);
    static vector<Aresta *> GetBetterCostGR(Grafo *_grafo, double _randomizacao = 0);
    static int Random(double _percent, Grafo *_grafo);
    static vector<Aresta *> GetEdgesOutSolution(No *_node, Grafo *_grafo, vector<No *> _nodeInSolution);
    static Aresta *GetRandomEdge(No *_node, Grafo *_grafo, vector<No *> _nodeInSolution, float _randomPercent);
};


#endif //TRABALHOGRAFOS_CAIXEIROVIAJANTE_H

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
    static int GetEuclideanDistance(int xa, int ya, int xb, int yb);
};


#endif //TRABALHOGRAFOS_CAIXEIROVIAJANTE_H

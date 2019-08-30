//
// Created by JuarezPCs on 30/08/2019.
//

#ifndef TRABALHOGRAFOS_LEITURAARQUIVO_H
#define TRABALHOGRAFOS_LEITURAARQUIVO_H

#include "Grafo.h"
#include "fstream"

using namespace std;

class LeituraArquivos {
private:
    ifstream file;

public:
    void geraGrafoNormal(Grafo *graf, char *caminho);
    void geraGrafoPonderado(Grafo *graf, char *caminho);
};
#endif //TRABALHOGRAFOS_LEITURAARQUIVO_H

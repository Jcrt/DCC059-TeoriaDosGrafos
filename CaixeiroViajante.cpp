//
// Created by julio on 05/11/2019.
//

#include <fstream>
#include "CaixeiroViajante.h"
#include "Grafo.h"
#include <math.h>
using namespace std;

/* == Construção do grafo ================================================*/
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

    /*Percorre a lista de arestas duas vezes, uma para pegar nó por nó e outra para criar as arestas*/
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
            }
        }
    }

    return grafo;
}

int CaixeiroViajante::GetEuclideanDistance(int xa, int ya, int xb, int yb){
    int x = pow(xa - xb, 2);
    int y = pow(ya - yb, 2);
    int result = sqrt(x + y);
}
/* =======================================================================*/


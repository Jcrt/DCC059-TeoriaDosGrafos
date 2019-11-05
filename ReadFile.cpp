//
// Created by julio on 29/09/2019.
//

#include <string>
#include <bits/stdc++.h>
//#include <boost/algorithm/string.hpp>
#include "ReadFile.h"

using namespace std;

ArquivoGrafo ReadFile::GetArquivoGrafo(string fileName){
    vector<string> grafo = ReadFile::Read(fileName);
    ArquivoGrafo ag;
    ag.Ordem = GetOrdemGrafo(grafo);
    ag.Linhas = GetLinhasGrafo(grafo);
    return ag;
}

LinhaArquivo ReadFile::CriaStructLinha(string linhaArquivo){
    vector<string> result;
    LinhaArquivo la;
    //boost::split(result, linhaArquivo, boost::is_any_of(" "));

    if(!result.empty()){
        switch (result.size()){
            case 3:{
                la.NoOrigem = stoi(result[0]);
                la.NoDestino = stoi(result[1]);
                la.PesoAresta = stoi(result[2]);
            } break;
            case 4: {
                la.NoOrigem = stoi(result[0]);
                la.PesoOrigem = stoi(result[1]);
                la.NoDestino = stoi(result[2]);
                la.PesoDestino = stoi(result[3]);
            }
            case 5: {
                la.NoOrigem = stoi(result[0]);
                la.PesoOrigem = stoi(result[1]);
                la.NoDestino = stoi(result[2]);
                la.PesoDestino = stoi(result[3]);
                la.PesoAresta = stoi(result[4]);
            } break;
        }
    }
    return la;
}

vector<string> ReadFile::Read(string filename) {
    string linha;
    vector<string> grafoCompleto;
    ifstream arquivoEntrada;
    arquivoEntrada.open(filename);

    if(arquivoEntrada.is_open()){
        while(!arquivoEntrada.eof()){
            getline(arquivoEntrada, linha);
            grafoCompleto.push_back(linha);
        }
    }

    arquivoEntrada.close();
    return grafoCompleto;
}

int ReadFile::GetOrdemGrafo(vector<string> &arquivoLido){
    int ordem = 0;
    if(arquivoLido.size() > 0){
        ordem = stoi(arquivoLido[0]);
    }
    return ordem;
}

vector<LinhaArquivo> ReadFile::GetLinhasGrafo(vector<string> &arquivoLido){
    vector<LinhaArquivo> linhasArquivos;
    for(int i = 1; i < arquivoLido.size(); i++){
        LinhaArquivo la = CriaStructLinha(arquivoLido[i]);
        linhasArquivos.push_back(la);
    }
    return linhasArquivos;
}




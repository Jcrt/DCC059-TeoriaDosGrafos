//
// Created by julio on 29/09/2019.
//

#ifndef TRABALHOGRAFOS_READFILE_H
#define TRABALHOGRAFOS_READFILE_H

using namespace std;

struct LinhaArquivo{
    int NoOrigem = 1;
    int PesoOrigem = 1;
    int NoDestino = 1;
    int PesoDestino = 1;
    int PesoAresta = 1;
};

struct ArquivoGrafo{
    int Ordem;
    vector<LinhaArquivo> Linhas;
};

class ReadFile{
public:
    static ArquivoGrafo GetArquivoGrafo(string fileName);
private:
    static vector<string> Read(string filename);
    static int GetOrdemGrafo(vector<string> &arquivoLido);
    static vector<LinhaArquivo> GetLinhasGrafo(vector<string> &arquivoLido);
    static LinhaArquivo CriaStructLinha(string linhaArquivo);
};


#endif //TRABALHOGRAFOS_READFILE_H

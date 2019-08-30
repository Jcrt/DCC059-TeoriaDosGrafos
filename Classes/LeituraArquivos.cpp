//
// Created by JuarezPCs on 28/08/2019.
//

# include  "LeituraArquivos.h"
# include  "Grafo.h"
# include  <iostream>
# include  <cstdlib>
# include  <string>
using namespace std;

///Le o arquivo e se der tudo certo cria o grafo
void LeituraArquivos::geraGrafoNormal(Grafo *graf, char *caminho) {
    file.open(caminho);
    if(!file.is_open())
        cout << "Nao foi possivel abrir o arquivo" << endl;
    else{
        int a, b;
        file >> a;
        cout << "Grafo criado com " << a << " nos" << endl;
        while(!file.eof()){
            file >> a >> b;
            graf->addAresta(a, b, 1);
        }
    }
    file.close();
}

///Le o arquivo e se der tudo certo cria o grafo
void LeituraArquivos::geraGrafoPonderado(Grafo *graf, char *caminho) {
    file.open(caminho);
    if(!file.is_open())
        cout << "Nao foi possivel abrir o arquivo" << endl;
    else{
        int a, b, c;
        file >> a;
        cout << "Grafo com " << a << "nos" << endl;
        while(!file.eof()){
            file >> a >> b >> c;
            graf->addAresta(a, b, c);
        }
    }
    file.close();
}

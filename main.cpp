#include <random>
#include "MenuPrincipal.h"
#include "Grafo.h"
#include "CaixeiroViajante.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>
#include <iomanip>
#include <chrono>
#include <cstdlib>

using namespace std;

/**
 * Metodo para leitura dos dados do arquivo e criacao do grafo de acordo com sua definicao.
 * @param arqEntrada caminho do arquivo de entrada.
 * @param direcionado 0 para grafo nao direcionado e 1 para grafo direcionado.
 * @param ponderadoAresta 0 para grafo nao ponderado nas arestas e 1 para grafo ponderado nas arestas.
 * @param ponderadoNo 0 para grafo nao ponderado nos vertices e 1 para grafo ponderado nos vertices.
 * @return retorna o grafo criado.
 */
Grafo* leituraDados(char *arqEntrada, bool direcionado, bool ponderadoAresta, bool ponderadoNo, char* arqSaida){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoOrigem;
    int idNoDestino;
    int ordem;
    ifstream file;

    file.open(arqEntrada);

    //Pegando a ordem do grafo
    file >> ordem;

    //Criando objeto grafo
    Grafo* graf = new Grafo(ordem, direcionado, ponderadoAresta, ponderadoNo);

    //Leitura de arquivo
    if(!graf->ehPonderadoAresta() && !graf->ehPonderadoVertice())
        while(file >> idNoOrigem >> idNoDestino)
            graf->addAresta(idNoOrigem, idNoDestino, 0);

    else if(graf->ehPonderadoAresta() && !graf->ehPonderadoVertice() ){
        float pesoAresta;
        while(file >> idNoOrigem >> idNoDestino >> pesoAresta)
            graf->addAresta(idNoOrigem, idNoDestino, pesoAresta);
    }

    else if(graf->ehPonderadoVertice() && !graf->ehPonderadoAresta()){
        float pesoNoOrigem, pesoNoDestino;
        while(file >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino) {
            graf->addAresta(idNoOrigem, idNoDestino, 0);
            graf->buscaNo(idNoOrigem)->setPeso(pesoNoOrigem);
            graf->buscaNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }

    else if(graf->ehPonderadoVertice() && graf->ehPonderadoAresta()){
        float pesoNoOrigem, pesoNoDestino, pesoAresta;
        while(file >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino >> pesoAresta) {
            graf->addAresta(idNoOrigem, idNoDestino, pesoAresta);
            graf->buscaNo(idNoOrigem)->setPeso(pesoNoOrigem);
            graf->buscaNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }

    file.close();
    return graf;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int opcaoEscolhida;
    auto inicio = std::chrono::high_resolution_clock::now();


    if(argc != 2) {
        cout << "Argumentos insuficientes" << endl;
        return 1;
    }



    char* arquivoEntrada = argv[1];
    char* arquivoSaida = argv[2];
    //bool isDirecionado = atoi(argv[2]);
    //bool isPonderadoAresta = atoi(argv[3]);
    //bool isPonderadoNo = atoi(argv[4]);

    bool isDirecionado;
    bool isPonderadoAresta;
    bool isPonderadoNo;

    int x;
    cout << "Qual o tipo de Grafo: " << endl;
    cout << "1) - Orientado e Ponderado nas Arestas " << endl;
    cout << "2) - Orientado e Nao podenrado nas Arestas" << endl;
    cout << "3) - Nao Orientado e Ponderado nas Arestas " << endl;
    cout << "4) - Nao Orientado e Nao ponderado nas Arestas" << endl;
    cin >> x;
    if(x == 1){
        isDirecionado = true;
        isPonderadoAresta = true;
    }else if(x == 2){
        isDirecionado = true;
        isPonderadoAresta = false;
    }else if(x == 3){
        isDirecionado = false;
        isPonderadoAresta = true;
    }else if(x == 4){
        isDirecionado = false;
        isPonderadoAresta = false;
    }
    cout << endl;


    do
    {
        opcaoEscolhida = MenuPrincipal::ReadOption();
        switch(opcaoEscolhida){
            case 1:{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                cout << "No inicial busca em largura: ";
                int idNo;
                cin >> idNo;
                x->buscaEmLargura(idNo);
                delete x;
            }break;
            case 2:{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                cout << "No inicial busca em profundidade: ";
                int idNo;
                cin >> idNo;
                x->buscaProfundidade(idNo);
                delete x;
            }break;
            case 3:{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                x->algFloyd(4, 3);
                delete x;
            }break;
            case 4:{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                x->menorCaminhoDijkstra(4, 3);
                delete x;
            }break;
            case 5:{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                x->Prim();
                delete x;
            } break;
            case 6:{
                Grafo* y;
                y = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                y->kruskal();
                delete y;
            }break;
            case 7 :{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, nullptr);
                x->imprimirArestas();
                delete x;
            }break;
            case 8:{
                Grafo* x = CaixeiroViajante::BuildTSPGraphFromFile(arquivoEntrada);
                CaixeiroViajante* cv = new CaixeiroViajante();
                cv->ExecRandomizing(x);

                //vector<NormalizedValue> eee =  CaixeiroViajante::GetListNormalizedHeights(x);
            }break;
        }
    }while(opcaoEscolhida != MenuPrincipal::FINAL_APLICACAO);

    auto resultado = std::chrono::high_resolution_clock::now() - inicio;
    long long seconds = std::chrono::duration_cast<std::chrono::seconds>(resultado).count();
    cout << "Tempo em segundos: " << seconds << endl;
}
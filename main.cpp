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

    if(argc != 3) {
        cout << "Argumentos insuficientes" << endl;
        return 1;
    }

    char* arquivoEntrada = argv[1];
    char* arquivoSaida = argv[2];
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

    ofstream file;
    file.open(arquivoSaida, ofstream::ios_base::app);

    string algoritmoEscolhido;

    do
    {

        opcaoEscolhida = MenuPrincipal::ReadOption();
        switch(opcaoEscolhida){
            case 1:{
                algoritmoEscolhido = " busca em largura ";
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);
                cout << "No inicial busca em largura: ";
                int idNo;
                cin >> idNo;

                auto inicioFuncoes = std::chrono::high_resolution_clock::now();
                x->buscaEmLargura(idNo, arquivoSaida);
                delete x;

                auto resultadoFuncoes = std::chrono::high_resolution_clock::now() - inicioFuncoes;
                long long resulFunc = std::chrono::duration_cast<std::chrono::milliseconds>(resultadoFuncoes).count();
                file << " Tempo de execucao em ms" << algoritmoEscolhido << ": " << resulFunc << endl;
            }break;
            case 2:{
                algoritmoEscolhido = " busca em profundidade ";
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);
                cout << "No inicial busca em profundidade: ";
                int idNo;
                cin >> idNo;

                auto inicioFuncoes = std::chrono::high_resolution_clock::now();
                x->buscaProfundidade(idNo, arquivoSaida);
                delete x;

                auto resultadoFuncoes = std::chrono::high_resolution_clock::now() - inicioFuncoes;
                long long resulFunc = std::chrono::duration_cast<std::chrono::milliseconds>(resultadoFuncoes).count();
                file << " Tempo de execucao em ms" << algoritmoEscolhido << ": " << resulFunc << endl;
            }break;
            case 3:{

                algoritmoEscolhido = " floyd ";
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);
                int no1, no2;
                cout << "No 1: ";
                cin >> no1;
                cout << "No 2: ";
                cin >> no2;

                auto inicioFuncoes = std::chrono::high_resolution_clock::now();
                x->algFloyd(no1, no2, arquivoSaida);
                delete x;

                auto resultadoFuncoes = std::chrono::high_resolution_clock::now() - inicioFuncoes;
                long long resulFunc = std::chrono::duration_cast<std::chrono::milliseconds>(resultadoFuncoes).count();
                file << " Tempo de execucao em ms" << algoritmoEscolhido << ": " << resulFunc << endl;
            }break;
            case 4:{
                algoritmoEscolhido = " dijsktra ";
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);
                int no1, no2;
                cout << "No 1: ";
                cin >> no1;
                cout << "No 2: ";
                cin >> no2;

                auto inicioFuncoes = std::chrono::high_resolution_clock::now();
                x->menorCaminhoDijkstra(no1, no2, arquivoSaida);
                delete x;

                auto resultadoFuncoes = std::chrono::high_resolution_clock::now() - inicioFuncoes;
                long long resulFunc = std::chrono::duration_cast<std::chrono::milliseconds>(resultadoFuncoes).count();
                file << " Tempo de execucao em ms" << algoritmoEscolhido << ": " << resulFunc << endl;
                file << endl;
            }break;
            case 5:{
                algoritmoEscolhido = " prim ";
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);

                auto inicioFuncoes = std::chrono::high_resolution_clock::now();
                x->Prim(arquivoSaida);
                delete x;

                auto resultadoFuncoes = std::chrono::high_resolution_clock::now() - inicioFuncoes;
                long long resulFunc = std::chrono::duration_cast<std::chrono::milliseconds>(resultadoFuncoes).count();
                file << " Tempo de execucao em ms" << algoritmoEscolhido << ": " << resulFunc << endl;
            } break;
            case 6:{

                algoritmoEscolhido = " kruskal ";
                Grafo* y;
                y = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);

                auto inicioFuncoes = std::chrono::high_resolution_clock::now();
                y->kruskal(arquivoSaida);
                delete y;

                auto resultadoFuncoes = std::chrono::high_resolution_clock::now() - inicioFuncoes;
                long long resulFunc = std::chrono::duration_cast<std::chrono::milliseconds>(resultadoFuncoes).count();
                file << " Tempo de execucao em ms" << algoritmoEscolhido << ": " << resulFunc << endl;
            }break;
            case 7 :{
                Grafo* x;
                x = leituraDados(arquivoEntrada, isDirecionado, isPonderadoAresta, isPonderadoNo, arquivoSaida);
                x->imprimirArestas();
                delete x;
            }break;
            case 8:{
                Grafo* x = CaixeiroViajante::BuildTSPGraphFromFile(arquivoEntrada);
                CaixeiroViajante* cv = new CaixeiroViajante();

                RDI rdiGuloso = cv->ExecGuloso(x);
                file << "RDI Guloso para instância " << arquivoEntrada << ": " << rdiGuloso.value << endl;

                RDI rdiRandomizado = cv->ExecRandomizado(x);
                file << "RDI Guloso randomizado para instância " << arquivoEntrada << ": " << rdiRandomizado.value << endl;

                RDI rdiReativo = cv->ExecRandomizadoReativo(x);
                file << "RDI Guloso randomizado reativo para instância " << arquivoEntrada << ": " << rdiReativo.value << endl;
            }break;
        }

    }while(opcaoEscolhida != MenuPrincipal::FINAL_APLICACAO);
    
}


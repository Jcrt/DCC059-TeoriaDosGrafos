//
// Created by julio on 06/08/2019.
//

#include "MenuPrincipal.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>

using namespace std;

//Definindo as opções do menu
vector<OpcoesMenu> MenuPrincipal::GetOpcoesMenu(){
    static vector<OpcoesMenu> opt = {
        {1, "Busca em largura"},
        {2, "Busca em profundidade"},
        {3, "Menor caminho floyd"},
        {4, "Menor caminho dijsktra"},
        {5, "Árvore geradora de custo mínimo Prim"},
        {6, "Imprime arestas"},
        {0, "Sair do programa"}
    };
    return opt;
}

void MenuPrincipal::Show() {
    vector<OpcoesMenu> opt = GetOpcoesMenu();
    //ClearOutput();
    cout << "*====================================================*" << endl;
    cout << "*= UNIVERSIDADE FEDERAL DE JUIZ DE FORA             =*" << endl;
    cout << "*= DCC059 - TEORIA DOS GRAFOS - 2019.03 - Grupo 7   =*" << endl;
    cout << "*====================================================*" << endl;
    for(int i = 0; i < opt.size(); i++){
        cout << opt[i].NumOption << ") " << opt[i].Description << endl;
    }
    cout << endl << "Selecione uma das opções: " << endl;
}

int MenuPrincipal::ReadOption() {
    string input;
    int option = -1;
    int qtdOpcoes = GetOpcoesMenu().size();

    Show();
    cin >> input;

    if(is_number(input) && stoi(input) >= 0 && qtdOpcoes -1 >= stoi(input)){
        option = stoi(input);
    } else {
        cout << "Opção '" << input << "' inválida" << endl << endl;
    }

    return option;
}

void MenuPrincipal::ClearOutput() {
    if(system(NULL)){
        system("cls");
        fflush(stdin);
    }
}

bool MenuPrincipal::is_number(const std::string& s)
{
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
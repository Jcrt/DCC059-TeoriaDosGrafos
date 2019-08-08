//
// Created by julio on 06/08/2019.
//

#include "MenuPrincipal.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;

void MenuPrincipal::Show() {
    cout << "============================================================" << endl;
    cout << "=== UNIVERSIDADE FEDERAL DE JUIZ DE FORA ===================" << endl;
    cout << "=== DCC059 - TEORIA DOS GRAFOS =============================" << endl;
    cout << "============================================================" << endl;
    cout << "Selecione uma das opções abaixo e pressione enter: ";

    cout << "0 - Encerrar o programa";
}

int MenuPrincipal::ReadOption() {
    char input;
    int option;

    Show();
    cin.get(input);

    if(!isdigit(input)){
        cout << endl << "The char passed isn't a number!" << endl;
        option = -1;
    }
    else{
        option = input;
    }

    return option;
}

void MenuPrincipal::ClearOutput() {
    system("CLS");
    fflush(stdin);
}

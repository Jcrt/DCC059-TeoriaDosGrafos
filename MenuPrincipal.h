//
// Created by julio on 06/08/2019.
//

#ifndef TRABALHOGRAFOS_MENUPRINCIPAL_H
#define TRABALHOGRAFOS_MENUPRINCIPAL_H
#include <string>
#include <vector>

using namespace std;

struct OpcoesMenu {
    int NumOption;
    string Description;
};

class MenuPrincipal {
public:
    static void Show();
    static void ClearOutput();
    static int ReadOption();

    static const int FINAL_APLICACAO = 0;
    static vector<OpcoesMenu> GetOpcoesMenu();
private:
    static bool is_number(const string &s);
};

#endif //TRABALHOGRAFOS_MENUPRINCIPAL_H

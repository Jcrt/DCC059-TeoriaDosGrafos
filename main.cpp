#include <random>
#include "Classes/MenuPrincipal.h"
#include "Classes/Grafo.h"
#include "Classes/Aresta.h"
#include "Classes/No.h"
using namespace std;

int main() {
    /*
    while(MenuPrincipal::ReadOption() != 0){
        MenuPrincipal::ReadOption();
    }*/

    Grafo *g = new Grafo(10, false, false, false);
    for(int i = 0; i <= 10; i++){
        g->insereNo(i);
    }
    cout << endl;

    g->addAresta(1, 10, 20);
    g->addAresta(1, 7, 10);
    g->addAresta(3, 5, 13);
    g->addAresta(5, 6, 19);
    g->addAresta(6, 9, 30);
    cout << endl;

    g->removeNo(1);
    g->removeNo((20));
    g->removeAresta(6, 5);
    g->removeAresta(4, 8);
}
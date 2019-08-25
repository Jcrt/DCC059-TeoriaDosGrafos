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

    Grafo g;
    for(int i = 0; i < 10; i++){
        g.insereNo(i);
    }

    g.addAresta(2,7,30, 5);
    g.addAresta(2,3,3, 10);
    g.addAresta(2,4,22, 32);

    g.imprimirVertices();
    g.imprimirArestas();


}
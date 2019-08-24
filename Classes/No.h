//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_NO_H
#define TRABALHOGRAFOS_NO_H


#include "Aresta.h"

class No {
    int Id;
    int DIn;
    int DOut;
    float Peso;
    No *Prox;
    Aresta *Adjascente;
};


#endif //TRABALHOGRAFOS_NO_H

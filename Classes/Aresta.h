//
// Created by julio on 24/08/2019.
//

#ifndef TRABALHOGRAFOS_ARESTA_H
#define TRABALHOGRAFOS_ARESTA_H


class Aresta {
public:
    int Id;
    int NoAdj;
    float Peso;
    Aresta *Prox;
};


#endif //TRABALHOGRAFOS_ARESTA_H

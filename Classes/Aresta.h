//
// Created by Leo on 29/09/2019.
//

#ifndef GRUPO_7_ARESTA_H
#define GRUPO_7_ARESTA_H


class Aresta {
    public:
        Aresta();
        ~Aresta();

        Aresta* getProx();
        void setProx(Aresta* p);
        void setPeso(int peso);
        void setAdj(int idAdj);
        int getAdj();
        float getPeso();

    private:
        int id;
        int adj;
        int peso;
        Aresta* prox;
};


#endif //GRUPO_7_ARESTA_H

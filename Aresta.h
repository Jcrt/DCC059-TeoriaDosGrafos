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
        int getAdj();
        float getPeso();
        int getId();
        void setProx(Aresta* p);
        void setPeso(int peso);
        void setAdj(int idAdj);
        void setId(int id);

    private:
        int id;
        int adj;
        int peso;
        Aresta* prox;
};


#endif //GRUPO_7_ARESTA_H

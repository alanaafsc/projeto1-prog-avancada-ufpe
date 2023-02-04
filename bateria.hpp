#ifndef BATERIA_H
#define BATERIA_H

class Bateria {
    int nivel;
    public:
        Bateria(int nivelInicial);
        void descarregar();
        void carregar();
};

#endif

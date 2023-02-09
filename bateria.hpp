#ifndef BATERIA_HPP
#define BATERIA_HPP

class Bateria {
    int nivel;
    public:
        Bateria(int nivelInicial);
        void descarregar();
        void carregar();
        int getNivel();
};

#endif

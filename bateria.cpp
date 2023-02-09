#include "bateria.hpp"

Bateria::Bateria(int nivelInicial) {
    nivel = nivelInicial;
};
//Bateria descarregada por uma unidade com cada ação:
void Bateria::descarregar() {
    nivel -= 1;
};
//Quando chegar na estação de carregamento
void Bateria::carregar() {
    nivel = 10;
};

int Bateria::getNivel(){
    return nivel;
};
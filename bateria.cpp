#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
using namespace std;

class Bateria {
    int nivel;
    public:
        Bateria(int nivelInicial) {
            nivel = nivelInicial;
        };
        void descarregar();
        void carregar();
};

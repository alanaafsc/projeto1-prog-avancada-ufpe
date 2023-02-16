#ifndef PARACHOQUE_HPP
#define PARACHOQUE_HPP

#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
using namespace std;

class Parachoque {
    public:
        bool calcularColisoes(Ambiente amb, int x, int y);
};

#endif 
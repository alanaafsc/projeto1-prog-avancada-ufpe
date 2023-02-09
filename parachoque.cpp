#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
#include "robot.hpp"
using namespace std;

class Parachoque {
    public:
        bool calcularColisoes(Ambiente amb, int posicaoMovimento[]);
};

bool Parachoque::calcularColisoes(Ambiente amb, int posicaoMovimento[]) {
    //detecta presenca de obstaculos na direcao do movimento
    if(amb.getGrade()[posicaoMovimento[0]][posicaoMovimento[1]] == '1') {
        return true;
    } 
    return false;
};
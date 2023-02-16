#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
#include "robot.hpp"
using namespace std;

class Parachoque {
    public:
        bool calcularColisoes(Ambiente amb, int x, int y);
};

bool Parachoque::calcularColisoes(Ambiente amb, int x, int y) {
    //detecta presenca de obstaculos na direcao do movimento
    if(amb.getGrade()[x][y] == '1') {
        return true;
    } 
    return false;
};
#include <iostream>
#include <fstream>
#include <string> 
#include "robot.hpp"
#include "laser.hpp"
#include "ambiente.hpp"
#include "bateria.hpp"
using namespace std;

class Modelo2: public Robot {
    char orientacao;
    Laser *laser;
    public:
        Modelo2(string robot, Ambiente amb):Robot(robot, amb) {
            laser = new Laser();
        };
        void limpar();
};

void Modelo2::limpar () {
    
};
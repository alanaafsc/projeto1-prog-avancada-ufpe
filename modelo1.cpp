#include <iostream>
#include <fstream>
#include <string> 
#include "robot.hpp"
#include "parachoque.hpp"
#include "ambiente.hpp"
using namespace std;

class Modelo1: public Robot {
    Parachoque *parachoque;
    public:
        Modelo1(string robot, Ambiente amb):Robot(robot, amb) {
            parachoque = new Parachoque();
        };
       
        void limpar();
};

void Modelo1::limpar () {

};
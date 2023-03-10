#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
#include "bateria.hpp"

using namespace std;

class Robot {
protected:
    string nome;
    int * posicaoGrade;
    Bateria * bateria;
public:
    Robot(string robot, Ambiente &amb);
    bool stopRobot();
    int * getPosicaoGrade();
    Bateria* getBateria();
};

#endif
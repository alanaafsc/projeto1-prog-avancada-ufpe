#ifndef ROBOT_H
#define ROBOT_H

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
        Robot(string, Ambiente);
        void stopRobot();
};

#endif
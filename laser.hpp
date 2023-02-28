#ifndef LASER_H
#define LASER_H

#include <iostream>
#include <fstream>
#include <string>
#include "ambiente.hpp"
using namespace std;


class Laser {
    public:
        bool calcularColisoes(Ambiente &amb, int robotX, int robotY);
};

#endif //LASER_H


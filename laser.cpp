#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
using namespace std;

class Laser {
    public: 
        bool calcularColisoes(Ambiente &amb, int robotX, int robotY);
};

bool Laser::calcularColisoes(Ambiente &amb, int robotX, int robotY) {
     if(amb.getGrade()[robotX][robotY] == '1') {
        return true;
    } 
    return false;
}









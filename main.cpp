#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
#include "bateria.hpp"
#include "laser.hpp"
#include "modelo1.hpp"
#include "modelo2.hpp"
#include "parachoque.hpp"
#include "robot.hpp"
using namespace std;

int main () {
    //Arquivo de configuração do ambiente
    string fileAmb = "config.txt";

    //Declaração do ambiente:
    Ambiente amb(fileAmb);

    //Arquivo de configuração do robô
    string fileRobot = "robot.txt";

    //Declaração do robô:
  //  Modelo1 modelo1(fileRobot, amb);

    return 0;
}
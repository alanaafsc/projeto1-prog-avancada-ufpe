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

    // //Declaração do robô:
    // Modelo1 modelo1(fileRobot, amb);
    // // posicao atual do robô:
    // int posicaoRobo_x = modelo1.getPosicaoGrade()[0];
    // int posicaoRobo_y = modelo1.getPosicaoGrade()[1];

    //definindo obstaculos:
    int obstaculoRec1[2] = {3,0};
    int obstaculoRec2[2] = {3,4};
    int obstaculo1[2] = {4,4};
    int obstaculo2[2] = {5,4};
    //adicionando obstaculos ao ambiente:
    amb.addObstaculo(obstaculoRec1, obstaculoRec2);
    amb.addObstaculo(obstaculo1);
    amb.addObstaculo(obstaculo2);
    
    amb.printAmbiente();
    // modelo1.limpar(amb);
    
    // //Iniciar modelo2:
    Modelo2 modelo2(fileRobot, amb);
    // // posicao atual do robô:
    int posicaoRobo_x = modelo2.getPosicaoGrade()[0];
    int posicaoRobo_y = modelo2.getPosicaoGrade()[1]; 

    // //limpar ambiente com modelo2:
    modelo2.limpar(amb);

    
    return 0;
}
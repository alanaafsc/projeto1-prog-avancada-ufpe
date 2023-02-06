#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
#include "robot.hpp"
using namespace std;

class Parachoque {
    public:
        void calcularColisoes(Ambiente amb, Robot &robot, char direcao);
};

void Parachoque::calcularColisoes(Ambiente amb, Robot &robot, char direcao) {
    //detecta presenca de obstaculos na direcao do movimento
    int * posicaoRobo_p = robot.getPosicaoGrade(); //tem que ser a posicao do robo
    int posicaoRobo_x = posicaoRobo_p[0];
    int posicaoRobo_y = posicaoRobo_p[1];
    int leftCell[2] = {posicaoRobo_x,posicaoRobo_y-1};
    int rightCell[2] = {posicaoRobo_x,posicaoRobo_y+1};
    int upCell[2] = {posicaoRobo_x-1,posicaoRobo_y};
    int downCell[2] = {posicaoRobo_x+1,posicaoRobo_y};

    if(amb.getGrade()[leftCell[0]][leftCell[1]] != '1' && amb.getGrade()[leftCell[0]][leftCell[1]] != 'L' 
    && amb.getGrade()[leftCell[0]][leftCell[1]] != 'E') {
        // Robo vai pra Left Cell e dps q sair de Left Cell vai ter o L no lugar
        // caso posicao do robo seja E, n pode colocar L

        //colocar L na posicao atual do robo
        //colocar R na posicao leftCell
        //diminuir 1 unidade de bateria -> chamar funcao descarregar do robo
    }

};
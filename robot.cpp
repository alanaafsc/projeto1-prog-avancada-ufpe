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

Robot::Robot (string robot, Ambiente amb) {
    posicaoGrade = new int[2];

    //Declarar variável do arquivo config.txt:
    ifstream fileRobot;
    fileRobot.open(robot);

    //Iterar em cada linha do arquivo config
    string line;
    //Contagem de linhas:
    int linha = 0;

    if(fileRobot.is_open()) {
        while(getline(fileRobot,line)) {
        linha++;
        if(linha == 1) {
            nome = line;
        } else if(linha == 2) {
            posicaoGrade[0] = stoi(line);
        } else if(linha == 3) {
            posicaoGrade[1] = stoi(line);
        } else if(linha == 4) {
            bateria = new Bateria(stoi(line));
        }
        }
        fileRobot.close();
    }
};

void Robot::stopRobot() {

}
/*
int main () {
    //Arquivo de configuração do robô
    string file = "robot.txt";

    //Declaração do robô:
    Robot robot(file);

    return 0;
};
*/
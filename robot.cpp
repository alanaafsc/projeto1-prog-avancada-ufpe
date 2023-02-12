#include "robot.hpp"

using namespace std;

//Construtor usando dados do arquivo 
Robot::Robot (string robot, Ambiente &amb) {
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

    if(amb.getGrade()[posicaoGrade[0]][posicaoGrade[1]] != 'E') {
        amb.getGrade()[posicaoGrade[0]][posicaoGrade[1]] = 'R';
    }
};

//Metodo para parar o robô quando a bateria descarregar
void Robot::stopRobot() {
    // if(nivel == 0) {
    //     cout << "Robo descarregado, Favor recarregar";
    // }
};

int * Robot::getPosicaoGrade() {
    return posicaoGrade;
};

Bateria* Robot::getBateria() {
    return bateria;
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
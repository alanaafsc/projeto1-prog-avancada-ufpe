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
bool Robot::stopRobot() {
    if(bateria->getNivel() == 0) {
         cout << "Robô descarregado. Por favor, leve o robô para a estação de carregamento." << endl;

         return true;
    }

    return false;
};

int * Robot::getPosicaoGrade() {
    return posicaoGrade;
};

Bateria* Robot::getBateria() {
    return bateria;
}

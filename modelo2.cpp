#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include "robot.hpp"
#include "laser.hpp"
#include "ambiente.hpp"
#include "bateria.hpp"
using namespace std;

class Modelo2: public Robot {
    char orientacao;
    Laser *laser;
    public:
        Modelo2(string robot, Ambiente amb):Robot(robot, amb) {
            laser = new Laser();
        };
        void limpar(Ambiente &amb);
};

//Robô irá limpar o ambiente e terá uma nova direcão e orientacao:
void Modelo2::limpar (Ambiente &amb) {

    // Deslocamentos para as 8 direções
    const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

   // Posição inicial do robô
    int robotPositionX = getPosicaoGrade()[0];
    int robotPositionY = getPosicaoGrade()[1];

    // Direção inicial do robô (0 = norte, 1 = nordeste, 2 = leste, 3 = sudeste, 4 = sul, 5 = sudoeste, 6 = oeste, 7 = noroeste)
    int dir = rand() % 8;
    // Move o robô em uma direção aleatória
    // robotPositionX += dx[dir];
    // robotPositionY += dy[dir];

    // Loop principal para movimentar o robô
    while (true) {

        // Verifica se há obstáculo na direção atual do robô
        int new_x = robotPositionX + dx[dir];
        int new_y = robotPositionY + dy[dir];
     
        cout << new_x << " " << new_y << endl;
        bool visited = false;
        bool loop = true;
        while(loop) {
            if (new_x < 0 || new_x >= amb.getDimensoes()[0] || new_y < 0 || new_y >= amb.getDimensoes()[1] || 
            amb.getGrade()[new_x][new_y] == '1') {
                cout << "entrou aqui nesse if" << endl;
                dir = (dir + 1) % 8;
                new_x = robotPositionX + dx[dir];
                new_y = robotPositionY + dy[dir];
            } else {
                while(visited) {
                    //verifica se celula ja foi visitada:
                    if(amb.getVisited()[new_x][new_y] == true) {
                        //escolher outra direcao
                        dir = rand() % 4;
                        new_x = robotPositionX + dx[dir];
                        new_y = robotPositionY + dy[dir];
                    } else {
                        visited = false;
                        break;
                    }
                }
                cout << "entra aquiii" << endl;
                break;
            }
        }
        cout << "tem que entrar aqui" << endl;
        // Move o robô na direção atual
        if (amb.getGrade()[robotPositionX][robotPositionY] != 'E') { 
            amb.getGrade()[robotPositionX][robotPositionY] = 'L';
        }    
        robotPositionX = new_x;
        robotPositionY = new_y;
        amb.getGrade()[robotPositionX][robotPositionY] = 'R';

        //adicionar em celula visitada:
        amb.getVisited()[robotPositionX][robotPositionY] == true;

        // Gira o robô 45 graus no sentido horário
        dir = (dir + 1) % 8;

        //descarregar robo a cada acao:
        bateria->descarregar();

        //printar ambiente e o nível atual de bateria:
        amb.printAmbiente();
        cout << "Nível de bateria: "<<bateria->getNivel() << endl;
        cout << "======================" << endl;
        sleep(1);
    }

};
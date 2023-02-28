#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <array>
#include <map>
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

// //Robô irá limpar o ambiente e terá uma nova direcão e orientacao:
void Modelo2::limpar (Ambiente &amb) {
   
    // mapeamento dos pares (x, y) para a quantidade de visitas
    map<pair<int, int>, int> mapaPares;

    // Deslocamentos para as 8 direções
    const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

   // Posição inicial do robô
    int robotPositionX = getPosicaoGrade()[0];
    int robotPositionY = getPosicaoGrade()[1];

    // Direção inicial do robô (0 = norte, 1 = nordeste, 2 = leste, 3 = sudeste, 4 = sul, 5 = sudoeste, 6 = oeste, 7 = noroeste)
    int dir = rand() % 8;

    // Loop principal para movimentar o robô
    while (true) {
        // Verifica se há obstáculo na direção atual do robô
        dir = rand() % 8;
        int new_x = robotPositionX + dx[dir];
        int new_y = robotPositionY + dy[dir];
        cout << new_x << " " << new_y << endl;
        bool visited = false;
        while (true) {
            if (new_x < 0 || new_x >= amb.getDimensoes()[0] || new_y < 0 || new_y >= amb.getDimensoes()[1] || 
                laser->calcularColisoes(amb, new_x, new_y) || amb.getGrade()[new_x][new_y] == 'E' || 
                mapaPares[make_pair(new_x, new_y)] > 4) {
                dir = rand() % 8;
                new_x = robotPositionX + dx[dir];
                new_y = robotPositionY + dy[dir];
            } else {
                visited = true;
                break;
            }
        }

        if (!visited) {
            // Todas as direções foram visitadas, não há mais células para limpar
            break;
        }

        // Move o robô na direção atual
        if (amb.getGrade()[robotPositionX][robotPositionY] != 'E') { 
            amb.getGrade()[robotPositionX][robotPositionY] = 'L';
        }    

        robotPositionX = new_x;
        robotPositionY = new_y;

        amb.getGrade()[robotPositionX][robotPositionY] = 'R';

        //adicionar em celula visitada:
        mapaPares[make_pair(robotPositionX, robotPositionY)]++;

        //descarregar robo a cada acao:
        bateria->descarregar();

        //printar ambiente e o nível atual de bateria:
        amb.printAmbiente();
        cout << "Nível de bateria: "<<bateria->getNivel() << endl;
        cout << "======================" << endl;
        sleep(1);

        if(stopRobot()) {
            string resposta;
            cout << "Bateria recarregada? Responda com 's' ou 'n' ";
            cin >> resposta;
            if(resposta == "s") {
                bateria->carregar();
            } else {
                cout << "Favor, carregar o robô" << endl;
                break;
            }
        }
    }
 };

#include "modelo1.hpp"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

void Modelo1::limpar(Ambiente &amb) {

    // Inicializando células a serem limpas na grade:
    vector<array<int, 2>> celulasParaLimpar;
    for (int i = 0; i < amb.getDimensoes()[0]; i++) {
        for (int j = 0; j < amb.getDimensoes()[1]; j++) {
            if (amb.getGrade()[i][j] == '0') {
                celulasParaLimpar.push_back({i, j});
            }
        }
    }

    //posicao do robo:
    int robotPositionX = getPosicaoGrade()[0];
    int robotPositionY = getPosicaoGrade()[1];
    
    while(!celulasParaLimpar.empty()) {
        // Direções de movimento
        const int dx[4] = {-1, 0, 1, 0};
        const int dy[4] = {0, 1, 0, -1};

        int menorDist = INT_MAX;
        int targetX, targetY;
        for (const auto &val : celulasParaLimpar) {
            int dist = abs(robotPositionX - val[0]) + abs(robotPositionY - val[1]);
            if (dist < menorDist) {
                menorDist = dist;
                targetX = val[0];
                targetY = val[1];
            }
        }
        //cout << "targetX " << targetX << " targetY " << targetY << endl; 
        // move o robô para a célula mais próxima
        // para em {2,0}; target {7,0}
        if (robotPositionX != targetX) {
            int direction = (robotPositionX < targetX) ? 1 : -1;
            while (robotPositionX != targetX) {
                int x = robotPositionX + direction;
                int y = robotPositionY;
                if (x >= 0 && x < amb.getDimensoes()[0] && y >= 0 && y < amb.getDimensoes()[1] && amb.getGrade()[x][y] != '1' 
                && amb.getGrade()[x][y] != 'E') {
                    if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                        amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    }  

                    robotPositionX = x;
                    amb.getGrade()[x][y] = 'R';
                    array<int, 2> target = {x, y};
                    auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                    if (it != celulasParaLimpar.end()) {
                        celulasParaLimpar.erase(it);
                    }
                    amb.printAmbiente();
                    cout << "======================" << endl;
                    sleep(1);
                } else {
                    if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                        amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    }  
                    array<int, 2> target = {robotPositionX, robotPositionY};
                    auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                    if (it != celulasParaLimpar.end()) {
                        celulasParaLimpar.erase(it);
                    }

                    if(robotPositionY == 0) {
                        robotPositionY++;
                    } else if(robotPositionY == 7) {
                        robotPositionY--;
                    } else {
                        robotPositionY++;
                    }
                    amb.getGrade()[robotPositionX][robotPositionY] = 'R';
                    //colocar print aq
                    break;
                }
            }
        } else if (robotPositionY != targetY) {
            int direction = (robotPositionY < targetY) ? 1 : -1;
            while (robotPositionY != targetY) {
                int x = robotPositionX;
                int y = robotPositionY + direction;
                
                if (x >= 0 && x < amb.getDimensoes()[0] && y >= 0 && y < amb.getDimensoes()[1] && amb.getGrade()[x][y] != '1' 
                && amb.getGrade()[x][y] != 'E') {
                    if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                        amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    }  
                    robotPositionY = y;
                    amb.getGrade()[x][y] = 'R';
                    array<int, 2> target = {x, y};
                    auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                    if (it != celulasParaLimpar.end()) {
                        celulasParaLimpar.erase(it);
                    }
                    amb.printAmbiente();
                    cout << "======================" << endl;
                    sleep(1);
                    } else {
                        if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                            amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                        }  
                        array<int, 2> target = {robotPositionX, robotPositionY};
                        auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                        if (it != celulasParaLimpar.end()) {
                            celulasParaLimpar.erase(it);
                        }

                        if(robotPositionX == 0) {
                            robotPositionX++;
                        } else if(robotPositionX == 7) {
                            robotPositionX--;
                        } else {
                            robotPositionX++;
                        }
                        amb.getGrade()[robotPositionX][robotPositionY] = 'R';
                        break;
                    }
                }
         }
    } 

    cout << "Ambiente limpo! " << endl;
}


#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
using namespace std;

class Laser {
    public: 
        bool calcularColisoes(Ambiente amb, int robotX, int robotY);
};

bool Laser::calcularColisoes(Ambiente amb, int robotX, int robotY) {
//O laser detecta a presenca de um obstaculo para qualquer
//célula adjacente

// Matriz de booleanos para armazenar a presença de obstáculos
bool has_obstacle[amb.getDimensoes()[0]][amb.getDimensoes()[1]];

// Loop para percorrer as células adjacentes
for (int i = robotX-1; i <= robotX+1; i++) {
    for (int j = robotY-1; j <= robotY+1; j++) {
        // Verifica se a célula está dentro da matriz
        if (i >= 0 && i < amb.getDimensoes()[0] && j >= 0 && j < amb.getDimensoes()[1]) {
            // Verifica se a célula é um obstáculo
            if (amb.getGrade()[i][j] == 1 || amb.getGrade()[i][j] == 'E') {
                // Há um obstáculo na célula (i, j)
                has_obstacle[i][j] = true;
            } else {
                // Não há obstáculo na célula (i, j)
                has_obstacle[i][j] = false;
            }
        }
    }
    return has_obstacle;
}
};
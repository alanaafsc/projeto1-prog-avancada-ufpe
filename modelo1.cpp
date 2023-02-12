#include "modelo1.hpp"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;
/*
//Metodo para o robô limpar o ambiente e tomar uma nova direcao
//Pode se mover nas quatro direcoes
void Modelo1::limpar (Ambiente &amb) {
    cout << "===================" << endl;
    bool escolherDirecao = true;
    while(escolherDirecao) {
        int posicaoRobo_x = posicaoGrade[0]; //posicao x do robo
        // cout << posicaoRobo_x << endl;
        int posicaoRobo_y = posicaoGrade[1]; //posicao y do robo
        // cout << posicaoRobo_y << endl;
        int *leftCell = new int[2];
        int *upCell = new int[2];
        int *rightCell = new int[2];
        int *downCell = new int[2];

        //Robo na ponta da grade ou nas bordas, necessario direcionar para que nao extrapole os indices de posicao da grade:
        if(posicaoRobo_x == 0 && posicaoRobo_y == 0) {
            //direcionar leftCell e upCell:
            leftCell[0] = posicaoRobo_x;
            leftCell[1] = 7;
            upCell[0] = 7;
            upCell[1] = posicaoRobo_y;

            downCell[0] = posicaoRobo_x + 1;
            downCell[1] = posicaoRobo_y;
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = posicaoRobo_y + 1;
        } else if(posicaoRobo_x == 0 && posicaoRobo_y == 7) {
            //direcionar rightCell e upCell
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = 0;
            upCell[0] = 7;
            upCell[1] = posicaoRobo_y;

            leftCell[0] = posicaoRobo_x;
            leftCell[1] = posicaoRobo_y - 1;
            downCell[0] = posicaoRobo_x + 1;
            downCell[1] = posicaoRobo_y;
        } else if(posicaoRobo_x == 7 && posicaoRobo_y == 0) {
            //direcionar leftCell e downCell
            leftCell[0] = posicaoRobo_x;
            leftCell[1] = 7;
            downCell[0] = 0;
            downCell[1] = posicaoRobo_y;

            rightCell[0] = posicaoRobo_x;
            rightCell[1] = posicaoRobo_y + 1;
            upCell [0] = posicaoRobo_x - 1;
            upCell[1] = posicaoRobo_y;
        } else if(posicaoRobo_x == 7 && posicaoRobo_y == 7) {
            //direcionar rightCell e downCell
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = 0;
            downCell[0] = 0;
            downCell[1] = posicaoRobo_y;

            leftCell[0] = posicaoRobo_x;
            leftCell[1] = posicaoRobo_y - 1;
            upCell[0] = posicaoRobo_x -1;
            upCell[1] = posicaoRobo_y;
        } else if(posicaoRobo_x == 0) {
            //direcionar upCell
            upCell[0] = 7;
            upCell[1] = posicaoRobo_y;

            downCell[0] = posicaoRobo_x + 1;
            downCell[1] = posicaoRobo_y;
            leftCell[0] = posicaoRobo_x;
            leftCell[1] = posicaoRobo_y - 1;
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = posicaoRobo_y + 1;
        } else if(posicaoRobo_x == 7) {
            //direcionar downCell
            downCell[0] = 0;
            downCell[1] = posicaoRobo_y;

            leftCell[0] = posicaoRobo_x;
            leftCell[1] = posicaoRobo_y - 1;
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = posicaoRobo_y + 1;
            upCell[0] = posicaoRobo_x - 1;
            upCell[1] = posicaoRobo_y;
        } else if(posicaoRobo_y == 0) {
            //direcionar leftCell
            leftCell[0] = posicaoRobo_x;
            leftCell[1] = 7;

            rightCell[0] = posicaoRobo_x;
            rightCell[1] = posicaoRobo_y + 1;
            upCell[0] = posicaoRobo_x - 1;
            upCell[1] = posicaoRobo_y;
            downCell[0] = posicaoRobo_x + 1;
            downCell[1] = posicaoRobo_y;
        } else if(posicaoRobo_y == 7) {
            //direcionar rightCell
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = 0;

            upCell[0] = posicaoRobo_x - 1;
            upCell[1] = posicaoRobo_y;
            downCell[0] = posicaoRobo_x + 1;
            downCell[1] = posicaoRobo_y;
            leftCell[0] = posicaoRobo_x;
            leftCell[1] = posicaoRobo_y - 1;
        } else {
            //celula a esquerda do robo
            leftCell[0] = posicaoRobo_x;
            leftCell[1] = posicaoRobo_y-1;
            //celula a direita do robo
            rightCell[0] = posicaoRobo_x;
            rightCell[1] = posicaoRobo_y+1;
            //celula acima do robo
            upCell[0] = posicaoRobo_x-1;
            upCell[1] = posicaoRobo_y;
            //celula abaixo do robo
            downCell[0] = posicaoRobo_x+1;
            downCell[1] = posicaoRobo_y;
        }

        //celula que o robo irá, dependendo do resultado das colisoes que serao calculadas pelo parachoque:
        int celulaEscolhida[2];
        bool celulaEscolhidaVazia = true;
        while(true) {
            //escolher direção aleatoriamente:
            int direcao = rand() % 4; //0 1 2 3 -> representa UP RIGHT DOWN LEFT
            bool obstaculo;
            vector< int > arr;
            arr.push_back(direcao);

            //verificar as 4 direcoes que o robo pode seguir:
            if(direcao == 0 && amb.getGrade()[upCell[0]][upCell[1]] != 'L' && amb.getGrade()[upCell[0]][upCell[1]] != 'E') {
                obstaculo = parachoque->calcularColisoes(amb, upCell);
                if(obstaculo) {
                    continue;
                }
                celulaEscolhida[0] = upCell[0];
                celulaEscolhida[1] = upCell[1];
                celulaEscolhidaVazia = false;
                break;
            } else if(direcao == 1 && amb.getGrade()[rightCell[0]][rightCell[1]] != 'L' && amb.getGrade()[rightCell[0]][rightCell[1]] != 'E') {
                obstaculo = parachoque->calcularColisoes(amb, rightCell);
                if(obstaculo) {
                    continue;
                }
                celulaEscolhida[0] = rightCell[0];
                celulaEscolhida[1] = rightCell[1];
                celulaEscolhidaVazia = false;
                break;
            } else if(direcao == 2 && amb.getGrade()[downCell[0]][downCell[1]] != 'L' && amb.getGrade()[downCell[0]][downCell[1]] != 'E') {
                obstaculo = parachoque->calcularColisoes(amb, downCell);
                if(obstaculo) {
                    continue;
                }
                celulaEscolhida[0] = downCell[0];
                celulaEscolhida[1] = downCell[1];
                celulaEscolhidaVazia = false;
                break;
            } else if(direcao == 3 && amb.getGrade()[leftCell[0]][leftCell[1]] != 'L' && amb.getGrade()[leftCell[0]][leftCell[1]] != 'E') {
                obstaculo = parachoque->calcularColisoes(amb, leftCell);
                if(obstaculo) {
                    continue;
                }
                celulaEscolhida[0] = leftCell[0];
                celulaEscolhida[1] = leftCell[1];
                celulaEscolhidaVazia = false;
                break;
            }

            int target[2];
            //4 direcoes que o robô pode tomar esta com celula limpa:
            if(arr.size() == 4) {
                for(int i = 0; i < amb.getDimensoes()[0]; i++) {
                    for(int j = 0; j < amb.getDimensoes()[1]; j++) {
                        if(amb.getGrade()[i][j] == '0') {
                            target[0] = i;
                            target[1] = j;
                            if(i > posicaoRobo_x) {
                                if(posicaoRobo_x == 7) {
                                    celulaEscolhida[0] = 0;
                                } else {
                                    celulaEscolhida[0] = posicaoRobo_x + 1;
                                }
                            } else {
                                if(posicaoRobo_x == 0) {
                                    celulaEscolhida[0] = 7;
                                } else {
                                 celulaEscolhida[0] = posicaoRobo_x - 1;
                                }
                            }

                            if(j > posicaoRobo_y) {
                                if(posicaoRobo_y == 7) {
                                    celulaEscolhida[1] = 0;
                                } else {
                                    celulaEscolhida[1] = posicaoRobo_y + 1;
                                }
                            } else {
                                if(posicaoRobo_y == 0) {
                                    celulaEscolhida[1] = 7;
                                } else {
                                    celulaEscolhida[1] = posicaoRobo_y - 1;
                                }
                            }
                        }
                        break;
                    }
                }
                escolherDirecao = false;
                break;
                // if(find(arr.begin(), arr.end(), arr[0]) != arr.end() && find(arr.begin(), arr.end(), arr[1]) != arr.end() && find(arr.begin(), arr.end(), arr[2]) != arr.end()
                // && find(arr.begin(), arr.end(), arr[3]) != arr.end()) {
                //     escolherDirecao = false;
                //     break;
                // }
            }
        }

        // Robô vai pra celulaEscolhida e depois que sair dela, terá o L no lugar da célula onde estava (significando que ele limpou aquela célula)
        // Caso célula esteja preenchida com E, significa que está no lugar de carregamento, portanto, não precisa colocar L
        if(amb.getGrade()[posicaoRobo_x][posicaoRobo_y] != 'E') {
            amb.getGrade()[posicaoRobo_x][posicaoRobo_y] = 'L';
        }

        //atribuindo nova célula a posicao do robô:
        posicaoGrade[0] = celulaEscolhida[0];
        posicaoGrade[1] = celulaEscolhida[1];
        //Nova posicao do robo:
        amb.getGrade()[posicaoGrade[0]][posicaoGrade[1]] = 'R';

        //printar ambiente
        amb.printAmbiente();
        //diminuir 1 unidade do nivel de bateria
        bateria->descarregar();
        cout << "Nível de bateria: " << bateria->getNivel() << endl;
        sleep(1);

        if(bateria->getNivel() == 0) {
            cout << "Bateria do robô esta zerada. Coloque-o novamente na estação de carregamento";
            break;
        }
        if(!escolherDirecao) {
            break;
        }
    }

};
*/


void Modelo1::limpar(Ambiente &amb) {

    //inializando celulas a serem limpas na grade:

    vector<array<int, 2>> *celulasParaLimpar = new vector<array<int, 2>>();
    for(int i = 0; i < amb.getDimensoes()[0]; i++) {
        for(int j = 0; j < amb.getDimensoes()[1]; j++) {
            if(amb.getGrade()[i][j] == '0') {
                celulasParaLimpar->push_back({i,j});
            }
        }
    }
    /*
    for (const auto &val : *celulasParaLimpar) {
        cout << "(" << val[0] << "," << val[1] << ")" << endl;
    } */

    //posicao do robo:
    int robotPositionX = getPosicaoGrade()[0];
    int robotPositionY = getPosicaoGrade()[1];
    
    while(!celulasParaLimpar->empty()) {
        // Direções de movimento
        const int dx[4] = {-1, 0, 1, 0};
        const int dy[4] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int x = robotPositionX + dx[i];
            int y = robotPositionY + dy[i];
            // bool verifica = (x >= 0 && x < amb.getDimensoes()[0] && y >= 0 && y < amb.getDimensoes()[1] && amb.getGrade()[x][y] == '0');
            // cout << verifica << endl;

            if (x >= 0 && x < amb.getDimensoes()[0] && y >= 0 && y < amb.getDimensoes()[1] && amb.getGrade()[x][y] ==0) {
                if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {

                    amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    array<int, 2> target = {robotPositionX, robotPositionY};
                    auto it = find(celulasParaLimpar->begin(), celulasParaLimpar->end(), target);
                    if (it != celulasParaLimpar->end()) {
                        celulasParaLimpar->erase(it);
                    }
                } 
                amb.getGrade()[x][y] = 'R';
                robotPositionX = x;
                robotPositionY = y;
            }
            sleep(2);
            amb.printAmbiente();
            cout << "========================" << endl;
        }
       
    }
}
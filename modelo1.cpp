#include "modelo1.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

void Modelo1::limpar(Ambiente &amb) {

    // Inicializando células a serem limpas na grade:
    vector<array<int, 2> > celulasParaLimpar;
    for (int i = 0; i < amb.getDimensoes()[0]; i++) {
        for (int j = 0; j < amb.getDimensoes()[1]; j++) {
            if (amb.getGrade()[i][j] == '0') {
                array<int,2> array = {i,j};
                celulasParaLimpar.push_back(array);
            }
        }
    }

    //posicao do robo:
    int robotPositionX = getPosicaoGrade()[0];
    int robotPositionY = getPosicaoGrade()[1];

    //enquanto vector com células a serem limpas estiver com algum elemento, significa que 
    //o robô precisa continuar limpando o ambiente
    while(!celulasParaLimpar.empty() && !stopRobot()) {
        // Direções de movimento
        const int dx[4] = {-1, 0, 1, 0};
        const int dy[4] = {0, 1, 0, -1};

        //lógica para obter qual celula do vector de celulas a serem limpas tem a menor distancia da posicao do robô
        //com isso, ele irá seguir um caminho para chegar na célula mais próxima a ser limpa (target)
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

        cout << "targets: " << targetX << " " << targetY << endl;
        cout << "robo " << robotPositionX << " " << robotPositionY<<endl;
        //chegar no x da celula a ser limpa
        if (robotPositionX != targetX) {
            //caso linha do robo seja menor que a linha do target, sua linha será aumentada em um valor; caso não, -1
            int direction = (robotPositionX < targetX) ? 1 : -1;
            while (robotPositionX != targetX) {
                //nova posicao do robo para chegar mais proximo ao target
                int x = robotPositionX + direction;
                int y = robotPositionY;
                cout << "direcoes " << x << " " << y << endl;
                //limitações para o robô não entrar numa célula com obstáculo ou que tenha a estação de carregamento;
                //limita, também, do robô parar em algum indice fora da grade
                if (x >= 0 && x < amb.getDimensoes()[0] && y >= 0 && y < amb.getDimensoes()[1] && !(parachoque->calcularColisoes(amb, x, y))
                && amb.getGrade()[x][y] != 'E') {
                    //célula de estação de carregamento não terá o valor de L (limpo) quando robô sair dela:
                    if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                        cout << "entrou aqui " << endl;
                        amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    }  
                    //nova posição em x do robo:
                    robotPositionX = x;
                    amb.getGrade()[x][y] = 'R';

                    //após essa ação, robo tera sua bateria diminuida em um nivel:
                    bateria->descarregar();

                    //retirar célula limpa do vector de células a serem limpas:
                    array<int, 2> target = {x, y};
                    auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                    if (it != celulasParaLimpar.end()) {
                        celulasParaLimpar.erase(it);
                    }

                    //printar ambiente e o nível atual de bateria:
                    amb.printAmbiente();
                    cout << "Nível de bateria: "<<bateria->getNivel() << endl;
                    cout << "======================" << endl;
                    sleep(1);
                    //verificacao do nivel do robo e se é necessário ele parar para ser carregado:
                    if(stopRobot()) {
                       string resposta;
                        cout << "Bateria recarregada? Responda com 's' ou 'n' ";
                        cin >> resposta;
                        if(resposta == "s") {
                            bateria->carregar();
                            if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                        cout << "entrou aqui 2" << endl;

                                amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                            } 
                            robotPositionX = amb.getPosicaoCarregamento()[0];
                            robotPositionY = amb.getPosicaoCarregamento()[1];
                            break;
                        } else {
                            cout << "Favor, carregar o robô" << endl;
                            if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                        cout << "entrou aqui 3" << endl;

                                amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                            } 
                            break;
                        }
                    }
                } else {
                    //caso o robo precise passar por uma posicao x,y que seja o limite da grade:

                    //limpa a celula que ele está quando sair para ir para x,y:
                    if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                cout << "entrou aqui 4" << endl;

                        amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    }  

                    //retira célula limpa do vector celulasParaLimpar:
                    array<int, 2> target = {robotPositionX, robotPositionY};
                    auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                    if (it != celulasParaLimpar.end()) {
                        celulasParaLimpar.erase(it);
                    }

                    //caso robo esteja na primeira coluna e não consiga ir para a proxima celula x,y pois tem um E ou um 1 (obstaculo):
                    if(robotPositionY == 0 && amb.getGrade()[robotPositionX][robotPositionY+1] != '1' && amb.getGrade()[robotPositionX][robotPositionY+1] != 'E') {
                                                cout << "entrou aqui 5" << endl;

                        robotPositionY++;
                        //caso o robo esteja na ultima coluna:
                    } else if(robotPositionY == 7 && amb.getGrade()[robotPositionX][robotPositionY-1] != '1' && amb.getGrade()[robotPositionX][robotPositionY-1] != 'E') {
                                                cout << "entrou aqui 6" << endl;

                        robotPositionY--;
                        //caso esteja no meio da grade:
                    } else {
                        int directionY = (robotPositionY < targetY) ? 1 : -1;
                        int directionX = (robotPositionX < targetX) ? 1 : -1;
 
                        if(amb.getGrade()[robotPositionX][robotPositionY+(directionY)] != '1' 
                        && amb.getGrade()[robotPositionX][robotPositionY+(directionY)] != 'E') {
                            robotPositionY += directionY;
                        } else if(amb.getGrade()[robotPositionX+(directionX)][robotPositionY] != '1' 
                        && amb.getGrade()[robotPositionX+(directionX)][robotPositionY] != 'E') {
                            robotPositionX += direction;
                        }
                    }

                    //nova posicao do robo
                    amb.getGrade()[robotPositionX][robotPositionY] = 'R';

                    //após essa ação, robo tera sua bateria diminuida em um nivel:
                    bateria->descarregar();

                    //printar ambiente e o nível atual de bateria:
                    amb.printAmbiente();
                    cout << "Nível de bateria: "<<bateria->getNivel() << endl;
                    cout << "======================" << endl;
                    sleep(1);

                    //verificacao do nivel do robo e se é necessário ele parar para ser carregado:
                    if(stopRobot()) {
                       string resposta;
                        cout << "Bateria recarregada? Responda com 's' ou 'n' ";
                        cin >> resposta;
                        if(resposta == "s") {
                            bateria->carregar();
                            if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                        cout << "entrou aqui 8" << endl;

                                amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                            } 
                            robotPositionX = amb.getPosicaoCarregamento()[0];
                            robotPositionY = amb.getPosicaoCarregamento()[1];
                        } else {
                            cout << "Favor, carregar o robô" << endl;
                            if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                        cout << "entrou aqui 9" << endl;

                                amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                            } 
                            break;
                        }
                    }

                    break;
                }
            }
            //chegar no y da celula a ser limpa:
        } else if (robotPositionY != targetY) {
            //caso coluna do robo seja menor que a coluna do target, sua coluna será aumentada em um valor; caso não, -1
            int direction = (robotPositionY < targetY) ? 1 : -1;
            while (robotPositionY != targetY) {
                //nova posicao do robo para chegar mais proximo do target (ou ir para o target)
                int x = robotPositionX;
                int y = robotPositionY + direction;

                //limitacoes para o robo nao ir para indice fora da grade ou para obstaculos:
                if (x >= 0 && x < amb.getDimensoes()[0] && y >= 0 && y < amb.getDimensoes()[1] && !(parachoque->calcularColisoes(amb, x, y)) 
                && amb.getGrade()[x][y] != 'E') {
                    if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                cout << "entrou aqui 10" << endl;

                        amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                    }  

                    //nova posicao do robo:
                    robotPositionY = y;
                    amb.getGrade()[x][y] = 'R';

                    //retirar célula limpa do vector de células a serem limpas:
                    array<int, 2> target = {x, y};
                    auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                    if (it != celulasParaLimpar.end()) {
                        celulasParaLimpar.erase(it);
                    }

                    //após essa ação, robo tera sua bateria diminuida em um nivel:
                    bateria->descarregar();

                   //printar ambiente e o nível atual de bateria:
                    amb.printAmbiente();
                    cout << "Nível de bateria: "<<bateria->getNivel() << endl;
                    cout << "======================" << endl;
                    sleep(1);

                    //verificacao do nivel do robo e se é necessário ele parar para ser carregado:
                    if(stopRobot()) {
                        string resposta;
                            cout << "Bateria recarregada? Responda com 's' ou 'n' ";
                            cin >> resposta;
                            if(resposta == "s") {
                                bateria->carregar();
                                if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                            cout << "entrou aqui 11" << endl;

                                    amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                                } 
                                robotPositionX = amb.getPosicaoCarregamento()[0];
                                robotPositionY = amb.getPosicaoCarregamento()[1];
                            } else {
                                cout << "Favor, carregar o robô" << endl;
                                if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                            cout << "entrou aqui 12" << endl;

                                    amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                                } 
                                break;
                            }
                        }

                    } else {
                        //caso o robo precise passar por uma posicao x,y que seja o limite da grade:

                        //limpa a celula que ele está quando sair para ir para x,y:
                        if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                    cout << "entrou aqui 13" << endl;

                            amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                        }  

                        //retirar célula limpa do vector de células a serem limpas:
                        array<int, 2> target = {robotPositionX, robotPositionY};
                        auto it = find(celulasParaLimpar.begin(), celulasParaLimpar.end(), target);
                        if (it != celulasParaLimpar.end()) {
                            celulasParaLimpar.erase(it);
                        }
                        
                        //caso o robo esteja com um y que dê para uma célula com obstaculo ou estacao de carregamento, 
                        //ele tera seu indice x incrementado ou diminuido, dependendo da situacao:
                        if(robotPositionX == 0 && amb.getGrade()[robotPositionX+1][robotPositionY] != '1' && amb.getGrade()[robotPositionX+1][robotPositionY] != 'E') {
                            robotPositionX++;
                                                    cout << "entrou aqui 14" << endl;

                        } else if(robotPositionX == 7 && amb.getGrade()[robotPositionX-1][robotPositionY] != '1' && amb.getGrade()[robotPositionX-1][robotPositionY] != 'E') {
                            robotPositionX--;
                                                    cout << "entrou aqui 15" << endl;

                        } else if(amb.getGrade()[robotPositionX+1][robotPositionY] != '1' && amb.getGrade()[robotPositionX+1][robotPositionY] != 'E'){
                            robotPositionX++;
                                                    cout << "entrou aqui 16" << endl;

                        }
                        amb.getGrade()[robotPositionX][robotPositionY] = 'R';

                        //após essa ação, robo tera sua bateria diminuida em um nivel:
                        bateria->descarregar();

                        //printar ambiente e o nível atual de bateria:
                        amb.printAmbiente();
                        cout << "Nível de bateria: "<<bateria->getNivel() << endl;
                        cout << "======================" << endl;
                        sleep(1);

                        //verificacao do nivel do robo e se é necessário ele parar para ser carregado:
                        if(stopRobot()) {
                        string resposta;
                        cout << "Bateria recarregada? Responda com 's' ou 'n' ";
                        cin >> resposta;
                        if(resposta == "s") {
                            bateria->carregar();
                            if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                        cout << "entrou aqui 17" << endl;

                                amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                            } 
                            robotPositionX = amb.getPosicaoCarregamento()[0];
                            robotPositionY = amb.getPosicaoCarregamento()[1];
                        } else {
                            cout << "Favor, carregar o robô" << endl;
                            if(amb.getGrade()[robotPositionX][robotPositionY] != 'E') {
                                                        cout << "entrou aqui 18" << endl;

                                amb.getGrade()[robotPositionX][robotPositionY] = 'L';
                            } 
                            break;
                        }
                    }

                        break;
                    }
                }
         }
    } 
    if(!stopRobot()) {
        cout << "Ambiente limpo! " << endl;
    }
}


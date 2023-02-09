#include "modelo1.hpp"
#include <unistd.h>
#include <vector>

using namespace std;

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

            //não há mais células a serem limpas:
            if(arr.size() == 4) {
                if(find(arr.begin(), arr.end(), arr[0]) != arr.end() && find(arr.begin(), arr.end(), arr[1]) != arr.end() && find(arr.begin(), arr.end(), arr[2]) != arr.end()
                && find(arr.begin(), arr.end(), arr[3]) != arr.end()) {
                    escolherDirecao = false;
                    break;
                }
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
        sleep(5);
       
        if(bateria->getNivel() == 0) {
            cout << "Bateria do robô esta zerada. Coloque-o novamente na estação de carregamento";
            break;
        }
    }
    
};
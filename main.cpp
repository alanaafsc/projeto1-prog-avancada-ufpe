#include <iostream>
#include <fstream>
#include <string> 
#include "ambiente.hpp"
#include "bateria.hpp"
#include "laser.hpp"
#include "modelo1.hpp"
#include "modelo2.hpp"
#include "parachoque.hpp"
#include "robot.hpp"
using namespace std;

int main () {
    //Arquivo de configuração do ambiente
    string fileAmb = "config.txt";

    //Declaração do ambiente:
    Ambiente amb(fileAmb);

    //Arquivo de configuração do robô
    string fileRobot = "robot.txt";

    //Declaração do robô:
    Modelo1 modelo1(fileRobot, amb);

    //  Adição de obstáculo:
    // int obstaculo1[2] = {3,0};
    // int obstaculo2[2] = {3,1};
    // int obstaculo3[2] = {3,2};
    // int obstaculo4[2] = {3,3};
    // int obstaculo5[2] = {3,4};
    // int obstaculo6[2] = {4,4};
    // int obstaculo7[2] = {5,4};
    // amb.addObstaculo(obstaculo1);
    // amb.addObstaculo(obstaculo2);
    // amb.addObstaculo(obstaculo3);
    // amb.addObstaculo(obstaculo4);
    // amb.addObstaculo(obstaculo5);
    // amb.addObstaculo(obstaculo6);
    // amb.addObstaculo(obstaculo7);


    //testando obstaculo com retangulo
    int obstaculoRec1[2] = {2,7};
    int obstaculoRec2[2] = {4,4};
     amb.addObstaculo(obstaculoRec1, obstaculoRec2);
  
    amb.printAmbiente();

    return 0;
}
//Feito:
//Classe ambiente
//Classe robo -> falta metodo parar e definir bateria
//Classe modelo1: herda do robo, falta fazer metodo do parachoque e entender como fazer metodo limpar e escolher direcao
//Classe modelo2: herda do robo, n sei o que seria atributo orientacao, precisa fazer metodo do laser, e metodo limpar do modelo2
//Classe bateria: Fazer metodo descarregar e carregar
//Classe parachoque: fazer metodo calcularColisoes
//Classe laser: fazer metodo calcularColisoes
//Estacao como ponto de partida, escolhe uma direcao e se move em linha reta ate achar obstaculo. Obstaculo detectado por sensor (laser ou parachoque).
    //robo atinge estado critico de bateria (definir isso) e volta pra estacao de carregamento.
    //se descarregar, ele para 
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
    // posicao atual do robô:
    int posicaoRobo_x = modelo1.getPosicaoGrade()[0];
    int posicaoRobo_y = modelo1.getPosicaoGrade()[1];

    //definindo obstaculos:
    int obstaculoRec1[2] = {3,0};
    int obstaculoRec2[2] = {3,4};
    int obstaculo1[2] = {4,4};
    int obstaculo2[2] = {5,4};
    //adicionando obstaculos ao ambiente:
    amb.addObstaculo(obstaculoRec1, obstaculoRec2);
    amb.addObstaculo(obstaculo1);
    amb.addObstaculo(obstaculo2);
    
    amb.printAmbiente();
    modelo1.limpar(amb);
    // string resposta;
    // cout << "Robô foi totalmente carregado? ";
    // cin >> resposta;
    // if(resposta == "sim") {
    // modelo1.limpar(amb);
    //     modelo1.getBateria()->carregar();
    // }
    
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
// novas coisas pra fazer: 08/02
// mudar nivel de bateria para 10 novamente dentro do txt, pq eh de la q ele chama -> na classe Bateria
// ver uma logica que, quando chegar no momento onde Robo esteja com 4 celulas adjacentes limpas, procurar mesmo assim se ha celulas sujas (0)
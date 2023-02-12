#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <math.h>
using namespace std;

class Ambiente {
  int * dimensoes;
  char ** grade;
  int * posicaoCarregamento;
  bool ** visited;
public:
  Ambiente(string config);
  void addObstaculo(int obstaculo[2]);
  void addObstaculo(int obstaculo1[2], int obstaculo2[2]);
  void printAmbiente() {
    cout << "Ambiente: " << endl;
    for(int i = 0; i < dimensoes[0]; i++) {
    for(int j = 0; j < dimensoes[1]; j++) { 
    cout << grade[i][j] << " ";
    }
    cout << endl;
  }
  };
  char ** getGrade() {
    return grade;
  };
  int * getPosicaoCarregamento() {
    return posicaoCarregamento;
  };
  int * getDimensoes() {
    return dimensoes;
  };

  bool ** getVisited() {
    return visited;
  }
};

Ambiente::Ambiente (string config) {
  //Inicializar atributos de ambiente:
  dimensoes = new int [2];
  posicaoCarregamento = new int[2];

  //Declarar variável do arquivo config.txt:
  ifstream myfile;
  myfile.open(config);

  //Iterar em cada linha do arquivo config
  string line;
  //Contagem de linhas:
  int linha = 0;

  if(myfile.is_open()) {
    while(getline(myfile,line)) {
      linha++;
      if(linha == 1) {
        dimensoes[0] = stoi(line);
      } else if(linha == 2) {
        dimensoes[1] = stoi(line);
      } else if(linha == 3) {
        posicaoCarregamento[0] = stoi(line);
      } else if(linha == 4) {
        posicaoCarregamento[1] = stoi(line);
      }
    }
    myfile.close();
  }

  int xGrade = dimensoes[0];
  int yGrade = dimensoes[1];

  //Definindo matriz do ambiente:
  grade = new char*[xGrade];
  for(int i = 0; i < xGrade; i++) {
    grade[i] = new char[yGrade];
  }

  //matriz do ambiente para mapear células visitadas pelo robô:
  visited = new bool*[xGrade];
  for(int i = 0; i < xGrade; i++) {
    visited[i] = new bool[yGrade];
  } 

  //Definindo grade sem obstáculos e com a posição de carregamento:
  for(int i = 0; i < xGrade; i++) {
    for(int j = 0; j< yGrade; j++) { 
      grade[i][j] = '0';
    }
  }

  //posicao de carregamento representado pelo numero 9, ja que n dá pra colocar um X pois grade é um ponteiro de int, não de char
  grade[posicaoCarregamento[0]][posicaoCarregamento[1]] = 'E';

};

void Ambiente::addObstaculo (int obstaculo[2]) {
  grade[obstaculo[0]][obstaculo[1]] = '1';
};

void Ambiente::addObstaculo (int obstaculo1[2], int obstaculo2[2]) {
  //Adicão de um retângulo de obstáculos 

  //Calculo da altura e largura do retângulo
  int altura = abs(obstaculo1[0] - obstaculo2[0]) + 1;
  int largura = abs(obstaculo1[1] - obstaculo2[1]) + 1;

  //Começando pelo obstaculo1:
  if(altura != 0 && largura != 0) {
    //Caso tenha largura e altura:
    //descer e ir para a direita
    if(obstaculo1[0] < obstaculo2[0] && obstaculo1[1] < obstaculo2[1]) {
      for(int i = obstaculo1[0]; i < (altura + obstaculo1[0]); i++) {
        for(int j = obstaculo1[1]; j < (obstaculo1[1] + largura); j++){
          if(grade[i][j] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
            grade[i][j] = '1';
          }
        }
      }
    } 
    //descer e ir para a esquerda
    else if (obstaculo1[0] < obstaculo2[0] && obstaculo1[1] > obstaculo2[1]) {
      for(int i = obstaculo1[0]; i < (obstaculo1[0] + altura); i++) {
        for(int j = obstaculo1[1]; j > (obstaculo1[1] - largura); j--){
          if(grade[i][j] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
            grade[i][j] = '1';
          }
        }
      }
    }
    //subir e ir para a direita 
    else if (obstaculo1[0] > obstaculo2[0] && obstaculo1[1] < obstaculo2[1]) {
        for(int i = obstaculo1[0]; i > (obstaculo1[0] - altura); i--) {
          for(int j = obstaculo1[1]; j < (obstaculo1[1] + largura); j++){
            if(grade[i][j] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
              grade[i][j] = '1';
            }
        }
      }
    } 
    //subir e ir para a esquerda
    else if (obstaculo1[0] > obstaculo2[0] && obstaculo1[1] > obstaculo2[1]) {
        for(int i = obstaculo1[0]; i > (obstaculo1[0] - altura); i--) {
          for(int j = obstaculo1[1];  j > (obstaculo1[1] - largura); j--){
            if(grade[i][j] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
              grade[i][j] = '1';
            }
          }
      }
    }
  }

  //Se não tiver largura ou altura:
  //pode ir apenas para o lado direito ou esquerdo
  if(altura == 1) {
    //pode ir para a direita
    if(obstaculo1[1] < obstaculo2[1]){
      for(int j = obstaculo1[1]; j < (obstaculo1[1] + largura); j++) {
        if(grade[obstaculo1[0]][j] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
          grade[obstaculo1[0]][j] = '1';
        }
      }
    } else {
      for(int j = obstaculo1[1]; j > obstaculo1[1] - largura; j--) {
       if(grade[obstaculo1[0]][j] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
          grade[obstaculo1[0]][j] = '1';
        } 
      } 
    }
  }
  //pode ir para cima ou para baixo
  if(largura == 1) {
      //pode ir para baixo
      if(obstaculo1[0] < obstaculo2[0]) {
      for(int i = obstaculo1[0]; i < (obstaculo1[0] + altura); i++) {
        if(grade[i][obstaculo1[1]] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
          grade[i][obstaculo1[1]] = '1';
        } 
      }
    } else {
      for(int i = obstaculo1[0]; i > obstaculo1[0] - altura; i--) {
        if(grade[i][obstaculo1[1]] != grade[posicaoCarregamento[0]][posicaoCarregamento[1]]) {
          grade[i][obstaculo1[1]] = '1';
        }
      }    
    }
  }
};

/*
int main() {
  //Arquivo de configuração do ambiente
  string file = "config.txt";

  //Declaração do ambiente:
  Ambiente amb(file);

  //Adição de obstáculo:
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
  // int obstaculoRec1[2] = {4,7};
  // int obstaculoRec2[2] = {4,4};
  // amb.addObstaculo(obstaculoRec1, obstaculoRec2);
  
  amb.printAmbiente();

  return 0;
}
*/
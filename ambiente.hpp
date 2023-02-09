#ifndef AMBIENTE_HPP
#define AMBIENTE_HPP

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <math.h>
using namespace std;

class Ambiente {
  int * dimensoes;
  char ** grade;
  int * posicaoCarregamento;
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
};

#endif

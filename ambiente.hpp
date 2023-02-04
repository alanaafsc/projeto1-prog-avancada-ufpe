#ifndef AMBIENTE_HPP
#define AMBIENTE_HPP

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <math.h>
using namespace std;

class Ambiente {
  int * dimensoes;
  int ** grade;
  int * posicaoCarregamento;
public:
  Ambiente(string config);
  void addObstaculo(int obstaculo[2]);
  void addObstaculo(int obstaculo1[2], int obstaculo2[2]);
  void printAmbiente();
};

#endif

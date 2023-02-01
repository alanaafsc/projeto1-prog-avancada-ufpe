#include <iostream>
#include <fstream>
using namespace std;

class Ambiente {
  int * dimensoes;
  int ** grade;
  int * posicaoCarregamento;
public:
  // Ambiente() {};
  Ambiente(string config);
  //tem que fazer sobrecarga aqui:
//  void addObstaculo(int obstaculo[2]);
//  void addObstaculoRetangulo(int obstaculo1[2], int obstaculo2[2]);
};

Ambiente::Ambiente (string config) {
  dimensoes = new int [2];
  posicaoCarregamento = new int[2];
  ifstream myfile;
  myfile.open(config);
  string line;
  int linha = 0;
  if(myfile.is_open()) {
    while(getline(myfile,line)) {
      linha++;
      if(linha = 1) {
        dimensoes[0] = stoi(line);
      } else if(linha = 2) {
        dimensoes[1] = stoi(line);
      } else if(linha = 3) {
        posicaoCarregamento[0] = stoi(line);
      } else if(linha = 4) {
        posicaoCarregamento[1] = stoi(line);
      }
    }
  myfile.close();
 }

  int xGrade = dimensoes[0];
  int yGrade = dimensoes[1];

  grade = new int*[xGrade];
  for(int i = 0; i < xGrade; i++) {
    grade[i] = new int[yGrade];
  }
};

int main() {
  string file = "config.txt";

  Ambiente amb(file);
  return 0;
}
/* void addObstaculo (int obstaculo[2]) {
  grade[obstaculo[0]][obstaculo[1]] = 1;
}

void addObstaculoRetangulo(int obstaculo1[2], int obstaculo2[2]) {

} */

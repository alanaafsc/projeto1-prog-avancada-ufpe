# Projeto 1 - Robô aspirador
Projeto 1 da disciplina de Programação Avançada da UFPE - CTG.


### Descrição do projeto
O objetivo deste projeto é desenvolver um simulador simples do robô Roomba. O robô Roomba é um robô
aspirador que utiliza uma estação de carregamento como ponto de partida e carrega sua bateria. A partir desta estação,
o robô se moverá aleatoriamente a fim de cobrir toda a superfície a ser limpa. Para isso, o robô escolhe
uma direção aleatória, depois se move em linha reta até encontrar um obstáculo. Os obstáculo são detectados
usando um sensor a bordo, como um para-choque ou um laser. O robô limpa a superfície até que sua bateria
atinja um nível crítico. Neste ponto, ele retornará a estação para carregar sua bateria. Se a bateria estiver
completamente descarregada, o robô para.

### Execução 

Compilar em um arquivo executável chamado program:

```
g++ -c ambiente.cpp bateria.cpp laser.cpp main.cpp modelo1.cpp modelo2.cpp parachoque.cpp robot.cpp
```


```
g++ -o program ambiente.o bateria.o laser.o main.o modelo1.o modelo2.o parachoque.o robot.o
```

executar: 
```
./program
```

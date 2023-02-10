#include <iostream>
#include <vector>
//codigo teste
const int ROWS = 5;
const int COLS = 5;

char room[ROWS][COLS];
bool visited[ROWS][COLS];

int startX, startY;
int chargingX, chargingY;

bool isValid(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS && room[row][col] == '0' && !visited[row][col];
}

void dfs(int x, int y) {
    if (!isValid(x, y)) {
        return;
    }

    visited[x][y] = true;
    room[x][y] = 'L';

    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}

int main() {
    // Inicializar o ambiente
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cin >> room[i][j];

            if (room[i][j] == '0') {
                startX = i;
                startY = j;
            } else if (room[i][j] == 'E') {
                chargingX = i;
                chargingY = j;
            }
        }
    }

    // Limpar o ambiente
    dfs(startX, startY);

    // Imprimir o ambiente limpo
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << room[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}


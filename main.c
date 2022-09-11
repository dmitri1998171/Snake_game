#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
#define WIDTH 20
#define HEIGHT 10

char map[HEIGHT][WIDTH];
/*char map[HEIGHT][WIDTH] =  {
    "00000000000000000000",
    "0                  0",
    "0                  0",
    "0                  0",
    "0                  0",
    "0                  0",
    "0                  0",
    "0                  0",
    "0                  0",
    "00000000000000000000"
};*/

void createMap() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                map[i][j] = '#';
            else
                map[i][j] = ' ';
        }
    }
}

void drawMap() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", map[i][j]);
        }
        
        printf("\n");
    }
}

int main(void) {
    int snakeSize = 5;
    char snake[5] = {"00000"};

    createMap();
    
/*
*/
    while(1) {
        drawMap();

        for (int i = 0; i < snakeSize; i++) {
            map[HEIGHT / 2][(WIDTH / 2) + i] = snake[i];
        }
        
        
        usleep(300);

        printf("\033[2J");      // Очистить терминал
        printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    }

    return 0;
}
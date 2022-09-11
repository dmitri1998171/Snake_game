#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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

void getKeyInput() {
    int key = getc(stdin);
        
        switch (key) {
            case 119:   // w
                
                break;
            
            case 115:   // s

                break;

            case 97:    // a
                
                break;
            
            case 100:   // d
            
                break;

            case 27:    // ESC
                exit(0);
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
        
        getKeyInput();
        
        usleep(300);

        printf("\033[2J");      // Очистить терминал
        printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    }

    return 0;
}
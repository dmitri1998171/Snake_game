#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
#define WIDTH 20
#define HEIGHT 10

char matrix[HEIGHT][WIDTH];
/*char matrix[HEIGHT][WIDTH] =  {
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
                matrix[i][j] = '0';
            else
                matrix[i][j] = ' ';
        }
    }
}

int main(void) {
    createMap();
    
/*
*/
    while(1) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                printf("%c", matrix[i][j]);
            }
            
            printf("\n");
        }
        
        usleep(300);

        printf("\033[2J");      // Очистить терминал
        printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    }

    return 0;
}
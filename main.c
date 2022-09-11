#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
#define WIDTH 80
#define HEIGHT 13

int matrix[WIDTH][HEIGHT];

void createMap() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) 
            matrix[i][j] = 0;
    }
}

int main(void)
{
    createMap();
    
/*
*/
    while(1) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) 
                printf("%d", matrix[i][j]);
            
            printf("\n");
        }
        
        usleep(300);

        printf("\033[2J");      // Очистить терминал
        printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    }

    return 0;
}
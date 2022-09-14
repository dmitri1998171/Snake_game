#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
 
#define WIDTH 20
#define HEIGHT 10

struct point {
    short x;
    short y;
};

struct point dir;
struct point curr_pos;

short loop = 1;
char map[HEIGHT][WIDTH];

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

void* getKeyInput(void *args) {
    pthread_detach(pthread_self());

    // Отключаем канонический режим ввода для stdin (отключаем нажатие Enter)
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, 0, &term);
    
    while(loop) {
        int key = getc(stdin);
            
        switch (key) {
            case 119:   // w
                dir.y = -1;
                //dir.x = 0;
                break;
            
            case 115:   // s
                dir.y = 1;
                //dir.x = 0;
                break;

            case 97:    // a
                //dir.y = 0;
                dir.x = -1;
                break;
            
            case 100:   // d
                //dir.y = 0;
                dir.x = 1;
                break;

            case 27:    // ESC
                loop = 0;
        }
    }

    return 0;
}

int main(void) {
    int snakeSize = 5;
    //char snake[5] = {"00000"};
    char coord_x[10], coord_y[10];
    
    dir.x = 1;
    dir.y = 0;

    curr_pos.x = 2;
    curr_pos.y = 2;

    int pos = 1;

    createMap();
    
    pthread_t thread;
    int status;
    int status_addr;
 
    status = pthread_create(&thread, NULL, getKeyInput, NULL);

    while(loop) {
        pos++;
        curr_pos.x = dir.x + pos;
        curr_pos.y = dir.y + pos;
        map[curr_pos.y][curr_pos.x] = ' ';

        for (int i = 0; i < snakeSize; i++) {
            map[curr_pos.y + 1][curr_pos.x + 1] = '0';
            curr_pos.x += dir.x;
            curr_pos.y += dir.y;
        }

        drawMap();

        sleep(1);
        //usleep(300);

        printf("\033[2J");      // Очистить терминал
        printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    }

/*
*/

    return 0;
}
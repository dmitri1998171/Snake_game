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

short loop;
short isNotEaten;
int score;
int lifes;
int snakeSize;
struct point dir;
struct point curr_pos;
struct point apple_pos;
char map[HEIGHT][WIDTH];
char *coord_x;
char *coord_y;

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
                dir.x = 0;
                break;
            
            case 115:   // s
                dir.y = 1;
                dir.x = 0;
                break;

            case 97:    // a
                dir.y = 0;
                dir.x = -1;
                break;
            
            case 100:   // d
                dir.y = 0;
                dir.x = 1;
                break;

            case 27:    // ESC
                loop = 0;
        }
    }

    return 0;
}

void moveSnake() {
    if(dir.x != 0) 
        curr_pos.x += dir.x;
    if(dir.y != 0) 
        curr_pos.y += dir.y;

    for (int i = 0; i < snakeSize; i++) {
        if(dir.x == 1)
            map[curr_pos.y][curr_pos.x + i] = coord_x[i];
        if(dir.x == -1)
            map[curr_pos.y][curr_pos.x - i] = coord_x[i];
    }

    for (int i = 0; i < snakeSize; i++) {
        if(dir.y == 1)
            map[curr_pos.y + i][curr_pos.x] = coord_y[i];
        if(dir.y == -1)
            map[curr_pos.y - i][curr_pos.x] = coord_y[i];
    }
}

void generateApple() {
    if(isNotEaten == 1) {
        apple_pos.x = 1 + rand() % (WIDTH - 2);
        apple_pos.y = 1 + rand() % (HEIGHT - 2);
    
        isNotEaten = 0;
    }

    map[apple_pos.y][apple_pos.x] = '*';
}

void checkCollision() {
    // An apple was eaten
    if(curr_pos.x == apple_pos.x && curr_pos.y == apple_pos.y) {
        score++;
        snakeSize++;
        isNotEaten = 1;

        coord_x = (char*) realloc(coord_x, snakeSize * sizeof(char));
        coord_x[snakeSize - 1] = 'o';
        
        coord_y = (char*) realloc(coord_y, snakeSize * sizeof(char));
        coord_y[snakeSize - 1] = 'o';
    }

    // Snake collide with itself or with walls
    if(curr_pos.x == 0 || curr_pos.x == WIDTH - 1 || curr_pos.y == 0 || curr_pos.y == HEIGHT - 1)
        lifes--;

    // GAME OVER
    if(lifes < 0) {
        for (int i = 0; i < HEIGHT; i++)
            memset(map[i], ' ', WIDTH);

        strcpy(map[HEIGHT / 2], "\tGAME OVER");
    }
}

int main(void) {
    printf("\033[2J");      // Очистить терминал
    printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    srand(time(NULL));
    
    pthread_t thread;
    int status;
    int status_addr;
    loop = 1;
    score = 0;
    lifes = 3;
    isNotEaten = 1;
    snakeSize = 2;
    curr_pos.x = 5;
    curr_pos.y = 5;
    dir.x = 1;
    dir.y = 0;

    coord_x = (char*) malloc(2);
    coord_y = (char*) malloc(2);

    for (int i = 0; i < snakeSize; i++)
        coord_x[i] = coord_y[i] = 'o';

 
    status = pthread_create(&thread, NULL, getKeyInput, NULL);

    while(loop) {
        createMap();
        generateApple();
        moveSnake();
        checkCollision();
        drawMap();
        
        printf("\nScore: %d  Lifes: %d\n", score, lifes);

        sleep(1);
        //usleep(300);

        printf("\033[2J");      // Очистить терминал
        printf("\033[0;0f");    // Перевести каретку в левое верхнее положение
    }

    return 0;
}
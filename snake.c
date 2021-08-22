#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char board[12][12];
int snakeX[12] = {0, 0, 0, 0}; // snake and tail X position
int snakeY[12] = {0, 1, 2, 3}; // snake and tail Y position
int foodX, foodY; // food X position and food Y position

char boardPattern = '.';
char snake = '#';
char food = '@';

int length = 4; // snake length
int box = 12; // matrix
char key = 'd'; // current key in buffer

int main()
{
    void createBoard();
    void createFood();
    void draw();
    void refill();
    void input();
    void move();
    void createSnake();
    int hasEatenFood();
    void addTail();
    
    createBoard();
    createFood();
    
    while(true)
    {
        clrscr();
        createSnake();
        draw(box);
        refill();
        input();
        move();
        
        if(hasEatenFood())
        {
            createFood();
            addTail();
        }
        
        usleep(200000); // delay in microseconds
    }
    
    return 0;
}

void createBoard()
{
    for(int i = 0; i < box; i++)
        for(int j = 0; j < box; j++)
            board[i][j] = boardPattern;
}

void createSnake()
{
    for(int i = 0; i < length; i++)
            board[snakeX[i]][snakeY[i]] = snake;
}

void draw()
{
    
    for(int i = 0; i < box; i++)
    {
        for(int j = 0; j < box; j++)
        {
            printf("%c", board[i][j]);
            if(j == box - 1)
                printf("\n");
        }
    }
}

void refill()
{
    for(int i = 0; i < length; i++)
            board[snakeX[i]][snakeY[i]] = boardPattern;
}

void input()
{
    if(kbhit())
        key = getch();
}

void move()
{
    for(int i = 0; i < length - 1; i++)
    {
        snakeX[i] = snakeX[i + 1];
        snakeY[i] = snakeY[i + 1];
    }
    
    
    switch(key)
    {
        case 'a':
        snakeY[length - 1]--;
        if(snakeY[length - 1] < 0)
            snakeY[length - 1] = box - 1;
        break;
            
        case 'd':
        snakeY[length - 1]++;
        if(snakeY[length - 1] > box - 1)
            snakeY[length - 1] = 0;
        break;
            
        case 's':
        snakeX[length - 1]++;
        if(snakeX[length - 1] > box - 1)
            snakeX[length - 1] = 0;
        break;
            
        case 'w':
        snakeX[length - 1]--;
        if(snakeX[length - 1] < 0)
            snakeX[length - 1] = box - 1;
        break;
    }
}

int hasEatenFood()
{
    if(snakeX[length - 1] == foodX && snakeY[length - 1] == foodY)
        return true;
    else
        return false;
}

void createFood()
{
    srand(time(NULL));
    foodX = rand() % box;
    foodY = rand() % box;
    board[foodX][foodY] = food;
}

void addTail()
{
    snakeX[length] = snakeX[length - 1];
    snakeY[length] = snakeY[length - 1];
    length++;
}
    

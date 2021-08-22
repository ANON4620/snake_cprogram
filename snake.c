#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char board[16][16];
int snakeX[256] = {0, 0, 0}; // snake and tail X position
int snakeY[256] = {0, 1, 2}; // snake and tail Y position
int foodX, foodY; // food X position and food Y position

char boardPattern = '.';
char snake = '#';
char food = '@';

int length = 3; // snake length
int box = 16; // matrix
char key = 'd'; // current key in buffer

int main()
{
    void createBoard();
    void changeFoodPosition();
    void createSnake();
    void createFood();
    void draw();
    void refillBoard();
    void input();
    void move();
    int hasCollided();
    int hasEatenFood();
    void addTail();
    
    createBoard();
    changeFoodPosition();
    
    while(true)
    {
        clrscr();
        createSnake();
        createFood();
        draw(box);
        refillBoard();
        input();
        move();
        if(hasCollided())
            break;
        if(hasEatenFood())
        {
            changeFoodPosition();
            addTail();
        }
        
        usleep(200000); // delay in microseconds
    }
    
    puts("\nGame Over!");
    
    return 0;
}

void createBoard()
{
    for(int i = 0; i < box; i++)
        for(int j = 0; j < box; j++)
            board[i][j] = boardPattern;
}

void changeFoodPosition()
{
    srand(time(NULL));
    foodX = rand() % box;
    foodY = rand() % box;
}

void createSnake()
{
    for(int i = 0; i < length; i++)
        board[snakeX[i]][snakeY[i]] = snake;
}

void createFood()
{
    board[foodX][foodY] = food;
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

void refillBoard()
{
    for(int i = 0; i < length; i++)
        board[snakeX[i]][snakeY[i]] = boardPattern;
}

void input()
{
    if(kbhit())
    {
        char temp = getch();
        if(temp == 'a' || temp == 'd' || temp == 's' || temp == 'w')
            if((temp == 'a' && key != 'd') || (temp == 'd' && key != 'a') || (temp == 's' && key != 'w') || (temp == 'w' && key != 's')) 
                key = temp;
    }
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

int hasCollided()
{
    for(int i = 0; i < length - 1; i++)
    {
        if(snakeX[length - 1] == snakeX[i] && snakeY[length - 1] == snakeY[i])
            return 1;
    }
    
    return 0;
}

int hasEatenFood()
{
    if(snakeX[length - 1] == foodX && snakeY[length - 1] == foodY)
        return true;
    else
        return false;
}

void addTail()
{
    snakeX[length] = snakeX[length - 1];
    snakeY[length] = snakeY[length - 1];
    length++;
}



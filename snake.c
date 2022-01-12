#define ushort unsigned short

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Board
{
    ushort box;
    char array[16][16];
    char pattern;
};
struct Snake
{
    short X[256];
    short Y[256];
    ushort length;
    char sprite;
};
struct Food
{
    ushort X, Y;
    char sprite;
};

struct Board board = {16, {}, '.'};
struct Snake snake = { {0, 0, 0},
                       {0, 1, 2},
                        3,
                       '*' };
struct Food food = {0, 0, '@'};

char key = 'd'; // current key in buffer

int main()
{
    void setFoodPosition();
    void createBoard();
    void createSnake();
    void createFood();
    void draw();
    void input();
    void move();
    int hasCollided();
    int hasEatenFood();
    void addTail();
    
    setFoodPosition();
    createBoard();
    
    while(true)
    {
        clrscr();
        createSnake();
        createFood();
        draw();
        input();
        move();
        if(hasCollided())
        {
            puts("\nGame Over!");
            break;
        }
        if(hasEatenFood())
        {
            setFoodPosition();
            addTail();
        }
        
        usleep(200000); // delay in microseconds
    }
    
    return 0;
}

void setFoodPosition()
{
    srand(time(NULL));
    food.X = rand() % board.box;
    food.Y = rand() % board.box;
}

void createBoard()
{
    for(ushort i = 0; i < board.box; i++)
        for(ushort j = 0; j < board.box; j++)
            board.array[i][j] = board.pattern;
}

void createSnake()
{
    for(ushort i = 0; i < snake.length; i++)
        board.array[snake.X[i]][snake.Y[i]] = snake.sprite;
}

void createFood()
{
    board.array[food.X][food.Y] = food.sprite;
}

void draw()
{
    for(ushort i = 0; i < board.box; i++)
    {
        for(ushort j = 0; j < board.box; j++)
            printf("%c", board.array[i][j]);
        printf("\n");
    }
    
    board.array[snake.X[0]][snake.Y[0]] = board.pattern;
}

void input()
{
    if(kbhit())
    {
        char temp = getch();
        if((temp == 'w' && key != 's') || (temp == 's' && key != 'w') || (temp == 'a' && key != 'd') || (temp == 'd' && key != 'a'))
            key = temp;
    }
}

void move()
{
    for(ushort i = 0; i < snake.length - 1; i++)
    {
        snake.X[i] = snake.X[i + 1];
        snake.Y[i] = snake.Y[i + 1];
    }
    
    
    switch(key)
    {
        case 'w':
        snake.X[snake.length - 1]--;
        if(snake.X[snake.length - 1] < 0)
            snake.X[snake.length - 1] = board.box - 1;
        break;
        
        case 's':
        snake.X[snake.length - 1]++;
        if(snake.X[snake.length - 1] > board.box - 1)
            snake.X[snake.length - 1] = 0;
        break;
        
        case 'a':
        snake.Y[snake.length - 1]--;
        if(snake.Y[snake.length - 1] < 0)
            snake.Y[snake.length - 1] = board.box - 1;
        break;
            
        case 'd':
        snake.Y[snake.length - 1]++;
        if(snake.Y[snake.length - 1] > board.box - 1)
            snake.Y[snake.length - 1] = 0;
        break;
    }
}

int hasCollided()
{
    for(ushort i = 0; i < snake.length - 1; i++)
        if(snake.X[snake.length - 1] == snake.X[i] && snake.Y[snake.length - 1] == snake.Y[i])
            return true;
    
    return false;
}

int hasEatenFood()
{
    if(snake.X[snake.length - 1] == food.X && snake.Y[snake.length - 1] == food.Y)
        return true;
    else
        return false;
}

void addTail()
{
    snake.X[snake.length] = snake.X[snake.length - 1];
    snake.Y[snake.length] = snake.Y[snake.length - 1];
    snake.length++;
}

    

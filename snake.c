#define box 16
#define ushort unsigned short

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Board
{
    char array[box][box];
    char pattern;
};
struct Snake
{
    short X[box * box];
    short Y[box * box];
    ushort length;
    char sprite;
};
struct Food
{
    ushort X, Y;
    char sprite;
};

struct Board board = {{}, '.'};
struct Snake snake = { {0, 0, 0},
                       {0, 1, 2},
                        3,
                       '*' };
struct Food food = {0, 0, '@'};


int main()
{
    void setFoodPosition();
    void createBoard();
    void createSnake();
    void createFood();
    void draw();
    void input(char*);
    void move(char);
    int hasCollided();
    int hasEatenFood();
    void addTail();
    
    char key = 'd'; // current key in buffer
    
    setFoodPosition();
    createBoard();
    
    while(true)
    {
        clrscr();
        createSnake();
        createFood();
        draw();
        input(&key);
        move(key);
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
    
    return(0);
}

void setFoodPosition()
{
    srand(time(NULL));
    food.X = rand() % box;
    food.Y = rand() % box;
}

void createBoard()
{
    for(ushort i = 0; i < box; i++)
        for(ushort j = 0; j < box; j++)
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
    for(ushort i = 0; i < box; i++)
    {
        for(ushort j = 0; j < box; j++)
            putchar(board.array[i][j]);
        putchar('\n');
    }
    
    board.array[snake.X[0]][snake.Y[0]] = board.pattern;
}

void input(char* p)
{
    if(kbhit())
    {
        char temp = getch();
        if((temp == 'w' && *p != 's') || (temp == 's' && *p != 'w') || (temp == 'a' && *p != 'd') || (temp == 'd' && *p != 'a'))
            *p = temp;
    }
}

void move(char key)
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
            snake.X[snake.length - 1] = box - 1;
        break;
        
        case 's':
        snake.X[snake.length - 1]++;
        if(snake.X[snake.length - 1] > box - 1)
            snake.X[snake.length - 1] = 0;
        break;
        
        case 'a':
        snake.Y[snake.length - 1]--;
        if(snake.Y[snake.length - 1] < 0)
            snake.Y[snake.length - 1] = box - 1;
        break;
            
        case 'd':
        snake.Y[snake.length - 1]++;
        if(snake.Y[snake.length - 1] > box - 1)
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



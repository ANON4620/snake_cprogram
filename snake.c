#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SNAKE_BOX 20

struct Board
{
    char array[SNAKE_BOX][SNAKE_BOX];
    char pattern;
};
struct Snake
{
    int X[SNAKE_BOX * SNAKE_BOX];
    int Y[SNAKE_BOX * SNAKE_BOX];
    int length;
    char sprite;
};
struct Food
{
    int X, Y;
    char sprite;
};

static void setFoodPosition(struct Food *);
static void createBoard(struct Board *);
static void createSnake(struct Board *, struct Snake);
static void createFood(struct Board *, struct Food);
static void draw(struct Board *, struct Snake);
static void input(char*);
static void move(struct Snake *, char);
static int hasCollided(struct Snake);
static int hasEatenFood(struct Snake, struct Food);
static void addTail(struct Snake *);

int main()
{
    struct Board board = {{}, '.'};
    struct Snake snake = { {0, 0, 0},
                       {0, 1, 2},
                        3,
                       '*' };
    struct Food food = {0, 0, '@'};

    char key = 'd'; // current key in buffer
    
    srand(time(NULL));
    
    setFoodPosition(&food);
    createBoard(&board);
    
    while(true)
    {
        clrscr();
        createSnake(&board, snake);
        createFood(&board, food);
        draw(&board, snake);
        input(&key);
        move(&snake, key);
        if(hasCollided(snake))
        {
            puts("\nGame Over!");
            break;
        }
        if(hasEatenFood(snake, food))
        {
            setFoodPosition(&food);
            addTail(&snake);
        }
        
        usleep(200000); // delay in microseconds
    }
    
    return(0);
}

void setFoodPosition(struct Food *food)
{
    food->X = rand() % SNAKE_BOX;
    food->Y = rand() % SNAKE_BOX;
}

void createBoard(struct Board *board)
{
    for(int i = 0; i < SNAKE_BOX; i++)
        for(int j = 0; j < SNAKE_BOX; j++)
            board->array[i][j] = board->pattern;
}

void createSnake(struct Board *board, struct Snake snake)
{
    for(int i = 0; i < snake.length; i++)
        board->array[snake.X[i]][snake.Y[i]] = snake.sprite;
}

void createFood(struct Board *board, struct Food food)
{
    board->array[food.X][food.Y] = food.sprite;
}

void draw(struct Board *board, struct Snake snake)
{
    for(int i = 0; i < SNAKE_BOX; i++)
    {
        for(int j = 0; j < SNAKE_BOX; j++)
            putchar(board->array[i][j]);
        putchar('\n');
    }
    
    board->array[snake.X[0]][snake.Y[0]] = board->pattern;
}

void input(char* p)
{
    if(kbhit())
    {
        char temp = getch();
        if((temp == 'w' && *p != 's') || (temp == 's' && *p != 'w') || (temp == 'a' && *p != 'd') || (temp == 'd' && *p != 'a') || (temp == 'q'))
            *p = temp;
    }
}

void move(struct Snake *snake, char key)
{
    int snake_length = snake->length;
    
    for(int i = 0; i < snake_length - 1; i++)
    {
        snake->X[i] = snake->X[i + 1];
        snake->Y[i] = snake->Y[i + 1];
    }
     
    switch(key)
    {
        case 'w':
        snake->X[snake_length - 1]--;
        if(snake->X[snake_length - 1] < 0)
            snake->X[snake_length - 1] = SNAKE_BOX - 1;
        break;
        
        case 's':
        snake->X[snake_length - 1]++;
        if(snake->X[snake_length - 1] > SNAKE_BOX - 1)
            snake->X[snake_length - 1] = 0;
        break;
        
        case 'a':
        snake->Y[snake_length - 1]--;
        if(snake->Y[snake_length - 1] < 0)
            snake->Y[snake_length - 1] = SNAKE_BOX - 1;
        break;
            
        case 'd':
        snake->Y[snake_length - 1]++;
        if(snake->Y[snake_length - 1] > SNAKE_BOX - 1)
            snake->Y[snake_length - 1] = 0;
        break;
        
        case 'q':
        exit(EXIT_SUCCESS);
    }
}

int hasCollided(struct Snake snake)
{
    for(int i = 0; i < snake.length - 1; i++)
        if(snake.X[snake.length - 1] == snake.X[i] && snake.Y[snake.length - 1] == snake.Y[i])
            return true;
    
    return false;
}

int hasEatenFood(struct Snake snake, struct Food food)
{
    if(snake.X[snake.length - 1] == food.X && snake.Y[snake.length - 1] == food.Y)
        return true;
    else
        return false;
}

void addTail(struct Snake *snake)
{
    snake->X[snake->length] = snake->X[snake->length - 1];
    snake->Y[snake->length] = snake->Y[snake->length - 1];
    snake->length++;
}



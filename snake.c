#define NDEBUG

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define SNAKE_BOX 20

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

static void setSnakePosition(struct Snake *);
static void setFoodPosition(struct Food *);
static void draw(char, struct Snake, struct Food food);
static void input(char*);
static void move(struct Snake *, char);
static int hasCollided(struct Snake);
static int hasEatenFood(struct Snake, struct Food);
static void addTail(struct Snake *);

int main()
{
    char board = '.';
    struct Snake snake = {{}, {}, 3, '*'};
    struct Food food = {0, 0, '@'};
    
    struct timespec request = {0, 200000000}; // for nanosleep function
    
    assert(snake.length < SNAKE_BOX);
    
    char key = 'd'; // current key in buffer
    
    srand(time(NULL));
    
    setSnakePosition(&snake);
    setFoodPosition(&food);
    
    while(true)
    {
        clrscr();
        draw(board, snake, food);
        input(&key);
        if(key == 'q')
            exit(EXIT_SUCCESS);
        
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
        
        nanosleep(&request, NULL);
    }
    
    return(0);
}

void setSnakePosition(struct Snake *snake)
{
    int snake_length = snake->length;
    
    for(int i = 0; i < snake_length; i++)
    {
        snake->X[i] = 0;
        snake->Y[i] = i;
    }
}

void setFoodPosition(struct Food *food)
{
    food->X = rand() % SNAKE_BOX;
    food->Y = rand() % SNAKE_BOX;
}

void draw(char board, struct Snake snake, struct Food food)
{
    for(int x = 0; x < SNAKE_BOX; x++)
    {
        for(int y = 0; y < SNAKE_BOX; y++)
        {
            bool print = false;
            
            if((x == food.X) && (y == food.Y))
            {
                putchar(food.sprite);
                print = true;
            }
            else
            {
                int snake_length = snake.length;
             
                for(int i = 0; i < snake_length; i++)
                    if((snake.X[i] == x) && (snake.Y[i] == y))
                    {
                        putchar(snake.sprite);
                        print = true;
                        break;
                    }
            }
            
            if(print == false)
                putchar(board);
        }
        putchar('\n');
    }
}

void input(char *key)
{
    if(kbhit())
    {
        char temp = getch();
        if((temp == 'w' && *key != 's') || (temp == 's' && *key != 'w') || (temp == 'a' && *key != 'd') || (temp == 'd' && *key != 'a') || (temp == 'q'))
            *key = temp;
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
    int snake_length = snake->length;
    
    assert(snake_length < (SNAKE_BOX * SNAKE_BOX));
    
    snake->X[snake_length] = snake->X[snake_length - 1];
    snake->Y[snake_length] = snake->Y[snake_length - 1];
    snake->length++;
}


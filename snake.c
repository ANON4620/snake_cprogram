// X[0] Y[0] is the head of the snake
// X[length - 1] Y[length - 1] is the tail of the snake

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD 20
#define BOARD_SPRITE '.'
#define SNAKE_SPRITE '*'
#define FOOD_SPRITE '@'

struct Snake
{
    int X[BOARD * BOARD];
    int Y[BOARD * BOARD];
    int length;
};
struct Food
{
    int X, Y;
};

static void set_snake_position(struct Snake *);
static void set_food_position(struct Snake, struct Food *);
static void draw(struct Snake, struct Food food);
static void input(char *);
static void move(struct Snake *, char);
static int has_collided(struct Snake);
static int has_eaten_food(struct Snake, struct Food);
static void add_tail(struct Snake *);

int main()
{
    struct Snake snake;
    struct Food food;
    struct timespec request = {0, 200000000}; // for nanosleep function
    char key = 'd'; // current key in buffer
    
    snake.length = 3;
    
    srand(time(NULL));
    
    set_snake_position(&snake);
    set_food_position(snake, &food);
    
    while(true)
    {
        clrscr();
        draw(snake, food);
        input(&key);
        
        if(key == 'q')
            exit(EXIT_SUCCESS);
        
        move(&snake, key);
        
        if(has_collided(snake))
        {
            puts("\nGame Over!");
            break;
        }
        if(has_eaten_food(snake, food))
        {
            add_tail(&snake);
            set_food_position(snake, &food);
        }
        
        nanosleep(&request, NULL);
    }
    
    return(0);
}

void set_snake_position(struct Snake *snake)
{
    int snake_length = snake->length;
    int y = 0;
     
    for(int i = snake_length - 1; i >= 0; i--)
    {
        snake->X[i] = 0;
        snake->Y[i] = y;
        y++;
    }
}

void set_food_position(struct Snake snake, struct Food *food)
{
    int random;
    int snake_length = snake.length;
    int arr_size = (BOARD * BOARD) - snake.length - 1; // -1 for food
    char X[arr_size];
    char Y[arr_size];
    
    int i = 0;
    
    for(int x = 0; x < BOARD; x++)
    {
        for(int y = 0; y < BOARD; y++)
        {
            bool blank_pos = true;
            
            if(x == food->X && y == food->Y)
                blank_pos = false;
            else
            {
                for(int i = snake_length - 1; i >= 0; i--)
                {
                    if((snake.X[i] == x) && (snake.Y[i] == y))
                    {
                        blank_pos = false;
                        break;
                    }
                }
            }
            
            if(blank_pos == true)
            {
                X[i] = x;
                Y[i] = y;
                i++;
            }
        }
    }
    
    random = rand() % arr_size;
    food->X = X[random];
    food->Y = Y[random];
}

void draw(struct Snake snake, struct Food food)
{
    int snake_length = snake.length;
    
    for(int x = 0; x < BOARD; x++)
    {
        for(int y = 0; y < BOARD; y++)
        {
            bool print = false;
            
            if((x == food.X) && (y == food.Y))
            {
                putchar(FOOD_SPRITE);
                print = true;
            }
            else
            {
                for(int i = snake_length - 1; i >= 0; i--)
                {
                    if((snake.X[i] == x) && (snake.Y[i] == y))
                    {
                        putchar(SNAKE_SPRITE);
                        print = true;
                        break;
                    }
                }
            }
            
            if(print == false)
                putchar(BOARD_SPRITE);
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
    
    for(int i = snake_length - 1; i > 0; i--)
    {
        snake->X[i] = snake->X[i - 1];
        snake->Y[i] = snake->Y[i - 1];
    }
     
    switch(key)
    {
        case 'w':
        snake->X[0]--;
        if(snake->X[0] < 0)
            snake->X[0] = BOARD - 1;
        break;
        
        case 's':
        snake->X[0]++;
        if(snake->X[0] > BOARD - 1)
            snake->X[0] = 0;
        break;
        
        case 'a':
        snake->Y[0]--;
        if(snake->Y[0] < 0)
            snake->Y[0] = BOARD - 1;
        break;
            
        case 'd':
        snake->Y[0]++;
        if(snake->Y[0] > BOARD - 1)
            snake->Y[0] = 0;
        break;
    }
}

int has_collided(struct Snake snake)
{
    for(int i = snake.length - 1; i > 0; i--)
        if(snake.X[0] == snake.X[i] && snake.Y[0] == snake.Y[i])
            return true;
    
    return false;
}

int has_eaten_food(struct Snake snake, struct Food food)
{
    if(snake.X[0] == food.X && snake.Y[0] == food.Y)
        return true;
    else
        return false;
}

void add_tail(struct Snake *snake)
{
    int snake_length = snake->length;
    
    snake->X[snake_length] = snake->X[snake_length - 1];
    snake->Y[snake_length] = snake->Y[snake_length - 1];
    snake->length++;
}


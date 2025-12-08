#include "main.h"
#include "raylib-cpp.hpp"
#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    raylib::Window snakeWindow(600, 600, "Snake", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    // clang-format off
    const int GRID_SIZE    = 40;
    bool  gameOver         = false;
    int   score            = 0;
    int   highScore        = 0;
    int   timeStepIterator = 0;
    char  currentDirection = 'd';
    char  nextDirection    = 'd';

    vector<Segment> snake;

    initSnake(snake, GRID_SIZE);
    Segment food = initFood(GRID_SIZE, snake);

    while (!WindowShouldClose())
    {
        // Check If Move is Valid
        if      (IsKeyDown(KEY_W) && currentDirection != 's') nextDirection = 'w';
        else if (IsKeyDown(KEY_S) && currentDirection != 'w') nextDirection = 's';
        else if (IsKeyDown(KEY_A) && currentDirection != 'd') nextDirection = 'a';
        else if (IsKeyDown(KEY_D) && currentDirection != 'a') nextDirection = 'd';

        // Move Head based on Direction, Also move it after Approx fixed time
        if (timeStepIterator % 10 == 0)
        {
            // Set Snake Direction
            currentDirection = nextDirection;

            moveSnake(currentDirection,snake,GRID_SIZE);
            wrapSnake(snake, GRID_SIZE);

            // Self-Collision Check
            for (int i = 1; i < snake.size(); i++)
            {
                if (CheckCollisionRecs(snake[0].rect, snake[i].rect))
                {
                    gameOver = true;
                    break;
                }
            }
            
            // Food Collision Check
            if (CheckCollisionRecs(snake[0].rect, food.rect))
            {
                score++;
                grow(snake);
                generateNewFood(food, GRID_SIZE, snake);
            }

            if (score>highScore) highScore = score;
            
            if (gameOver) resetGame(snake, food, GRID_SIZE, score, gameOver);

            render(snake, food);
        }

        timeStepIterator++;
    }
}

vector<Segment> initSnake(const int GRID_SIZE)
{
    vector<Segment> snake;

    Segment snakeHead, s1, s2;

    snakeHead.rect.SetPosition(120, GRID_SIZE);
    snakeHead.rect.SetSize(GRID_SIZE, GRID_SIZE);
    snakeHead.color = GREEN;

    s1 = snakeHead;
    s2 = snakeHead;

    s1.rect.SetPosition(80, GRID_SIZE);
    s2.rect.SetPosition(40, GRID_SIZE);

    snake = {snakeHead, s1, s2};
    return snake;
}

Segment initFood(const int GRID_SIZE, std::vector<Segment> &snake)
{
    Segment food;
    food.rect.SetSize(GRID_SIZE, GRID_SIZE);
    food.color = RED;

    generateNewFood(food, GRID_SIZE, snake);

    return food;
}

void resetGame(std::vector<Segment> &snake, Segment &food,
               int GRID_SIZE, int &score, bool &gameOver)
{
    snake = initSnake(GRID_SIZE);
    food  = initFood(GRID_SIZE, snake);

    score    = 0;
    gameOver = false;
}

void generateNewFood(Segment &food, const int GRID_SIZE,
                     std::vector<Segment> &snake)
{
foodGeneration:
    food.rect.x = GetRandomValue(0, 14) * GRID_SIZE;
    food.rect.y = GetRandomValue(0, 14) * GRID_SIZE;

    // Regenerate Food if its on Snake Body
    for (auto &s : snake)
    {
        if (CheckCollisionRecs(s.rect, food.rect))
            goto foodGeneration;
    }
}

void render(std::vector<Segment> &snake, Segment &food)
{
    // Rendering Logic
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto &segment : snake)
        segment.draw();

    food.draw();
    EndDrawing();
}

void moveSnake(char currentDirection, std::vector<Segment> &snake,
               const int GRID_SIZE)
{
    Segment temp = snake[0];

    // Move Head
    switch (currentDirection)
    {
    case 'w': snake[0].rect.y -= GRID_SIZE; break;
    case 'a': snake[0].rect.x -= GRID_SIZE; break;
    case 's': snake[0].rect.y += GRID_SIZE; break;
    case 'd': snake[0].rect.x += GRID_SIZE; break;
    }

    // Move Body
    for (int i = 1; i < snake.size(); i++)
    {
        Segment nextTemp = snake[i];
        snake[i].rect.SetPosition(temp.rect.GetPosition());
        temp = nextTemp;
    }
}

void wrapSnake(std::vector<Segment> &snake, const int GRID_SIZE)
{
    if (snake[0].rect.x > 600 - GRID_SIZE) snake[0].rect.x = 0;               // Right wrap
    if (snake[0].rect.y > 600 - GRID_SIZE) snake[0].rect.y = 0;               // Down wrap
    if (snake[0].rect.x < 0)               snake[0].rect.x = 600 - GRID_SIZE; // Left wrap
    if (snake[0].rect.y < 0)               snake[0].rect.y = 600 - GRID_SIZE; // Up wrap
}

void grow(std::vector<Segment> &snake)
{
    Segment newSegment = snake.back();
    snake.push_back(newSegment);
}

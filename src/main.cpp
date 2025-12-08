#include "main.h"
#include "raylib-cpp.hpp"
#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    raylib::Window snakeWindow(600, 640, "Snake", FLAG_VSYNC_HINT);
    SetTargetFPS(75);
    system("cls");

    // clang-format off
    const int GRID_SIZE    = 40;
    bool  gameOver         = false;
    int   score            = 0;
    int   highScore        = 0;
    int   timeStepIterator = 0;
    char  currentDirection = 'd';
    char  nextDirection    = 'd';

    vector<Segment> snake = initSnake(GRID_SIZE);
    Segment         food  = initFood(GRID_SIZE, snake);
    
    while (!WindowShouldClose())
    {       
        // clang-format off
        // Check If Move is Valid
        if      (IsKeyDown(KEY_W) && currentDirection != 's') nextDirection = 'w';
        else if (IsKeyDown(KEY_S) && currentDirection != 'w') nextDirection = 's';
        else if (IsKeyDown(KEY_A) && currentDirection != 'd') nextDirection = 'a';
        else if (IsKeyDown(KEY_D) && currentDirection != 'a') nextDirection = 'd';
        // clang-format on
        // Move Head based on Direction, Also move it after Approx fixed time
        if (timeStepIterator % 10 == 0)
        {
            // Set Snake Direction
            currentDirection = nextDirection;

            moveSnake(currentDirection, snake, GRID_SIZE);
            wrapSnake(snake, GRID_SIZE);

            checkSelfCollision(snake, gameOver);
            checkFoodCollision(snake, food, score, GRID_SIZE);

            if (score > highScore)
                highScore = score;

            if (gameOver)
            {
                resetGame(snake, food, GRID_SIZE, score, gameOver,
                          timeStepIterator, currentDirection, nextDirection);
            }
        }

        render(snake, food, score, highScore);
        timeStepIterator++;
    }
}

void checkFoodCollision(std::vector<Segment> &snake, Segment &food, int &score,
                        const int GRID_SIZE)
{
    // Food Collision Check
    if (CheckCollisionRecs(snake[0].rect, food.rect))
    {
        grow(snake, score);
        generateNewFood(food, GRID_SIZE, snake);
    }
}

void checkSelfCollision(std::vector<Segment> &snake, bool &gameOver)
{
    // Self-Collision Check
    for (int i = 1; i < snake.size(); i++)
    {
        if (CheckCollisionRecs(snake[0].rect, snake[i].rect))
        {
            gameOver = true;
            break;
        }
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

    snakeHead.color = DARKGREEN;

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

void moveSnake(char currentDirection, std::vector<Segment> &snake,
               const int GRID_SIZE)
{
    Segment temp = snake[0];

    // Move Head
    // clang-format off
    switch (currentDirection)
    {
    case 'w': snake[0].rect.y -= GRID_SIZE; break;
    case 'a': snake[0].rect.x -= GRID_SIZE; break;
    case 's': snake[0].rect.y += GRID_SIZE; break;
    case 'd': snake[0].rect.x += GRID_SIZE; break;
    }
    // clang-format on
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
    if (snake[0].rect.x > 600 - GRID_SIZE)
        snake[0].rect.x = 0; // Right wrap
    if (snake[0].rect.y > 600 - GRID_SIZE)
        snake[0].rect.y = 0; // Down wrap
    if (snake[0].rect.x < 0)
        snake[0].rect.x = 600 - GRID_SIZE; // Left wrap
    if (snake[0].rect.y < 0)
        snake[0].rect.y = 600 - GRID_SIZE; // Up wrap
}

void grow(std::vector<Segment> &snake, int &score)
{
    score++;
    Segment newSegment = snake.back();
    snake.push_back(newSegment);
}

void render(std::vector<Segment> &snake, Segment &food, int &score,
            int &highScore)
{
    // Rendering Logic
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto &segment : snake)
    {
        segment.draw();
        segment.rect.DrawLines(BLACK, 2);
    }

    DrawText(TextFormat("Score: %d", score), 20, 605, 30, WHITE);
    DrawText(TextFormat("High Score: %d", highScore), 375, 605, 30, WHITE);

    DrawRectangleLinesEx({0,0,600,600},5,DARKGRAY);
    
    food.draw();
    EndDrawing();
}

void resetGame(std::vector<Segment> &snake, Segment &food, int GRID_SIZE,
               int &score, bool &gameOver, int &timeStepIterator,
               char &currentDirection, char &nextDirection)
{
    snake = initSnake(GRID_SIZE);
    food = initFood(GRID_SIZE, snake);

    score = 0;
    gameOver = false;
    timeStepIterator = 0;

    currentDirection = 'd';
    nextDirection = 'd';
}

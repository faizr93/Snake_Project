#include "main.h"
#include "raylib-cpp.hpp"
#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;

bool checkCollision(Segment s1, Segment s2)
{
    return CheckCollisionRecs(s1.rect, s2.rect);
}

int main()
{
    raylib::Window gameWindow(600, 600, "Snake", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    const int GRID_SIZE = 40;
    bool  gameOver      = false;

    Segment snakeHead, s1, s2, food;

    snakeHead.rect.SetSize({GRID_SIZE, GRID_SIZE});
    snakeHead.rect.SetPosition(40, 40);
    snakeHead.color = GREEN;

    s1 = s2 = food = snakeHead;

    food.color = RED;

   // clang-format off
    food.rect.SetPosition({400, 200});

    vector<Segment> snake            = {snakeHead, s1, s2};  // Container for snake
    int             length           = 3;
    int             timeStepIterator = 0;
    char            currentDirection = 'd';
    char            nextDirection    = 'd';

    while (!WindowShouldClose())
    {
        // Check If Move is Valid
        if      (IsKeyDown(KEY_W) && currentDirection != 's') nextDirection = 'w';
        else if (IsKeyDown(KEY_S) && currentDirection != 'w') nextDirection = 's';
        else if (IsKeyDown(KEY_A) && currentDirection != 'd') nextDirection = 'a';
        else if (IsKeyDown(KEY_D) && currentDirection != 'a') nextDirection = 'd';

        // Set Snake Direction
        currentDirection = nextDirection;

        // Move Head based on Direction, Also move it after Approx fixed time
        if (timeStepIterator % 10 == 0)
        {
            moveSnake(currentDirection, snake, GRID_SIZE);
        }

        timeStepIterator++;

        // Wrap Snake
        wrapSnake(snake, GRID_SIZE);

        if (snake[0].rect.x == food.rect.x &&
            snake[0].rect.y == food.rect.y)
        {
            length++;
            grow(snake);
        foodGeneration:
            food.rect.x = GetRandomValue(0, 14) * GRID_SIZE;
            food.rect.y = GetRandomValue(0, 14) * GRID_SIZE;
            for (auto &s : snake)
            {
                if (CheckCollisionRecs(s.rect, food.rect))
                    goto foodGeneration;
            }
        }

        for (auto &s : snake)
        {
            CheckCollisionRecs(s.rect, snake[0].rect);
            gameOver = true;
        }

        if (gameOver)
        {
            snake.clear();
            snake = {snakeHead, s1, s2};
            length = 3;
        }
        render(snake, food);
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
    // Move each segment to the position of the segment before it
    for (int i = snake.size() - 1; i > 0; i--)
    {
        snake[i].rect.SetPosition(snake[i - 1].rect.GetPosition());
    }

    switch (currentDirection)
    {
    case 'w':
        snake[0].rect.y -= GRID_SIZE;
        break;
    case 'a':
        snake[0].rect.x -= GRID_SIZE;
        break;
    case 's':
        snake[0].rect.y += GRID_SIZE;
        break;
    case 'd':
        snake[0].rect.x += GRID_SIZE;
        break;
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

void grow(std::vector<Segment> &snake)
{
    Segment newSegment;

    Segment tail = snake.back();

    newSegment.rect.SetSize(tail.rect.GetSize());
    newSegment.rect.SetPosition(tail.rect.GetPosition());
    newSegment.color = tail.color;

    snake.push_back(newSegment);
}

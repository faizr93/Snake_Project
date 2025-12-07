#include "main.h"
#include "raylib-cpp.hpp"
#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    raylib::Window snake(600, 600, "Snake", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    const int GRID_SIZE = 40;
    bool gameOver = false;
    bool snakeIsGrowing = false;

    Segment snakeHead, s1, s2, food;

    snakeHead.rect.SetSize({GRID_SIZE, GRID_SIZE});
    snakeHead.rect.SetPosition(40, 40);
    snakeHead.color = GREEN;

    s1 = s2 = food = snakeHead;

    food.color = RED;

    s1.rect.SetPosition({80, 40});
    s2.rect.SetPosition({120, 40});
    food.rect.SetPosition({400, 200});

    // clang-format off
    vector<Segment> segments         = {snakeHead, s1, s2};  // Container for snake
    int             length           =  3 ;
    int             timeStepIterator =  0 ;
    char            currentDirection = 'd';
    char            nextDirection    = 'd';

    while (!WindowShouldClose())
    {
        // Check If Move is Valid
        if      (IsKeyDown(KEY_W) && currentDirection != 's') nextDirection = 'w';
        else if (IsKeyDown(KEY_S) && currentDirection != 'w') nextDirection = 's';
        else if (IsKeyDown(KEY_A) && currentDirection != 'd') nextDirection = 'a';
        else if (IsKeyDown(KEY_D) && currentDirection != 'a') nextDirection = 'd';
        // clang-format on
        // Set Snake Direction
        currentDirection = nextDirection;

        // Move Head based on Direction, Also move it after Approx fixed time
        if (timeStepIterator % 10 == 0)
        {
            moveSnake(currentDirection, segments, GRID_SIZE);

            // Check for Self-Collision (head with body)
            for (int i = 1; i < segments.size(); i++)
            {
                if (!snakeIsGrowing)
                {
                    if (CheckCollisionRecs(segments[0].rect, segments[i].rect))
                    {
                        gameOver = true;
                        break;
                    }
                }
            }
        }
        // clang-format off
        timeStepIterator++;

        // Wrap Snake
        wrapSnake(segments, GRID_SIZE);

        if (segments[0].rect.x == food.rect.x &&
            segments[0].rect.y == food.rect.y)
        {
            length++;
            grow(segments);
        foodGeneration:
            food.rect.x = GetRandomValue(0, 14) * GRID_SIZE;
            food.rect.y = GetRandomValue(0, 14) * GRID_SIZE;

            // Regenerate Food if its on Snake Body
            for (auto &s : segments)
            {
                if (CheckCollisionRecs(s.rect, food.rect))
                    goto foodGeneration;
            }
        }

        if (gameOver) std::cout << "Hell";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
        // {
        //     segments.clear();
        //     segments = {snakeHead, s1, s2};
        //     length   = 3;
        // }
        
        render(segments, food);
    }
}

void render(std::vector<Segment> &segments, Segment &food)
{
    // Rendering Logic
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto &segment : segments)
        segment.draw();

    food.draw();
    EndDrawing();
}

void moveSnake(char currentDirection, std::vector<Segment> &segments,
               const int GRID_SIZE)
{
    Segment temp = segments[0];

    // Move SnakeHead
    switch (currentDirection)
    {
    case 'w': segments[0].rect.y -= GRID_SIZE; break;
    case 'a': segments[0].rect.x -= GRID_SIZE; break;
    case 's': segments[0].rect.y += GRID_SIZE; break;
    case 'd': segments[0].rect.x += GRID_SIZE; break;
    }

    // Move Body
    for (int i = 1; i < segments.size(); i++)
    {
        Segment nextTemp = segments[i];                        
        segments[i].rect.SetPosition(temp.rect.GetPosition()); 
        temp = nextTemp;                                       
    }
}

void wrapSnake(std::vector<Segment> &segments, const int GRID_SIZE)
{
    if (segments[0].rect.x > 600 - GRID_SIZE) segments[0].rect.x = 0;               // Right wrap
    if (segments[0].rect.y > 600 - GRID_SIZE) segments[0].rect.y = 0;               // Down wrap
    if (segments[0].rect.x < 0)               segments[0].rect.x = 600 - GRID_SIZE; // Left wrap
    if (segments[0].rect.y < 0)               segments[0].rect.y = 600 - GRID_SIZE; // Up wrap
}

void grow(std::vector<Segment> &segments)
{
    Segment newSegment = segments.back();
    segments.push_back(newSegment);
}

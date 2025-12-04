/* Pixel Cords to grid, we have grid, x = grid.x.pixelX or somthin
MoveHead
MoveEachSegmentToPreviousInSuccession
Eat = pushbackTail.
*/
#include "main.h"
#include "raylib-cpp.hpp"
#include "segment.h"
#include <conio.h>
#include <iostream>


using namespace std;

bool checkCollision(Segment s1, Segment s2)
{
    return CheckCollisionRecs(s1.rect, s2.rect);
}

int main()
{
    raylib::Window snake(600, 600, "Snake", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    const int GRID_SIZE = 40;
    bool won = false;

    Segment snakeHead, s1, s2;
    snakeHead.rect.SetSize({GRID_SIZE, GRID_SIZE});
    snakeHead.rect.SetPosition(40, 40);

    snakeHead.color = GREEN;

    s1 = s2 = snakeHead;

    s1.rect.SetPosition({80, 40});
    s2.rect.SetPosition({120, 40});

    vector<Segment> segments = {snakeHead, s1, s2}; // Container for snake
    char currentDirection = 'd';
    char nextDirection = 'd';
    int timeStepIterator = 0;

    while (!WindowShouldClose())
    {
        // Check If Move is Valid
        if (IsKeyDown(KEY_W) && currentDirection != 's')
            nextDirection = 'w';
        else if (IsKeyDown(KEY_S) && currentDirection != 'w')
            nextDirection = 's';
        else if (IsKeyDown(KEY_A) && currentDirection != 'd')
            nextDirection = 'a';
        else if (IsKeyDown(KEY_D) && currentDirection != 'a')
            nextDirection = 'd';

        // Set Snake Direction
        currentDirection = nextDirection;

        // Move Head based on Direction, Also move it after Approx fixed time
        if (timeStepIterator % 10 == 0)
        {
            // Move each segment to the position of the segment before it
            for (int i = segments.size() - 1; i > 0; i--)
            {
                segments[i].rect.SetPosition(
                    segments[i - 1].rect.GetPosition());
            }

            switch (currentDirection)
            {
            case 'w':
                segments[0].rect.y -= GRID_SIZE;
                break;
            case 'a':
                segments[0].rect.x -= GRID_SIZE;
                break;
            case 's':
                segments[0].rect.y += GRID_SIZE;
                break;
            case 'd':
                segments[0].rect.x += GRID_SIZE;
                break;
            }
        }
        timeStepIterator++;

        // Wrap Snake
        wrapSnake(segments, GRID_SIZE);

        for (auto &sI : segments)
        {
            for (auto &sJ : segments)
                CheckCollisionRecs(sI.rect, sJ.rect);
            won = true;
        }

        // Rendering Logic
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto &segment : segments)
            segment.draw();

        EndDrawing();
    }
}

void wrapSnake(std::vector<Segment> &segments, const int GRID_SIZE)
{
    if (segments[0].rect.x > 600 - GRID_SIZE)
        segments[0].rect.x = 0; // Right wrap
    if (segments[0].rect.y > 600 - GRID_SIZE)
        segments[0].rect.y = 0; // Down wrap
    if (segments[0].rect.x < 0)
        segments[0].rect.x = 600 - GRID_SIZE; // Left wrap
    if (segments[0].rect.y < 0)
        segments[0].rect.y = 600 - GRID_SIZE; // Up wrap
}

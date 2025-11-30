#include "main.h"
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

struct Position
{
    int x;
    int y;
};

struct snakeSegment
{
    Position position;
};

void printGrid(char grid[10][10]);

int main()
{
    // Initialize / Reset Grid
    char grid[10][10] = {};
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j] = '-';
        }
    }

    // Initialize snake (length 1)
    Position snakeHead;
    snakeHead.x = 3;
    snakeHead.y = 3;

    grid[snakeHead.x][snakeHead.y] = 'X';

    char input = ' ';
    char direction = 'd';

    printGrid(grid);

    while (input != '0')
    {
        input = getch();
        switch (input)
        {
        case 'w':
            direction = 'w';
            break;
        case 's':
            direction = 's';
            break;
        case 'a':
            direction = 'a';
            break;
        case 'd':
            direction = 'd';
            break;
        }

        // Remove old head from grid
        grid[snakeHead.x][snakeHead.y] = '-';

        // Move snake head
        if (direction == 'w' && snakeHead.x > 0)
            snakeHead.x--;
        else if (direction == 's' && snakeHead.x < 9)
            snakeHead.x++;
        else if (direction == 'a' && snakeHead.y > 0)
            snakeHead.y--;
        else if (direction == 'd' && snakeHead.y < 9)
            snakeHead.y++;

        // Place new head
        grid[snakeHead.x][snakeHead.y] = 'X';

        printGrid(grid);
    }
    return 0;
}

void printGrid(char grid[10][10])
{
    // Print Grid
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << grid[i][j];
        }
        cout << '\n';
    }
    cout << endl;
}
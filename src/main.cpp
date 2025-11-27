#include "game.h"
#include "raylib-cpp.hpp"
#include <iostream>


int main()
{
    Game snakeGame;

    while (!WindowShouldClose())
    {
        snakeGame.handleInput();
        snakeGame.update();
        snakeGame.render();
    }

    return 0;
}

#include "game.h"

void Game::run()
{
    handleInput();
    update();
    render();
}
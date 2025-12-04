#include "snake.h"

Snake::Snake() 
{
    Segment snakeHead = {{40 ,40,40,40}, GREEN};
    Segment s1        = {{80 ,40,40,40}, GREEN};
    Segment s2        = {{120,40,40,40}, GREEN};

    snake = {snakeHead, s1, s2}; // Initialized the snake
}

void Snake::handleInput() {
    
}
void Snake::update() {

}
void Snake::render() {

}
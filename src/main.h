#pragma once
#include "segment.h"
#include <vector>

std::vector<Segment> initSnake(const int GRID_SIZE);

void checkSelfCollision(std::vector<Segment> &snake, bool &gameOver);

void checkFoodCollision(std::vector<Segment> &snake, Segment &food, int &score,
                        const int GRID_SIZE);

Segment initFood(const int GRID_SIZE, std::vector<Segment> &snake);

void moveSnake(char currentDirection, std::vector<Segment> &snake,
               const int GRID_SIZE);

void wrapSnake(std::vector<Segment> &segments, const int GRID_SIZE);

void render(std::vector<Segment> &snake, Segment &food, int &score, int &highScore);

void generateNewFood(Segment &food, const int GRID_SIZE,
                     std::vector<Segment> &segments);

void grow(std::vector<Segment> &segments, int &score);

void resetGame(std::vector<Segment> &snake, Segment &food, int GRID_SIZE,
               int &score, bool &gameOver, int &timeStepIterator,
               char &currentDirection, char &nextDirection);
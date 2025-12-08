#pragma once
#include "segment.h"
#include <vector>

void wrapSnake(std::vector<Segment> &segments, const int GRID_SIZE);

void initSnake(std::vector<Segment> &snake, const int GRID_SIZE);

Segment initFood(const int GRID_SIZE, std::vector<Segment> &snake);

void moveSnake(char currentDirection, std::vector<Segment> &snake,
               const int GRID_SIZE);

void render(std::vector<Segment> &segments, Segment &food);

void generateNewFood(Segment &food, const int GRID_SIZE,
                     std::vector<Segment> &segments);

bool foodCollision(std::vector<Segment> &snake, Segment &food);

void grow(std::vector<Segment> &segments);
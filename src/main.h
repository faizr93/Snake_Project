#pragma once
#include "segment.h"
#include <vector>


void wrapSnake(std::vector<Segment> &segments, const int GRID_SIZE);

void moveSnake(char currentDirection, std::vector<Segment> &segments,
               const int GRID_SIZE);

void render(std::vector<Segment> &segments, Segment &food);

void grow(std::vector<Segment> &segments);

void initSnake(std::vector<Segment> &segments);
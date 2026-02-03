#pragma once
#include "globals.h"

struct Point2D
{
  public:
    float x, y;
};

struct Point3D
{
  public:
    float x, y, z;

    Point3D(int x, int y, int z) : x(x), y(y), z(z) {};
};
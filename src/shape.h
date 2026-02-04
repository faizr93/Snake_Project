#pragma once
#include "vector3D.h"
#include "raylib-cpp.hpp"
#include <vector>

class EdgeIndexPair
{
  public:
    int first;
    int second;

    raylib::Color color;

    void setColor(Color c);
    EdgeIndexPair(int f, int s, raylib::Color c = raylib::GREEN)
        : first(f), second(s), color(c) {}
};

class Shape
{
  public:
    std::vector<Vec3> vertices;           // Points of a shape
    std::vector<EdgeIndexPair>   edges;              // Index pair of vertices that make an Edge
    Vec3              position{0, 0, 0};  // Position of shape in 3D space
    Vec3              rotation{0, 0, 0};  // Rotation of shape in radians in 3D space

    void move(const Vec3 &delta);
    void rotate(const Vec3 &delta);
};

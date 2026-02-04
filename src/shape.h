#include "points.h"
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
    std::vector<Point3D>       vertices;           // Points of a shape
    std::vector<EdgeIndexPair> edges;              // Index pair of vertices that make an Edge
    Point3D                    position{0, 0, 0};  // Position of shape in 3D space
    Point3D                    rotation{0, 0, 0};  // Rotation of shape in radians in 3D space

    void move(const Point3D &delta);
    void rotate(const Point3D &delta);
};

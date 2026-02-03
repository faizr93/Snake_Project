#pragma once

#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"

class Renderer
{
  public:
    static float focal;
    // clang-format off
    using Shape       = std::vector<Point3D>; // All points of the shape
    using Edge        = std::pair<int, int>;  // Two Points to connect i.e Edge of shape
    using Connections = std::vector<Edge>;    // All connections of shape i.e All edges or All connections of points

    static Point2D transformCartesian(Point2D p); // Convert point to cartesian plane, so projection is accurate

    static Point2D project2D(Point3D &p); // Project 3d Point to 2d screen
    static void render(Shape shape, Connections connections); // Renders 3d point on screen's cartesian plane
    // clang-format on
    ;
};

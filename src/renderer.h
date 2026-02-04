#pragma once

#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"
#include "world.h"

class Renderer
{
  public:
    static float focal;
    static float dx;
    static float dy;
    static World renderedWorld; 
    // clang-format off

    static void transformPoint(Point3D &p);          // Convert point to cartesian plane, so projection is accurate
    static void projectPoint(Point3D &p);            // Project 3D Point on 2d screen
    static void preparePoint(Point3D &p);            // Projects and transforms a 3D point
    static void drawPoint(Point2D &p2D, Color color);  // Renders point on 2d screen's cartesian plane
    
    static void transformShape(Shape &shape);  // Rotate, Scale, Translate shape in 3D space
    static void projectShape(Shape &shape);    // Project 3D shape on 2D screen's cartesian plane
    static void drawShape(Shape &shape);       // Renders 3D shape on 2D screen's cartesian plane
    
    static void transformWorld(World &world);  // Rotate, Scale, Translate shapes of world in 3D space
    static void projectWorld(World &world);    // Project 3D world to 2D screen's cartesian plane
    static void drawWorld(World &world);       // Renders 3D world on 2D screen's cartesian plane
  
    static void handleInput();         // Decide if an action is needed
    static void update(World &world);  // Perform the needed action

    static void render(World &world);  // Render world via render pipeline, Transform->Project->Draw

    // TEMP DEBUG FUCTION
    static void pushWorldIntoView(World &world, int amount);

    // clang-format on
};

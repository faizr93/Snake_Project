#include "renderer.h"
#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"

/*
- Inverts Y axis around the origin
- Centers origin on 0,0
- Returns translated 2D point
*/
Point2D Renderer::transformCartesian(Point2D &p)
{
    p.y = -p.y;
    p.x += (GetScreenWidth() - POINT_SIZE) / 2;
    p.y += (GetScreenHeight() - POINT_SIZE) / 2;

    return {p.x, p.y};
}

/* 
- Project the 3D Point onto the 2D screen
- Return projected 2D point
*/
Point2D Renderer::project(Point3D &p)
{
    p.z = p.z == 0 ? 1 : p.z;

    float x = p.x / p.z * focal;
    float y = p.y / p.z * focal;

    return {x, y};
}

/*
- Converts 3D point to 2D
- Transforms to cartesian plane
- Draws the points and their connections/edges on screen
*/
void Renderer::renderShape(Shape shape, Connections connections)
{
    // clang-format off
    
    for (auto &edge : connections)
    {
        Point3D A3D = shape[edge.first];  // first point
        Point3D B3D = shape[edge.second]; // second point
        
        // Prepare points for rendering
        Point2D A2D = preparePoint(A3D);
        Point2D B2D = preparePoint(B3D);
        
        // Turn points into renderable rectangles with size
        raylib::Rectangle rect1 = {A2D.x, A2D.y, POINT_SIZE, POINT_SIZE};
        raylib::Rectangle rect2 = {B2D.x, B2D.y, POINT_SIZE, POINT_SIZE};
        
        // Render to screen
        rect1.Draw(RED);
        rect2.Draw(RED);
    }
    // clang-format on
}

/*
- Projects 3D point to 2D
- Transforms to cartesian plane
- Returns prepared 2D point for rendering
*/
Point2D Renderer::preparePoint(Point3D &p3D)
{
    // clang-format off
    Point2D p2D = project(p3D);                  // Convert from 3D to 2D
            p2D = transformCartesian(p2D);       // Translate to cartesiasn plane
            p2D = {round(p2D.x), round(p2D.y)};  // Fix floating point errors

    return p2D;
    // clang-format on
}

void Renderer::renderPoint(Point3D &p) {}

float Renderer::focal = 200.f;

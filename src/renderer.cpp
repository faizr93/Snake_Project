#include "renderer.h"
#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"

// clang-format off
/*
- Inverts Y axis around the origin
- Centers origin on 0,0
*/
void Renderer::transformPoint(Point3D &p)
{
    p.y = -p.y;
    p.x += (GetScreenWidth()  - POINT_SIZE) / 2;
    p.y += (GetScreenHeight() - POINT_SIZE) / 2;
}

/* 
- Project the 3D Point onto the 2D screen
*/
void Renderer::projectPoint(Point3D &p)
{
    p.z = p.z == 0 ? 1 : p.z;

    float x = p.x / p.z * focal;
    float y = p.y / p.z * focal;

    p = {x, y, 0};
}

/*
- Projects 3D point to 2D
- Transforms to cartesian plane
*/
void Renderer::preparePoint(Point3D &p)
{
    projectPoint(p);              // Convert from 3D to 2D
    transformPoint(p);            // Translate to cartesiasn plane
}

// Render the 2D point on screen in given Color
void Renderer::drawPoint(Point2D &p, Color color)
{
    // Turn point into renderable rectangles with size
    raylib::Rectangle rect = {p.x, p.y, POINT_SIZE, POINT_SIZE};  
    rect.Draw(color); 
}

// - Rotate, Scale, Translate shape to its accurate position
void Renderer::transformShape(Shape &shape)
{
    // Rotate #TODO
    // Transform ={scale,translate,rotate}, project, render

    // Move
    for (auto &point : shape.vertices)
    {
        point.x += shape.position.x;
        point.y += shape.position.y;
        point.y += shape.position.z;
    }
}

void Renderer::projectShape(Shape &shape)
{
    for (auto &point : shape.vertices)
    {
        preparePoint(point);
    }
}

/*
- Draws the points or their connections/edges on screen
*/
void Renderer::drawShape(Shape &shape)
{
    for(auto &edge: shape.edges) 
    {
        Point3D A = shape.vertices[edge.first];
        Point3D B = shape.vertices[edge.second];

        float offset = POINT_SIZE/2;
        DrawLine(A.x+offset, A.y+offset, B.x+offset, B.y+offset, edge.color);  // Render Edge
    }
}

void Renderer::transformWorld(World &world)
{
    for (auto &shape : world.shapes)
    {
        transformShape(shape);
    }
}

void Renderer::projectWorld(World & world)
{
    for (auto &shape : world.shapes)
    {
        projectShape(shape);
    }
}

// Draw given world to screen
void Renderer::drawWorld(World &world) 
{
    BeginDrawing();
    ClearBackground(BLACK);

    for(auto &shape: world.shapes) 
    {
        drawShape(shape);
    }

    EndDrawing();
}

// Check key presses, decide movement #TODO make camera movement and shape movement input seperate
void Renderer::handleInput()
{
    // By default do no movement
    dx = dy = 0;

    // Return if no key pressed
    if (GetKeyPressed() == 0) return; 
    
    // Decide change in x or y based on input
    if (IsKeyDown(KEY_W)) dy += 1;
    if (IsKeyDown(KEY_S)) dy -= 1;
    if (IsKeyDown(KEY_A)) dx -= 1;
    if (IsKeyDown(KEY_D)) dx += 1;
}

/*
- Transforms
- Projects
*/
void Renderer::update(World &world)
{
    transformWorld(world);
    projectWorld(world);    
}

void Renderer::pushWorldIntoView(World &world, int amount)
{
    for (auto &shape : world.shapes)
    {
        for (auto &point : shape.vertices)
        {
            point.z+=amount;
        }
    }
}

// Render world via render pipeline, Transform->Project->Draw
void Renderer::render(World &world)
{
    update   (world);  // Transform, Project, and Input
    drawWorld(world);  // Draw to screen
}

// clang-format on
float Renderer::focal = 500.f;
float Renderer::dx    = 0;
float Renderer::dy    = 0;

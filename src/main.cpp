#include "points.h"
#include "raylib-cpp.hpp"
#include "renderer.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    raylib::Window graphicWindow(600, 600, "Graphic Render", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    float h = 100.f; // Cube face distance from origin, Used to create symmetric cube
    Shape cube;

    cube.vertices = {
        {-h, -h, -h}, {h, -h, -h}, {h, h, -h}, {-h, h, -h},
        {-h, -h,  h}, {h, -h,  h}, {h, h,  h}, {-h, h,  h}
    };

    cube.edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };

    World world;
    world.shapes.push_back(cube);
    Renderer::pushWorldIntoView(world, 600);// Temp function
    
    while (!WindowShouldClose())
    {
        Renderer::handleInput();
        Renderer::render(world);
    }
    return 0;
}
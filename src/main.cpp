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

    float h = 100.f; // Distance from Center {0,0,0} of the cube's faces, Used to create symmetric cube
    vector<Point3D> cube = {{-h, -h, -h}, {h, -h, -h}, {h, h, -h}, {-h, h, -h},
                            {-h, -h, h},  {h, -h, h},  {h, h, h},  {-h, h, h}};

    vector<Point2D> points2D;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto &p : cube)
        {
            p.x += 0.01;
            Renderer::render(p);
        }

        EndDrawing();
    }
}

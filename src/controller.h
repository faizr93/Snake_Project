#include "raylib-cpp.hpp"
#include "world.h"
// handles input, camera movement, shape movement
class Controller 
{
    public:
    static bool moveMode;

    raylib::Vector3 camMove       = {0,0,0};
    raylib::Vector3 shapeMove     = {0,0,0};

    static void handleInput();         // Decide if an action is needed
    static void update(World &world);  // Perform the needed action
};
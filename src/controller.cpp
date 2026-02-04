#include "controller.h"

// Check key presses, decide movement #TODO make camera movement and shape movement input seperate
void Controller::handleInput() {

    // By default do no movement
    int dx, dy, dz;
    dx = dy = dz = 0;

    // Return if no key pressed
    if (GetKeyPressed() == 0) return; 
    
    if(IsKeyPressed(KEY_O)) moveMode=0;
    if(IsKeyPressed(KEY_P)) moveMode=1;

    // Decide change in x or y based on input
    if (IsKeyDown(KEY_W)) dy += 1;
    if (IsKeyDown(KEY_A)) dx -= 1;
    if (IsKeyDown(KEY_S)) dy -= 1;
    if (IsKeyDown(KEY_D)) dx += 1;

    if (IsKeyDown(KEY_I)) dz += 1;
    if (IsKeyDown(KEY_K)) dz -= 1;
}
void Controller::update(World &world) {}
bool moveMode = 0;
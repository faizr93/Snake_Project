#include "shape.h"
#include "raylib-cpp.hpp"

void Shape::move(const raylib::Vector3 &delta) 
{
    position.x += delta.x;
    position.y += delta.y;
    position.z += delta.z;
}

void Shape::rotate(const raylib::Vector3 &delta) 
{
    rotation.x += delta.x;
    rotation.y += delta.y;
    rotation.z += delta.z;
}

void EdgeIndexPair::setColor(Color c) { this->color = c; }

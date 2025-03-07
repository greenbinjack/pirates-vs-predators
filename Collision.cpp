/// Collision.cpp - Implementation of Collision System
#include "Collision.hpp"
#include <iostream>

bool Collision::checkCollision(Entity* a, Entity* b) {
    return a->getBounds().intersects(b->getBounds());
}

/// Collision.hpp - Handles Attack & Collision Detection
#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "Entity.hpp"
#include "Predator.hpp"
#include "Pirate.hpp"

class Collision {
public:
    static bool checkCollision(Entity* a, Entity* b);
};
#endif

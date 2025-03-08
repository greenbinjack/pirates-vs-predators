#include "Gunner.hpp"
#include <iostream>

Gunner::Gunner(const std::string &textureFile, float x, float y)
    : Pirate(textureFile, x, y, 10, 1.5f, 600.0f) {}

Bullet* Gunner::fireBullet(float deltaTime) {
    return Pirate::fireBullet(deltaTime);
}

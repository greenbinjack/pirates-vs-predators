#include "CannonShooter.hpp"
#include <iostream>

CannonShooter::CannonShooter(const std::string &textureFile, float x, float y)
    : Pirate(textureFile, x, y, 10, 2.0f, 500.0f) {}

Bullet* CannonShooter::fireBullet(float deltaTime) {
    return Pirate::fireBullet(deltaTime);
}

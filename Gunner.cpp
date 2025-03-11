#include "Gunner.hpp"
#include <iostream>

const int ATTACK_POWER = 10;
const float ATTACK_SPEED = 1.5;
const float BULLET_SPEED = 600;

Gunner::Gunner(const std::string &textureFile, float x, float y)
    : Pirate(textureFile, x, y, ATTACK_POWER, ATTACK_SPEED, BULLET_SPEED) {}

Bullet* Gunner::fireBullet(float deltaTime) {
    return Pirate::fireBullet(deltaTime);
}

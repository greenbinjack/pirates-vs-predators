#include "CannonShooter.hpp"
#include <iostream>

const int ATTACK_POWER = 10;
const float ATTACK_SPEED = 2.0;
const float BULLET_SPEED = 500;

CannonShooter::CannonShooter(const std::string &textureFile, float x, float y)
    : Pirate(textureFile, x, y, ATTACK_POWER, ATTACK_SPEED, BULLET_SPEED) {}

Bullet* CannonShooter::fireBullet(float deltaTime) {
    return Pirate::fireBullet(deltaTime);
}

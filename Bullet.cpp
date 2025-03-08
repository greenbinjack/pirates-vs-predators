#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(const std::string &textureFile, float x, float y, float speed, int damage)
    : Entity(textureFile, x, y), speed(speed), damage(damage) {}

void Bullet::update(float deltaTime) {
    position.x += speed * deltaTime * 6;  // Bullet moves right
    sprite.setPosition(position);
}

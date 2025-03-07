#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(const std::string &textureFile, float x, float y, float speed, int damage)
    : Entity(textureFile, x, y), speed(speed), damage(damage) {}

void Bullet::update(float deltaTime) {
    move(deltaTime);  // 🔹 Move the bullet each frame
}

void Bullet::move(float deltaTime) {
    position.x += speed * deltaTime * 0.2f;  // Move right
    sprite.setPosition(position);
    std::cout << "[DEBUG] Bullet moved to X=" << position.x << ", Y=" << position.y << std::endl;
}

int Bullet::getDamage() const {
    return damage;
}

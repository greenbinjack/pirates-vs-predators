#include "Gunner.hpp"
#include <iostream>

Gunner::Gunner(const std::string &textureFile, float x, float y) : Pirate(textureFile, x, y, 10, 1.5f) {}

void Gunner::attack(Predator* enemy) {
    enemy->takeDamage(attackPower);
    std::cout << "[DEBUG] Gunner attacked a predator!" << std::endl;
}

Bullet* Gunner::fireBullet(float deltaTime) {
    if (timeSinceLastShot >= attackSpeed) {
        timeSinceLastShot = 0;
        std::cout << "[DEBUG] Gunner fired a bullet!" << std::endl;
        return new Bullet("assets/bullet.png", position.x + 50, position.y + 20, 600.0f, attackPower);
    }
    return nullptr;
}

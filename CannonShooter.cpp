#include "CannonShooter.hpp"

CannonShooter::CannonShooter(const std::string &textureFile, float x, float y) 
    : Pirate(textureFile, x, y, 150, 2.0f) {}  // Example: 150 HP, 2.0 attack speed

void CannonShooter::update(float deltaTime) {
    // CannonShooter remains stationary but can fire bullets
}

void CannonShooter::attack(Predator* enemy) {
    enemy->takeDamage(20);  // Example: CannonShooter deals 20 damage per shot
}

Bullet* CannonShooter::fireBullet(float deltaTime) {
    return new Bullet("assets/bullet.png", position.x + 20, position.y, 250.0f, 20);
}

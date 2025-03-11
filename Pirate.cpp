#include "Pirate.hpp"
#include <iostream>

Pirate::Pirate(const std::string &textureFile, float x, float y, int attackPower, float attackSpeed, float bulletSpeed)
    : Entity(textureFile, x, y), attackPower(attackPower), attackSpeed(attackSpeed), bulletSpeed(bulletSpeed) {}

Bullet* Pirate::fireBullet(float deltaTime) {
    if (fireCooldown.getElapsedTime().asSeconds() >= attackSpeed) {
        fireCooldown.restart();
        return new Bullet("assets/bullet.png", position.x + 50, position.y, bulletSpeed, attackPower);
    }
    return nullptr;
}

void Pirate::update(float deltaTime) {
    
}

void Pirate::render(sf::RenderWindow &window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

#include "Pirate.hpp"
#include <iostream>

Pirate::Pirate(const std::string &textureFile, float x, float y, int attackPower, float attackSpeed)
    : Entity(textureFile, x, y), attackPower(attackPower), attackSpeed(attackSpeed), timeSinceLastShot(0) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "[ERROR] Failed to load Pirate texture: " << textureFile << std::endl;
    } else {
        sprite.setTexture(texture);
    }
}

void Pirate::update(float deltaTime) {
    timeSinceLastShot += deltaTime;  // Update attack cooldown
}

Bullet* Pirate::fireBullet(float deltaTime) {
    if (timeSinceLastShot >= attackSpeed) {
        timeSinceLastShot = 0;  // Reset attack timer

        std::cout << "[DEBUG] Pirate fired a bullet!" << std::endl;
        return new Bullet("assets/bullet.png", position.x + 50, position.y + 20, 600.0f, attackPower);
    }
    return nullptr;
}

void Pirate::render(sf::RenderWindow &window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

#include "Predator.hpp"
#include <iostream>

Predator::Predator(const std::string &textureFile, float x, float y, int health, float speed)
    : Entity(textureFile, x, y), health(health), speed(speed) {}

void Predator::update(float deltaTime) {
    position.x -= speed * deltaTime * 100;  // Move left
    sprite.setPosition(position);
}

void Predator::render(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Predator::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        std::cout << "[DEBUG] Predator Defeated!" << std::endl;
    }
}

bool Predator::isDefeated() const {
    return health <= 0;
}

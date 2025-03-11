#include "Predator.hpp"
#include <iostream>

const float COLLISION_DELAY = 1.0f;
const int MOVEMENT_FACTOR = 100;

Predator::Predator(const std::string &textureFile, float x, float y, int health, float speed)
    : Entity(textureFile, x, y), health(health), speed(speed), isPaused(false) {}

void Predator::update(float deltaTime) {
    if (isPaused) {
        if (collisionTimer.getElapsedTime().asSeconds() >= COLLISION_DELAY) {  
            isPaused = false;  
        } else {
            return;  
        }
    }

    position.x -= speed * deltaTime * MOVEMENT_FACTOR;  // Move left
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

void Predator::pauseMovement() {
    isPaused = true;  
    collisionTimer.restart();
}

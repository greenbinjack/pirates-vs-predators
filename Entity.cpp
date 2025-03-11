#include "Entity.hpp"
#include <iostream>
#include <stdexcept>

Entity:: Entity(const std::string &textureFile, float x, float y) : position(x, y) {
    try {
        if (!texture.loadFromFile(textureFile)) {
            throw std:: runtime_error("Failed to load texture: " + textureFile);
        }
        sprite.setTexture(texture);
    } catch (const std:: exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}

sf::Sprite& Entity::getSprite() { return sprite; } 
sf::FloatRect Entity::getBounds() const { return sprite.getGlobalBounds(); }
sf::Vector2f Entity::getPosition() const { return position; }

#include "Entity.hpp"
#include <iostream>

Entity::Entity(const std::string &textureFile, float x, float y) : position(x, y) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "[ERROR] Failed to load texture: " << textureFile << std::endl;
    } else {
        sprite.setTexture(texture);
    }
}

void Entity::render(sf::RenderWindow &window) {
    sprite.setPosition(position);
    window.draw(sprite);
}

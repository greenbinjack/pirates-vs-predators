#include "Entity.hpp"
#include "Constants.hpp"
#include <iostream>
#include <stdexcept>

Entity::Entity (const std::string &textureFile, float x, float y) : position (x, y)
{
    loadTexture (texture, textureFile);
    sprite.setTexture (texture);
}

sf::Sprite &
Entity::getSprite ()
{
    return sprite;
}

sf::FloatRect
Entity::getBounds () const
{
    return sprite.getGlobalBounds ();
}

sf::Vector2f
Entity::getPosition () const
{
    return position;
}

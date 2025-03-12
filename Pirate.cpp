#include "Constants.hpp"
#include "Pirate.hpp"
#include <iostream>

Pirate::Pirate (const std::string &textureFile, float x, float y, int attackPower, float attackSpeed, float bulletSpeed) : Entity (textureFile, x, y), attackPower (attackPower), attackSpeed (attackSpeed), bulletSpeed (bulletSpeed) {}

void
Pirate::update (float deltaTime)
{
}

void
Pirate::render (sf::RenderWindow &window)
{
    sprite.setPosition (position);
    window.draw (sprite);
}

#include "Bullet.hpp"
#include "Constants.hpp"

Bullet::Bullet (const std::string &textureFile, float x, float y, float speed, int damage) : Entity (textureFile, x, y), speed (speed), damage (damage) {}

void
Bullet::update (float deltaTime)
{
    position.x += speed * deltaTime * BULLET_MOVEMENT_FACTOR;
    sprite.setPosition (position);
}

void
Bullet::render (sf::RenderWindow &window)
{
    window.draw (sprite);
}

int
Bullet::getDamage () const
{
    return damage;
}

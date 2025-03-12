#include "Constants.hpp"
#include "Gunner.hpp"
#include <iostream>

Gunner::Gunner (const std::string &textureFile, float x, float y) : Pirate (textureFile, x, y, GUNNER_ATTACK_POWER, GUNNER_ATTACK_SPEED, GUNNER_BULLET_SPEED) {}

Bullet *
Gunner::fireBullet (float deltaTime)
{
    if (fireCooldown.getElapsedTime ().asSeconds () >= attackSpeed)
        {
            fireCooldown.restart ();
            return new Bullet (IMG_BULLET, position.x + 65, position.y + 40, bulletSpeed, attackPower);
        }
    return nullptr;
}

int
Gunner::getPrice ()
{
    return GUNNER_PRICE;
}
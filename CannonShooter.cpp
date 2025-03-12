#include "CannonShooter.hpp"
#include "Constants.hpp"
#include <iostream>

CannonShooter::CannonShooter (const std::string &textureFile, float x, float y) : Pirate (textureFile, x, y, CANNONSHOOTER_ATTACK_POWER, CANNONSHOOTER_ATTACK_SPEED, CANNONSHOOTER_BULLET_SPEED) {}

Bullet *
CannonShooter::fireBullet (float deltaTime)
{
    if (fireCooldown.getElapsedTime ().asSeconds () >= attackSpeed)
        {
            fireCooldown.restart ();
            return new Bullet (IMG_CANNONBALL, position.x + 70, position.y + 40, bulletSpeed, attackPower);
        }
    return nullptr;
}

int
CannonShooter::getPrice ()
{
    return CANNONSHOOTER_PRICE;
}
#include "Predator.hpp"
#include "Constants.hpp"
#include <iostream>

Predator::Predator (const std::string &textureFile, float x, float y, int health, float speed, int gridRow) : Entity (textureFile, x, y), health (health), speed (speed), row (gridRow), isPaused (false) {}

void
Predator::update (float deltaTime)
{
    if (isPaused)
        {
            if (collisionTimer.getElapsedTime ().asSeconds () >= PREDATOR_COLLISION_DELAY)
                {
                    isPaused = false;
                }
            else
                {
                    return;
                }
        }

    position.x -= speed * deltaTime * PREDATOR_MOVEMENT_FACTOR; // Move left
    sprite.setPosition (position);
}

void
Predator::render (sf::RenderWindow &window)
{
    window.draw (sprite);
}

void
Predator::takeDamage (int damage)
{
    health -= damage;
    if (health <= 0)
        {
            std::cout << "[DEBUG] Predator Defeated!" << std::endl;
        }
}

bool
Predator::isDefeated () const
{
    return health <= 0;
}

void
Predator::pauseMovement ()
{
    isPaused = true;
    collisionTimer.restart ();
}

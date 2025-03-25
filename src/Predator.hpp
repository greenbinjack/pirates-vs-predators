#ifndef PREDATOR_HPP
#define PREDATOR_HPP

#include "Entity.hpp"

class Predator : public Entity
{
  private:
    int health;
    float speed;
    sf::Clock collisionTimer; /// Timer for movement delay
    bool isPaused;            /// due to collision
    int row;
    sf::Texture predatorTexture;

  public:
    Predator (const std::string &textureFile, float x, float y, int health, float speed, int gridRow);
    void update (float deltaTime) override;
    void render (sf::RenderWindow &window) override;
    void takeDamage (int damage);
    bool isDefeated () const;
    void pauseMovement ();
    int
    getRow () const
    {
        return row;
    }
};

#endif

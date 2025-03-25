#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"

class Bullet : public Entity
{
  private:
    float speed;
    int damage;

  public:
    Bullet (const std::string &textureFile, float x, float y, float speed, int damage);
    void update (float deltaTime) override;
    void render (sf::RenderWindow &window) override;
    int getDamage () const;
};
#endif

#ifndef BULLET_HPP
#define BULLET_HPP
#include "Entity.hpp"

class Bullet : public Entity {
private:
    float speed;
    int damage;

public:
    Bullet(const std::string &textureFile, float x, float y, float speed, int damage);
    void update(float deltaTime) override;  // Use update() instead of move()
    int getDamage() const { return damage; }
};
#endif

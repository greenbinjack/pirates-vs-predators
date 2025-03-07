#ifndef BULLET_HPP
#define BULLET_HPP
#include "Entity.hpp"

class Bullet : public Entity {
private:
    float speed;
    int damage;

public:
    Bullet(const std::string &textureFile, float x, float y, float speed, int damage);
    void update(float deltaTime) override;  // 🔹 Override update function
    void move(float deltaTime);
    int getDamage() const;
};
#endif

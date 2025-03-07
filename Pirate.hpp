#ifndef PIRATE_HPP
#define PIRATE_HPP
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Predator.hpp"
#include <vector>

class Pirate : public Entity {
protected:
    int attackPower;
    float attackSpeed;
    float timeSinceLastShot;

public:
    Pirate(const std::string &textureFile, float x, float y, int attackPower, float attackSpeed);
    virtual ~Pirate() override {}  // 🔹 Add virtual destructor

    virtual void attack(Predator* enemy) = 0;  // 🔹 Ensure this is implemented
    virtual Bullet* fireBullet(float deltaTime) = 0;  // 🔹 Ensure this is implemented

    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
};
#endif

#ifndef PIRATE_HPP
#define PIRATE_HPP

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Predator.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>

class Pirate : public Entity {
protected:
    int attackPower;
    float attackSpeed;
    float bulletSpeed;
    sf::Clock fireCooldown;  // Timer for firing bullets
public:
    Pirate(const std::string &textureFile, float x, float y, int attackPower, float attackSpeed, float bulletSpeed);
    virtual ~Pirate() override {}

    virtual Bullet* fireBullet(float deltaTime) = 0;
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
};

#endif

#ifndef PREDATOR_HPP
#define PREDATOR_HPP
#include "Entity.hpp"

class Predator : public Entity {
private:
    int health;
    float speed;

public:
    Predator(const std::string &textureFile, float x, float y, int health, float speed);
    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
    void takeDamage(int damage);
    bool isDefeated() const;
};
#endif

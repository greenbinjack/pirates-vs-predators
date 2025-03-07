#ifndef GUNNER_HPP
#define GUNNER_HPP
#include "Pirate.hpp"

class Gunner : public Pirate {
public:
    Gunner(const std::string &textureFile, float x, float y);
    void attack(Predator* enemy) override;
    Bullet* fireBullet(float deltaTime) override;
};
#endif

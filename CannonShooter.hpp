#ifndef CANNONSHOOTER_HPP
#define CANNONSHOOTER_HPP
#include "Pirate.hpp"

class CannonShooter : public Pirate {
public:
    CannonShooter(const std::string &textureFile, float x, float y);
    void update(float deltaTime) override;  // 🔹 Now properly declared
    void attack(Predator* enemy) override;
    Bullet* fireBullet(float deltaTime) override;
};
#endif

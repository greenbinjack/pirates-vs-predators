#ifndef CANNONSHOOTER_HPP
#define CANNONSHOOTER_HPP

#include "Pirate.hpp"

class CannonShooter : public Pirate
{
  public:
    CannonShooter (const std::string &textureFile, float x, float y);
    Bullet *fireBullet (float deltaTime) override;
    int getPrice ();
};

#endif

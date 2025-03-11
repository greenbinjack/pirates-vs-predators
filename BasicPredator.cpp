#include "BasicPredator.hpp"

const int HEALTH = 100;
const float SPEED = 2.0f;

BasicPredator::BasicPredator(const std::string &textureFile, float x, float y) 
  : Predator(textureFile, x, y, HEALTH, SPEED) {}
    
void BasicPredator:: update(float deltaTime) override { move(deltaTime); }
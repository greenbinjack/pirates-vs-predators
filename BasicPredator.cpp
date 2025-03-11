#include "BasicPredator.hpp"
#include "Constants.hpp"

BasicPredator::BasicPredator(const std::string &textureFile, float x, float y) 
  : Predator(textureFile, x, y, BASIC_PREDATOR_HEALTH, BASIC_PREDATOR_SPEED) {}
    
void BasicPredator:: update(float deltaTime) override { move(deltaTime); }
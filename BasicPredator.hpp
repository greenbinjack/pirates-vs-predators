#ifndef BASIC_PREDATOR_HPP
#define BASIC_PREDATOR_HPP

#include "Predator.hpp"

class BasicPredator : public Predator {
public:
    BasicPredator(const std::string &textureFile, float x, float y);
    void update(float deltaTime) override;
};

#endif

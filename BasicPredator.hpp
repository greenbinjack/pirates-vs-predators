#ifndef BASIC_PREDATOR_HPP
#define BASIC_PREDATOR_HPP
#include "Predator.hpp"

class BasicPredator : public Predator {
public:
    BasicPredator(float x, float y) : Predator("assets/predator.png", x, y, 100, 2.0f) {}
    void update(float deltaTime) override { move(deltaTime); }
};

#endif

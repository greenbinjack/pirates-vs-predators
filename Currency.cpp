/// Currency.cpp - Implementation of Gold System
#include "Currency.hpp"

Currency::Currency() : gold(234234) {}

void Currency::addGold(int amount) {
    gold += amount;
}

bool Currency::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

int Currency::getGold() const {
    return gold;
}

void Currency::resetGold () {
    gold = 234234;
}
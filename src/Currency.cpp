#include "Constants.hpp"
#include "Currency.hpp"

Currency::Currency () : gold (INITIAL_GOLD) {}

void
Currency::addGold (int amount)
{
    gold += amount;
}

bool
Currency::spendGold (int amount)
{
    if (gold >= amount)
        {
            gold -= amount;
            return true;
        }
    return false;
}

int
Currency::getGold () const
{
    return gold;
}

void
Currency::resetGold ()
{
    gold = INITIAL_GOLD;
}
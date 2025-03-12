#ifndef CURRENCY_HPP
#define CURRENCY_HPP

class Currency
{
  private:
    int gold;

  public:
    Currency ();
    void resetGold ();
    void addGold (int amount);
    bool spendGold (int amount);
    int getGold () const;
};
#endif

#pragma once
#include "Item.h"



class Potion : public Item
{
    private:
    int amount;

    public:
    Potion(std::string name, int amount) : Item(name), amount(amount) {}
    virtual void use(Player& player) = 0;

protected:
    int getAmount() const { return amount; }

};

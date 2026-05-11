#pragma once
#include "Potion.h"

class ShieldPotion : public Potion
{
private:
public:
    ShieldPotion() : Potion("ShieldPotion", 8) {} // Constructor oluşturma islemi
    void use(Player &Player) override
    {
    }
};

#pragma once
#include "Potion.h"

class HealthPotion : public Potion
{
private:
public:
    HealthPotion() : Potion("HealtPotion", 20) {} // Constructor oluşturma islemi
    void use(Player &Player) override
    {
    }
};

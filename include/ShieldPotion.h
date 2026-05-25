#pragma once
#include "Potion.h"
#include "Player.h"

class ShieldPotion : public Potion
{
public:
    ShieldPotion() : Potion("ShieldPotion", 8) {}
    void use(Player& player) override
    {
        player.setDefense(player.getDefense() + getAmount());
    }
};

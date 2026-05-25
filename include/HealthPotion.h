#pragma once
#include "Potion.h"
#include "Player.h"

class HealthPotion : public Potion
{
public:
    HealthPotion() : Potion("HealthPotion", 20) {}
    void use(Player& player) override
    {
        player.setHp(player.getHp() + getAmount());
    }
};
